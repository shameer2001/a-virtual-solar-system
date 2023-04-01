#ifndef solarSystem_hpp
#define solarSystem_hpp

#include "particle.hpp"
#include <memory>

class SolarSystem {

  public:
  SolarSystem();
  SolarSystem(std::vector<std::shared_ptr<Particle>>& in_body_list);
  
  Particle celestialBody(double mass, double distance); // Mass is relative to the sun and distance is that between body and sun
  
  void InitialConditionGenerator(); 
  std::vector<std::shared_ptr<Particle>> getCelestialBodyList();

  void evolutionOfSolarSystem(double dt, double total_time);
  void printMessages();

  private:
  std::vector<std::shared_ptr<Particle>> celestial_body_list;




};


#endif