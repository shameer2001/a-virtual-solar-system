#include "solarSystem.hpp"
#include <chrono>
#include <iostream>


SolarSystem::SolarSystem() {} // Constructor for celestial body list as the solar system
SolarSystem::SolarSystem(std::vector<std::shared_ptr<Particle>>& in_body_list): celestial_body_list(in_body_list) {} // Constructor for custom celestial body list (for testing)


Particle SolarSystem::celestialBody(double mass, double distance) // Mass is relative to the sun and distance is that between body and sun
{
    if (mass == 1.0 && distance == 0.0) // The sun
    {
        Eigen::Vector3d pos_sun(distance, distance, distance);
        Eigen::Vector3d vel_sun(0.0, 0.0, 0.0);
        Eigen::Vector3d acc_sun(0.0, 0.0, 0.0);

        return Particle {mass, pos_sun, vel_sun, acc_sun};
    }
    else {
        // Seed the random number generator
        std::srand(std::time(0));
        double theta = static_cast<double>(std::rand()) / RAND_MAX * (2 * M_PI); // Random theta between 0 and 2pi
        
        Eigen::Vector3d pos(distance * sin(theta),  distance * cos(theta),  0.0);
        Eigen::Vector3d vel((-1.0/sqrt(distance)) * cos(theta),  (1.0/sqrt(distance)) * sin(theta), 0.0);
        Eigen::Vector3d acc(0.0, 0.0, 0.0); // Initial acceleration is 0 or all bodies

        return Particle {mass, pos, vel, acc};
    }

} 


// Generate Particle list for solar system bodies
std::vector<std::shared_ptr<Particle>> SolarSystem::generateInitialConditions() {

    // Store mass and distances in a vector:
    std::vector<std::pair<double, double>> mass_dist = {
     // {mass relative to sun, distance to sun relative to earth-sun distance}
        {1.0, 0.0},              // Sun
        {1.0/6023600.0, 0.4},    // Mercury
        {1.0/408524.0, 0.7},     // Venus
        {1.0/332946.038, 1.0},   // Earth
        {1.0/3098710.0, 1.5},    // Mars
        {1.0/1047.55, 5.2},      // Jupiter
        {1.0/3499.0, 9.5},       // Saturn
        {1.0/22962.0, 19.2},     // Uranus
        {1.0/19352.0, 30.1}      // Neptune
    };
    celestial_body_list.clear(); // Ensure list is empty

    // Loop through vector to create Particle instances for each body and push into list
    for (const auto& [mass, distance] : mass_dist) {

        auto body = std::make_shared<Particle>(celestialBody(mass, distance)); // Make celestial body instance as shared pointers
        celestial_body_list.push_back(body);
    }

    return celestial_body_list;
}



std::vector<std::shared_ptr<Particle>> SolarSystem::getCelestialBodyList() {
    return celestial_body_list; 
}




void SolarSystem::printMessages() {
    std::vector<std::string> names{"Sun", "Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus","Neptune"};

    for (int i =0; i < celestial_body_list.size(); i++) {

        // If Sun's acceleration is unchanged 
        if(celestial_body_list[0]->getAcceleration() == Eigen::Vector3d {0.0, 0.0, 0.0} ) {

            std::cout << "The initial position of " << names[i] << " is (" 
            << celestial_body_list[i]->getPosition()[0] << ", " 
            << celestial_body_list[i]->getPosition()[1] << ", "
            << celestial_body_list[i]->getPosition()[2]
            << ").\n";
        }
        // If Sun's acceleration is changed (i.e. simulation has ran)
        else {
            std::cout << "The final position of " << names[i] << " is (" 
            << celestial_body_list[i]->getPosition()[0] << ", " 
            << celestial_body_list[i]->getPosition()[1] << ", "
            << celestial_body_list[i]->getPosition()[2]
            << ").\n";   
        }
    }
    std::cout << "" << std::endl;

}






// Evolution of any system of bodies as a separate function
void evolutionOfSystem(const std::vector<std::shared_ptr<Particle>>& particle_list, double dt, double total_time) {

    // Loop for full simulation time
    for (double sim_time = 0.0; sim_time < total_time; sim_time += dt) {

        // Update acceleration felt by each body
        for (auto& particle : particle_list) {
            sumAccelerations(particle_list, *particle);
        }
        // Update position and velocity of each body
        for (auto& particle : particle_list) {
            particle->update(dt);
        }
    }
}






///////////////////////////////////////////////////////// Energy Functions /////////////////////////////////////////////////////////



double totalKineticEnergy(const std::vector<std::shared_ptr<Particle>>& particle_list) {
    double tot_KE_sum = 0.0;
    
    for(int i = 0; i < particle_list.size(); i++) {
        tot_KE_sum += particle_list[i]->getMass() * (particle_list[i]->getVelocity()).squaredNorm(); // KE equation
    }
    return tot_KE_sum * 0.5;
}




double totalPotentialEnergy(const std::vector<std::shared_ptr<Particle>>& particle_list) {
    double tot_PE_sum = 0.0;

    // Loop for total PE
    for (int i = 0; i < particle_list.size(); i++) {

        // Loop for PE of 1 particle
        for (int j = 0; j < particle_list.size(); j++) {

            // If the particle in the list is not the particle who's PE is being calculated
            if ( i != j ) 
            {
                tot_PE_sum += ( particle_list[i]->getMass() * particle_list[j]->getMass() ) 
                / ( particle_list[j]->getPosition() - particle_list[i]->getPosition() ).norm(); // The PE between two particles
            }
        }
    }

    return tot_PE_sum * -0.5;
}




double totalEnergy(const std::vector<std::shared_ptr<Particle>>& particle_list) {
    return totalKineticEnergy(particle_list) + totalPotentialEnergy(particle_list);
}



void printEnergyMessages(const std::vector<std::shared_ptr<Particle>>& particle_list) {

    // If Sun's acceleration is unchanged
    if(particle_list[0]->getAcceleration() == Eigen::Vector3d {0.0, 0.0, 0.0} ) {

    std::cout << "The initial total kinetic energy of the system is " << totalKineticEnergy(particle_list) << "\n"
                << "The initial total potential energy of the system is " << totalPotentialEnergy(particle_list) << "\n"
                << "The initial total energy of the system is " << totalEnergy(particle_list) << "\n"
    << std::endl;
    }

    // If Sun's acceleration is changed (i.e. simulation has ran)
    else {
    std::cout << "The final total kinetic energy of the system is " << totalKineticEnergy(particle_list) << "\n"
                << "The final total potential energy of the system is " << totalPotentialEnergy(particle_list) << "\n"
                << "The final total energy of the system is " << totalEnergy(particle_list) << "\n"
    << std::endl;
    }

}