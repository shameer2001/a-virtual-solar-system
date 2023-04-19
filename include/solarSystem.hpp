#ifndef solarSystem_hpp
#define solarSystem_hpp

#include "particle.hpp"


// Initial condition generator abstract class
class InitialConditionGenerator {
    public:
    virtual std::vector<std::shared_ptr<Particle>> generateInitialConditions() = 0;
};

// Initial condition generator for the solar system
class SolarSystem : public InitialConditionGenerator  // Refactor class as subclass for base class InitialConditionGenerator
{

  public:
  SolarSystem();
  SolarSystem(std::vector<std::shared_ptr<Particle>>& in_body_list);

  // Generate Particle list for solar system bodies
  std::vector<std::shared_ptr<Particle>> generateInitialConditions() override; 
  std::vector<std::shared_ptr<Particle>> getCelestialBodyList() const; // Mainly for tests

  void printMessages();

  private:
  std::vector<std::shared_ptr<Particle>> celestial_body_list;

};

// Generate a celestial body as a separate function
Particle celestialBody(double mass, double distance, double angle); // Mass relative to the sun and distance that between body and sun

// Evolution of any system of bodies as a separate function
void evolutionOfSystem(const std::vector<std::shared_ptr<Particle>>& particle_list, double dt, double total_time, double epsilon = 0.0);



double totalKineticEnergy(const std::vector<std::shared_ptr<Particle>>& particle_list);
double totalPotentialEnergy(const std::vector<std::shared_ptr<Particle>>& particle_list);
double totalEnergy(const std::vector<std::shared_ptr<Particle>>& particle_list);

void printEnergyMessages(const std::vector<std::shared_ptr<Particle>>& particle_list);


#endif