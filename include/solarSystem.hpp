#ifndef solarSystem_hpp
#define solarSystem_hpp

#include "particle.hpp"
#include <memory>

// Initial condition generator abstract class
class InitialConditionGenerator {
    public:
    virtual std::vector<std::shared_ptr<Particle>> generateInitialConditions() = 0;
};


class SolarSystem : public InitialConditionGenerator  // Refactor class as subclass for base class InitialConditionGenerator
{

  public:
  SolarSystem();
  SolarSystem(std::vector<std::shared_ptr<Particle>>& in_body_list);
  
  Particle celestialBody(double mass, double distance); // Mass is relative to the sun and distance is that between body and sun

  std::vector<std::shared_ptr<Particle>> generateInitialConditions() override; 
  std::vector<std::shared_ptr<Particle>> getCelestialBodyList(); // Mainly for tests

  void printMessages();

  private:
  std::vector<std::shared_ptr<Particle>> celestial_body_list;

};


void evolutionOfSolarSystem(const std::vector<std::shared_ptr<Particle>>& particle_list, double dt, double total_time);

double totalKineticEnergy(const std::vector<std::shared_ptr<Particle>>& particle_list);
double totalPotentialEnergy(const std::vector<std::shared_ptr<Particle>>& particle_list);
double totalEnergy(const std::vector<std::shared_ptr<Particle>>& particle_list);

void printEnergyMessages(const std::vector<std::shared_ptr<Particle>>& particle_list);



#endif