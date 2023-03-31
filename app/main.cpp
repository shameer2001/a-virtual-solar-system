#include <iostream>
#include "particle.hpp"
#include <chrono>
#include <cstdlib> // Include the cstdlib header for rand()
#include <ctime>   // Include the ctime header for time()


class InitialConditionGenerator {

  public:

  Particle celestialBody(double mass, double distance) // Mass is relative to the sun and distance is that between body and sun
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

  


  std::vector<Particle> solarSystemList() {

    Particle theSun = celestialBody(1.0, 0.0);
    Particle mercury = celestialBody(1.0/6023600.0, 0.4);
    Particle venus = celestialBody(1.0/408524.0, 0.7);
    Particle earth = celestialBody(1.0/332946.038, 1.0);
    Particle mars = celestialBody(1.0/3098710.0, 1.5);
    Particle jupiter = celestialBody(1.0/1047.55, 5.2);
    Particle saturn = celestialBody(1.0/3499.0, 9.5);
    Particle uranus = celestialBody(1.0/22962.0, 19.2);
    Particle neptune = celestialBody(1.0/19352.0, 30.1);


    return std::vector<Particle> {theSun, mercury, venus, earth, mars, jupiter, saturn, uranus, neptune};
  }

  private:


};







void help() {
  std::cout << "Usage: solarSystemSimulator [options]\n"
            << "Options:\n"
            << "  -t, --timestep           Set the timestep in seconds.\n"
            << "  -s, --simulation-time    Set the total simulation time in seconds.\n"
            << "  -h, --help               Show this help message.\n";
}



int main(int argc, char *argv[]) 
{
  // Parse command line arguments
  bool dt = 0.0;
  bool sim_time = 0.0;

  for (int i = 1; i < argc; i++)
  {
    std::string arg = argv[i];

    if (arg == "-t" || arg == "--timestep")
    {
      if (i + 1 < argc) 
      {
        dt = argv[i + 1]; // Argument after --t is the timestep value
        i++;
      }
      else 
      {
        help();
        return 1;
      }
    
    }


    else if (arg == "-s" || arg == "--simulation-time" && (i+1)<argc)
    {
      if (i + 1 < argc) 
      {
        sim_time = argv[i + 1]; // Argument after --t is the filename
        i++;
      }
      else 
      {
        help();
        return 1;
      }
    }


    else if (arg == "-h" || arg == "--help")
    {
      help();
      return 0;
    }


    else 
    {
      help();
      return 0;
    }

  }

  return 0;
}

