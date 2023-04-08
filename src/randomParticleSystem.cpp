#include "randomParticleSystem.hpp"
#include <chrono>
#include <random>


RandomSystem::RandomSystem(int body_num): num_bodies(body_num) {}

Particle RandomSystem::celestialBody(double mass, double distance, double angle) {
    if (mass == 1.0 && distance == 0.0) // A central star
    {
        Eigen::Vector3d pos_star(distance, distance, distance);
        Eigen::Vector3d vel_star(0.0, 0.0, 0.0);
        Eigen::Vector3d acc_star(0.0, 0.0, 0.0);

        return Particle {mass, pos_star, vel_star, acc_star};
    }
    else {

        Eigen::Vector3d pos(distance * sin(angle),  distance * cos(angle),  0.0);
        Eigen::Vector3d vel((-1.0/sqrt(distance)) * cos(angle),  (1.0/sqrt(distance)) * sin(angle), 0.0);
        Eigen::Vector3d acc(0.0, 0.0, 0.0); // Initial acceleration is 0 or all bodies

        return Particle {mass, pos, vel, acc};
    }
}

std::vector<std::shared_ptr<Particle>> RandomSystem::generateInitialConditions() {
    celestial_body_list.clear(); // Ensure list is empty

    auto star = std::make_shared<Particle>(celestialBody(1.0, 0.0));
    celestial_body_list.push_back(star);

    std::default_random_engine generator(42); // Seed the random number generator
    std::uniform_real_distribution<double> massDistribution(1.0 / 6000000, 1.0 / 1000);
    std::uniform_real_distribution<double> distanceDistribution(0.4, 30.0);
    std::uniform_real_distribution<double> angleDistribution(0.0, 2.0 * M_PI);

    // Create the remaining particles
    for (unsigned int i = 1; i < num_bodies; i++) {

        // Generate random values:
        double mass = massDistribution(generator);
        double distance = distanceDistribution(generator);
        double angle = angleDistribution(generator);

        auto body = std::make_shared<Particle>(celestialBody(mass, distance, angle)); // Make celestial body instance as shared pointers
        celestial_body_list.push_back(body);
    }

    return celestial_body_list;
}


std::vector<std::shared_ptr<Particle>> RandomSystem::getCelestialBodyList() {
    return celestial_body_list; 
}







