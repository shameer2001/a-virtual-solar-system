#include "solarSystem.hpp"
#include <chrono>
#include <cstdlib> // Include the cstdlib header for rand()
#include <ctime>   // Include the ctime header for time()

SolarSystem::SolarSystem() {} // Constructor for celestial body list as the solar system
SolarSystem::SolarSystem(std::vector<Particle> in_body_list): celestial_body_list(in_body_list) {} // Constructor for custom celestial body list


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
void SolarSystem::InitialConditionGenerator() {

    Particle theSun = celestialBody(1.0, 0.0);
    Particle mercury = celestialBody(1.0/6023600.0, 0.4);
    Particle venus = celestialBody(1.0/408524.0, 0.7);
    Particle earth = celestialBody(1.0/332946.038, 1.0);
    Particle mars = celestialBody(1.0/3098710.0, 1.5);
    Particle jupiter = celestialBody(1.0/1047.55, 5.2);
    Particle saturn = celestialBody(1.0/3499.0, 9.5);
    Particle uranus = celestialBody(1.0/22962.0, 19.2);
    Particle neptune = celestialBody(1.0/19352.0, 30.1);

    // Set private member value:
    celestial_body_list.push_back(theSun);
    celestial_body_list.push_back(mercury);
    celestial_body_list.push_back(venus);
    celestial_body_list.push_back(earth);
    celestial_body_list.push_back(mars);
    celestial_body_list.push_back(jupiter);
    celestial_body_list.push_back(saturn);
    celestial_body_list.push_back(uranus);
    celestial_body_list.push_back(neptune);

}


std::vector<Particle> SolarSystem::getCelestialBodyList() {
    return celestial_body_list; 
}



void SolarSystem::evolutionOfSolarSystem(double dt, double total_time) {

    // Loop for full simulation time
    for (double sim_time = 0.0; sim_time < total_time; sim_time += dt) {

        // Update acceleration felt by each body
        for (auto& particle : celestial_body_list) {
            sumAccelerations(celestial_body_list, particle);
        }
        // Update position and velocity of each body
        for (auto& particle : celestial_body_list) {
            particle.update(dt);
        }
    }
}