#ifndef randomParticleSystem_hpp
#define randomParticleSystem_hpp

#include "solarSystem.hpp"



class RandomSystem : public InitialConditionGenerator  // Refactor class as subclass for base class InitialConditionGenerator
{

  public:
  RandomSystem(int body_num);
  
  Particle celestialBody(double mass, double distance, double angle = 0.0); // Mass is relative to the sun and distance is that between body and sun

  std::vector<std::shared_ptr<Particle>> generateInitialConditions() override; 
  std::vector<std::shared_ptr<Particle>> getCelestialBodyList();


  private:
  int num_bodies;
  std::vector<std::shared_ptr<Particle>> celestial_body_list;




};




#endif