#ifndef solarSystem_hpp
#define solarSystem_hpp

#include "particle.hpp"


class SolarSystem {

  public:
  SolarSystem();
  SolarSystem(std::vector<Particle> in_body_list);
  
  Particle celestialBody(double mass, double distance); // Mass is relative to the sun and distance is that between body and sun
  
  void InitialConditionGenerator(); 
  std::vector<Particle> getCelestialBodyList();

  void evolutionOfSolarSystem(double dt, double total_time);
  void printMessages();

  private:
  std::vector<Particle> celestial_body_list;




};


#endif