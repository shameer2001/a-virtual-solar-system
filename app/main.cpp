#include "particle.hpp"
#include "solarSystem.hpp"
#include "randomParticleSystem.hpp"
#include <cctype>
#include <string>


void help() {
  std::cout << "Usage: solarSystemSimulator [options]\n"
            << " \n"
            << "Options:\n"
            << "  -ss,  --solar_system       Select to simulate our solar system.\n"
            << "  -rs,  --random_system      Select to simulate a random solar system with random bodies.\n"
            << "  -n,   --number             Set the number of bodies in the random system (must select random system first). Type is integer.\n"
            << "  -e,   --epsilon            Set the softening factor for the random system. Type is double. Default is 0.0.\n"
            << "  -t,   --timestep           Set the timestep of the simulation. Type is double.\n"
            << "  -s,   --simulation_time    Set the total simulation time. Type is double.\n"
            << "  -r,   --runtime            Select if you want measurements of the runtime of the simulation.\n"
            << "  -h,   --help               Show this help message.\n"
            << " \n"
            << "Note 1 : The units for the time arguments are in radians where 2π represents one full earth cycle (i.e. one year).\n"
            << "Note 2 : You can use 'pi' in the simulation time argument to input a precise value of π and multiply it with any number BEFORE 'pi'\n"
            << "         E.G. 2pi = 2π\n"          
            << " "
            << std::endl;
}



int main(int argc, char *argv[]) 
{
  // Parse command line arguments
  bool solarsystem = false;
  bool randomsystem = false;
  int num_bodies = 0;
  double soft_fac = 0.0; // The softening factor i.e epsilon
  double dt = 0.0;
  double sim_time = 0.0;
  bool run_time = false; // To measure runtime or not to measure runtime

  if (argc == 1) // When there are no arguments given
  {
    help();
    return 1;
  }

  for (int i = 1; i < argc; i++)
  {
    std::string arg = argv[i];

    if (arg == "-ss" || arg == "--solar_system") {
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
    else if (arg == "-rs" || arg == "--random_system") {
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

    else if (arg == "-n" || arg == "--number" && (i+1)<argc) {
      if (i + 1 < argc) // If there is a value after this argument
      {
        std::string num_arg = argv[i + 1];
        for (auto c : num_arg) { // Loop through each char in the string
          if (!std::isdigit(c)) { // Check that there is no non-integer character
            throw std::invalid_argument("Number argument must be an integer");
          }
        }

        num_bodies = std::stoi(num_arg); 
        i++;
      }
      else 
      {
        help();
        return 1;
      }
      // Ensure random system is selected for this input to be used:
      if (randomsystem != true) {
        help();
        return 1;
      }
    }

    else if (arg == "-e" || arg == "--epsilon" && (i+1)<argc)
    {
      if (i + 1 < argc)
      {
        const char* input = argv[i + 1];
        char* endptr;
        soft_fac = strtod(input, &endptr); // Convert char to double using strtod()

        if (*endptr != '\0') { // If non-numerical character in argument
          help();
          throw std::invalid_argument("Invalid character encountered in softening factor argument.");
        }
        i++;
      }
      else 
      {
        help();
        return 1;
      }
    }

    else if (arg == "-t" || arg == "--timestep" && (i+1)<argc)
    {
      if (i + 1 < argc)
      {
        const char* input = argv[i + 1];
        char* endptr;
        dt = strtod(input, &endptr); // Convert timestep to double

        if (*endptr != '\0') { // If non-numerical character in argument
          help();
          throw std::invalid_argument("Invalid character encountered in timestep argument.");
        }
        i++;
      }
      else 
      {
        help();
        return 1;
      }
    }

    else if (arg == "-s" || arg == "--simulation_time" && (i+1)<argc)
    {
      if (i + 1 < argc) 
      {
        std::string sim_time_str(argv[i + 1]); // Convert the input to string
        size_t pi_pos = sim_time_str.find("pi"); // Find position of "pi"

        // If no "pi" found in argument
        if (pi_pos == std::string::npos) { 
          const char* input = argv[i + 1];
          char* endptr;
          sim_time = strtod(input, &endptr); // Simulation time as input if input is a double

          if (*endptr != '\0') { // If non-numerical character in argument
            help();
            throw std::invalid_argument("Invalid character encountered in simulation time argument. The only non-numerical characters allowed are 'pi'");
          }
        }  

        else {
          std::string x_str = sim_time_str.substr(0, pi_pos); // String between position 0 and pi_pos (ie any "coefficient" of pi)

          if (x_str == "") { // If no coefficient
            sim_time = M_PI;
          }
          else {
            double x = std::stod(x_str);
            sim_time = x * M_PI;
          }
        }
        i++;
      }


      else 
      {
        help();
        return 1;
      }
    }



    else if (arg == "-r" || arg == "--runtime") {
      if (i < argc) 
      {
        run_time = true;
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
    SolarSystem* solar_system = dynamic_cast<SolarSystem*>(systems[0]); // Cast the already defined InitialConditionGenerator Pointer to a SolarSystem pointer. 
    // i.e. you can use solar_system as a pointer to SolarSystem and use the other methods exclusive to the SolarSystem class


    if (run_time == false) {
      // Simulate solar system and it's evolution
      systems[0]->generateInitialConditions();
      solar_system->printMessages(); 
      printEnergyMessages(solar_system->getCelestialBodyList());



      try {
        evolutionOfSystem(solar_system->getCelestialBodyList(), dt, sim_time, soft_fac); // Run evolution simulation
      }
      catch(std::exception &e) {
        std::cout << e.what() << std::endl; // If dt, sim_time or soft_fac are not doubles
      }      
      solar_system->printMessages();
      printEnergyMessages(solar_system->getCelestialBodyList());
    }


    // If you want to measure runtime
    else {
      auto start_time = std::chrono::high_resolution_clock::now();
      systems[0]->generateInitialConditions();

      #ifdef DEBUG // Disable
      solar_system->printMessages(); 
      printEnergyMessages(solar_system->getCelestialBodyList());
      #endif

      try {
        evolutionOfSystem(solar_system->getCelestialBodyList(), dt, sim_time, soft_fac); // Run evolution simulation
      }
      catch(std::exception &e) {
        std::cout << e.what() << std::endl; 
      }       
      auto end_time = std::chrono::high_resolution_clock::now();
      solar_system->printMessages();
      printEnergyMessages(solar_system->getCelestialBodyList());




      int num_timesteps = std::ceil( sim_time / dt ); // Number of timesteps needed in simulation (round up to nearest int)

      double runtime = std::chrono::duration<double, std::milli>(end_time - start_time).count();
      std::cout << "The total simulation time is: " << runtime << " ms\n"
                << "The average time per timestep is: " << runtime/num_timesteps << " ms\n"         
      << std::endl;
    }

  }







  else if (randomsystem == true) {
    try 
    {
      systems[1] = new RandomSystem(num_bodies); // Create object of RandomSystem class
    }
    catch(std::exception &e)
    {
      std::cout << e.what() << std::endl; // If num_bodies is not int type
    }
    RandomSystem* random_system = dynamic_cast<RandomSystem*>(systems[1]); // Cast the already defined InitialConditionGenerator Pointer to a RandomSystem pointer



    if (run_time == false) {
      // Simulate random system and it's evolution:
      systems[1]->generateInitialConditions();
      printEnergyMessages(random_system->getCelestialBodyList());



      try {
        evolutionOfSystem(random_system->getCelestialBodyList(), dt, sim_time, soft_fac); // Run evolution simulation
      }
      catch(std::exception &e) {
        std::cout << e.what() << std::endl; 
      } 
      printEnergyMessages(random_system->getCelestialBodyList());
    }
    else {
      auto start_time = std::chrono::high_resolution_clock::now();
      systems[1]->generateInitialConditions();

      #ifdef DEBUG
      printEnergyMessages(random_system->getCelestialBodyList()); 
      #endif

      try {
        evolutionOfSystem(random_system->getCelestialBodyList(), dt, sim_time, soft_fac); // Run evolution simulation
      }
      catch(std::exception &e) {
        std::cout << e.what() << std::endl; 
      }       
      auto end_time = std::chrono::high_resolution_clock::now();
      printEnergyMessages(random_system->getCelestialBodyList());  




      int num_timesteps = std::ceil( sim_time / dt ); 

      double runtime = std::chrono::duration<double, std::milli>(end_time - start_time).count();
      std::cout << "The total simulation time is: " << runtime << " ms\n"
                << "The average time per timestep is: " << runtime/num_timesteps << " ms\n"         
      << std::endl;

      // Print number of max threads
      int thread_num_max = omp_get_max_threads();
      std::cout << "Max threads: " << thread_num_max << "\n" << std::endl;
    }


  }







  // If neither system is selected
  else if (solarsystem == false && randomsystem == false) {
    std::cout << "Did not select any system.\n" 
              << " ";
    help();
    return 1;
  }
  // If both systems are selected
  else if (solarsystem == true && randomsystem == true) {
    std::cout << "Both systems cannot be simulated at the same time.\n" 
              << " ";
    help();
    return 1;
  }


    
  return 0;
}

