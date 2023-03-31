#ifndef solarSystem_hpp
#define solarSystem_hpp

#include "particle.hpp"


class InitialConditionGenerator {

  public:
  Particle celestialBody(double mass, double distance); // Mass is relative to the sun and distance is that between body and sun

  std::vector<Particle> solarSystemList(); 

  private:


};





#endif