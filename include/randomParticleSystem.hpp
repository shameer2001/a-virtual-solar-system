#ifndef randomParticleSystem_hpp
#define randomParticleSystem_hpp

#include "solarSystem.hpp"


// Initial condition generator for a random system
class RandomSystem : public InitialConditionGenerator  // Class as subclass for base class InitialConditionGenerator
{

  public:
  RandomSystem(int body_num);
  
  std::vector<std::shared_ptr<Particle>> generateInitialConditions() override; 
  std::vector<std::shared_ptr<Particle>> getCelestialBodyList();


  private:
  int num_bodies; // Including the star
  std::vector<std::shared_ptr<Particle>> celestial_body_list;




};




#endif