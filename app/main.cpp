#include <iostream>
#include "particle.hpp"
#include "solarSystem.hpp"
#include "randomParticleSystem.hpp"
#include <chrono>



void help() {
  std::cout << "Usage: solarSystemSimulator [options]\n"
            << "Options:\n"
            << "  -ss,  --solar-system       To simulate our solar system.\n"
            << "  -rs,  --random-system      To simulate a random solar system with random bodies.\n"
            << "  -n,   --number             Set the number of bodies in the random system.\n"
            << "  -e,   --epsilon            Set the softening factor for the random system. Default is 0.0.\n"
            << "  -t,   --timestep           Set the timestep of the simulation.\n"
            << "  -s,   --simulation-time    Set the total simulation time.\n"
            << "  -h,   --help               Show this help message.\n"
            << "Note: The units for the time arguments are in radians where 2π represents one full earth cycle (i.e. one year).";
}



int main(int argc, char *argv[]) 
{
  // Parse command line arguments
  bool solarsystem = false;
  bool randomsystem = false;
  int num_bodies = 0;
  double soft_fac = 0.0;
  double dt = 0.0;
  double sim_time = 0.0;

  if (argc == 1) // When there are no arguments given
  {
    help();
    return 1;
  }

  for (int i = 1; i < argc; i++)
  {
    std::string arg = argv[i];

    if (arg == "-ss" || arg == "--solar-system") {
      if (i + 1 < argc) // If there are arguments after this one
      {
        solarsystem = true;
      }
      else 
      {
        help();
        return 1;
      }
    }
    else if (arg == "-rs" || arg == "--random-system") {
      if (i + 1 < argc) 
      {
        randomsystem = true;
      }
      else 
      {
        help();
        return 1;
      }    
    }

    else if (arg == "-n" || arg == "--number") {
      if (i + 1 < argc) // If there is a value after this argument
      {
        num_bodies = std::stoi(argv[i + 1]); 
        i++;
      }
      else 
      {
        help();
        return 1;
      }
    }

    else if (arg == "-e" || arg == "--epsilon")
    {
      if (i + 1 < argc)
      {
        soft_fac = strtod(argv[i + 1], NULL); // Convert char to double using strtod()
        i++;
      }
      else 
      {
        help();
        return 1;
      }
    }

    else if (arg == "-t" || arg == "--timestep")
    {
      if (i + 1 < argc)
      {
        dt = strtod(argv[i + 1], NULL); 
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
        sim_time = strtod(argv[i + 1], NULL); 
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

  }





  // Use pointer to base class generateInitialConditions method instead of calling from subclasses
  // This will reduce code duplication and reduce memory usage
  InitialConditionGenerator* systems[2]; // Pointer to initial condition generator base class


  if (solarsystem == true) {

    systems[0] = new SolarSystem(); // Create object of SolarSystem class
    SolarSystem* solar_system = dynamic_cast<SolarSystem*>(systems[0]); // Cast the already defined InitialConditionGenerator Pointer to a SolarSystem pointer. i.e. you can use solar_system as a pointer to SolarSystem and use the other methods exclusive to the SolarSystem class

    // Simulate solar system and it's evolution
    systems[0]->generateInitialConditions();
    solar_system->printMessages(); 
    printEnergyMessages(solar_system->getCelestialBodyList());

    evolutionOfSystem(solar_system->getCelestialBodyList(), dt, sim_time); // Run evolution simulation
    solar_system->printMessages();
    printEnergyMessages(solar_system->getCelestialBodyList());




    // Run simulation for 1 year (2pi) and dt = 0.001:
    std::cout << "=======Running the simulation for one year and with a dt of 0.001=======\n" << std::endl;
    systems[0]->generateInitialConditions();
    solar_system->printMessages();
    evolutionOfSystem(solar_system->getCelestialBodyList(), 0.001, 2 * M_PI); 
    solar_system->printMessages();




    // Run simulation for 1 year (2pi) and 8 different timesteps and print energies:
    std::vector<double> dt_list{0.0001, 0.001, 0.01, 0.1, 1.0, 62.8, 100.0, 314.0};
    std::cout << "=======Run simulation for 1 year and 8 different timesteps and PRINT ENERGIES=======\n" << std::endl;

    for(double& dt: dt_list) {
      std::cout << "-------Running for one year and with dt = " << dt << "-------\n" << std::endl;

      systems[0]->generateInitialConditions();
      solar_system->printMessages(); 
      printEnergyMessages(solar_system->getCelestialBodyList());


      evolutionOfSystem(solar_system->getCelestialBodyList(), dt, 2 * M_PI); 
      solar_system->printMessages();
      printEnergyMessages(solar_system->getCelestialBodyList());

    }




    // Run simulation for 1 year (2pi) and 8 different timesteps and print simulation time:
    double total_runtime = 0.0;
    std::cout << "=======Run simulation for 1 year and 8 different timesteps and PRINT SIMULATION TIME=======\n" << std::endl;
    
    for(double& dt: dt_list) {
      std::cout << "-------Running for one year and with dt = " << dt << " -------\n" <<std::endl;

      auto start_time = std::chrono::high_resolution_clock::now();
      systems[0]->generateInitialConditions();

      #ifdef DEBUG // Disable output when debug enabled in order to prevent inclusion in simulation time calculation
      solar_system->printMessages(); 
      printEnergyMessages(solar_system->getCelestialBodyList());

      #endif

      evolutionOfSystem(solar_system->getCelestialBodyList(), dt, 2 * M_PI); 
      auto end_time = std::chrono::high_resolution_clock::now();

      solar_system->printMessages();
      printEnergyMessages(solar_system->getCelestialBodyList());


      double runtime = std::chrono::duration<double, std::milli>(end_time - start_time).count();
      std::cout << "The runtime of this simulation is " 
                << runtime << " ms\n"
      << std::endl;

      total_runtime += runtime;
    }

    std::cout << "The total simulation time is: " << total_runtime << " ms\n"
              << "The average simulation time is: " << total_runtime / solar_system->getCelestialBodyList().size() << " ms\n"
    << std::endl;





    // Run simulation for 1 year (2pi) and dt = 0.01 and print simulation time (for 0 optimisation flags):
    std::cout << "=======Running for one year and with dt = 0.01=======\n" <<std::endl;

    auto start_time = std::chrono::high_resolution_clock::now();
    systems[0]->generateInitialConditions();

    #ifdef DEBUG
    solar_system->printMessages(); 
    printEnergyMessages(solar_system->getCelestialBodyList());

    #endif

    evolutionOfSystem(solar_system->getCelestialBodyList(), 0.01, 2 * M_PI); 
    auto end_time = std::chrono::high_resolution_clock::now();

    solar_system->printMessages();
    printEnergyMessages(solar_system->getCelestialBodyList());


    double runtime = std::chrono::duration<double, std::milli>(end_time - start_time).count();
    std::cout << "The runtime of this simulation is " 
              << runtime << " ms\n"
    << std::endl;

  }




  else if (randomsystem == true) {
    systems[1] = new RandomSystem(num_bodies); // Create object of RandomSystem class
    RandomSystem* random_system = dynamic_cast<RandomSystem*>(systems[1]); // Cast the already defined InitialConditionGenerator Pointer to a RandomSystem pointer

    // Simulate random system and it's evolution:

    systems[1]->generateInitialConditions();
    printEnergyMessages(random_system->getCelestialBodyList());



    auto start_time = std::chrono::high_resolution_clock::now();
    
    systems[1]->generateInitialConditions(); // Generate again to include in runtime (without excluding energy messages)
    evolutionOfSystem(random_system->getCelestialBodyList(), dt, sim_time, soft_fac); // Run evolution simulation
    
    auto end_time = std::chrono::high_resolution_clock::now();



    printEnergyMessages(random_system->getCelestialBodyList());

    double runtime = std::chrono::duration<double, std::milli>(end_time - start_time).count();
    std::cout << "The runtime of this simulation is " 
              << runtime << " ms\n"
    << std::endl;
  }




  return 0;
}

