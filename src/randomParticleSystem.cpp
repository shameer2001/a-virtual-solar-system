#include "randomParticleSystem.hpp"



RandomSystem::RandomSystem(int body_num): num_bodies(body_num) {
    if (typeid(body_num) != typeid(int)) {
        throw std::invalid_argument("Number of bodies must be an integer.");
    }
}


std::vector<std::shared_ptr<Particle>> RandomSystem::generateInitialConditions() {
    celestial_body_list.clear(); // Ensure list is empty

    auto star = std::make_shared<Particle>(celestialBody(1.0, 0.0, 0.0));
    celestial_body_list.push_back(star);

    std::default_random_engine generator(42); // Seed the random number generator. Can fix the seed to any value by changing the number.
    std::uniform_real_distribution<double> massDistribution(1.0 / 6000000, 1.0 / 1000);
    std::uniform_real_distribution<double> distanceDistribution(0.4, 30.0);
    std::uniform_real_distribution<double> angleDistribution(0.0, 2.0 * M_PI);

    // Create the remaining particles
    for (unsigned int i = 1; i < num_bodies; i++) {

        // Generate pseudo-random values:
        double mass = massDistribution(generator);
        double distance = distanceDistribution(generator);
        double angle = angleDistribution(generator);

        auto body = std::make_shared<Particle>(celestialBody(mass, distance, angle)); // Make celestial body instance as shared pointers
        celestial_body_list.push_back(body);
    }

    return celestial_body_list;
}


std::vector<std::shared_ptr<Particle>> RandomSystem::getCelestialBodyList() const{
    return celestial_body_list; 
}







