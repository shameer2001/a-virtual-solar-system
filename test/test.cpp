#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "particle.hpp"
#include "solarSystem.hpp"
#include "randomParticleSystem.hpp"
using Catch::Matchers::WithinRel;

TEST_CASE( "Particle sets mass correctly", "[particle]" ) {
    Eigen::Vector3d pos_test(0.0, 0.3, 0.3);
    Eigen::Vector3d vel_test(0.0, 0.0, 0.0);
    Eigen::Vector3d acc_test(0.0, 0.0, 0.0);

    Particle p{3.14, pos_test, vel_test, acc_test};
    REQUIRE_THAT( p.getMass(), WithinRel(3.14, 0.01) );
}



TEST_CASE( "Particle calculates velocity and postion correctly with 0 acceleration", "[particle]" ) {
    Eigen::Vector3d pos_test(2.3, 2.3, 2.3);
    Eigen::Vector3d vel_test(4.0, 4.0, 4.0);
    Eigen::Vector3d acc_test(0.0, 0.0, 0.0);

    Particle p{3.14, pos_test, vel_test, acc_test};
    p.update(2.0);

    Eigen::Vector3d pos_exp(10.3, 10.3, 10.3); // Using equation and calculator
    Eigen::Vector3d vel_exp(4, 4, 4); // Velocity shouldn't change with 0 acceleration

    REQUIRE( p.getPosition().isApprox(pos_exp) );
    REQUIRE( p.getVelocity().isApprox(vel_exp) );

}



TEST_CASE( "Particle calculates velocity and postion correctly with constant acceleration", "[particle]" ) {
    Eigen::Vector3d pos_test(2.3, 2.3, 2.3);
    Eigen::Vector3d vel_test(4.0, 4.0, 4.0);
    Eigen::Vector3d acc_test(1.0, 1.0, 1.0); 

    Particle p{3.14, pos_test, vel_test, acc_test};
    p.update(2.0);

    Eigen::Vector3d pos_exp(10.3, 10.3, 10.3); 
    Eigen::Vector3d vel_exp(6.0, 6.0, 6.00); 

    REQUIRE( p.getPosition().isApprox(pos_exp) );
    REQUIRE( p.getVelocity().isApprox(vel_exp) );

}




TEST_CASE( "Particle calculates velocity and postion correctly with artificial acceleration", "[particle]" ) {
    Eigen::Vector3d pos_test(1.0, 0.0, 0.0);
    Eigen::Vector3d vel_test(0.0, 1.0, 0.0);
    Eigen::Vector3d acc_test = -1 * pos_test; // Artificial acceleration

    Particle p{3.14, pos_test, vel_test, acc_test};

    double dt = 0.001;
    double sim_time = 0.0;

    // Loop till 2pi in .001 increments and update acceleration each time:
    for (sim_time = 0.0; sim_time < 2 * M_PI; sim_time += dt) {
        p.update(dt);

        acc_test = -1 * p.getPosition();
        p.updateAcceleration(acc_test);
    }

    // Initial and final position, velocity should be approximately (.001 precision here) equal:
    REQUIRE( p.getPosition().isApprox(pos_test, 1e-2) ); 
    REQUIRE( p.getVelocity().isApprox(vel_test, 1e-2) );

}




TEST_CASE("The gravitational force/acceleration between two particles is as expected: calcAcceleration function", "[particle]") {

    SECTION("Test case 1; simple", "[particles]") {
        Eigen::Vector3d pos_test1(0.0, 0.0, 0.0);
        Eigen::Vector3d vel_test1(0.0, 0.0, 0.0);
        Eigen::Vector3d acc_test1(1.0, 1.0, 1.0);
        double mass_test1 = 1;

        Eigen::Vector3d pos_test2(1.0, 1.0, 1.0);
        Eigen::Vector3d vel_test2(0.0, 0.0, 0.0);
        Eigen::Vector3d acc_test2(0.0, 0.0, 0.0);
        double mass_test2 = 1;

        Particle p1(mass_test1, pos_test1, vel_test1, acc_test1);
        Particle p2(mass_test2, pos_test2, vel_test2, acc_test2);

        Eigen::Vector3d acceleration = calcAcceleration(p1, p2);
        Eigen::Vector3d acc_exp(1.0/pow(3.0, 3.0/2.0), 1.0/pow(3.0, 3.0/2.0), 1.0/pow(3.0, 3.0/2.0)); // Vector contents calculated by hand using equation

        REQUIRE( acceleration.isApprox(acc_exp) );
    }


    SECTION("Test case 2; different xyz", "[particles]") {
        Eigen::Vector3d pos_test1(0.0, 0.0, 0.0);
        Eigen::Vector3d vel_test1(2.0, 3.0, 1.0);
        Eigen::Vector3d acc_test1(4.0, 0.0, 1.0);
        double mass_test1 = 4.0;

        Eigen::Vector3d pos_test2(1.0, 1.0, 2.0);
        Eigen::Vector3d vel_test2(4.0, 5.0, 7.0);
        Eigen::Vector3d acc_test2(1.0, 2.0, 3.0);
        double mass_test2 = 1.0;

        Particle p1(mass_test1, pos_test1, vel_test1, acc_test1);
        Particle p2(mass_test2, pos_test2, vel_test2, acc_test2);

        Eigen::Vector3d acceleration = calcAcceleration(p1, p2);
        Eigen::Vector3d acc_exp( 1.0/pow(6, 3.0/2.0), 1.0/pow(6, 3.0/2.0), 2.0/pow(6, 3.0/2.0) );

        REQUIRE( acceleration.isApprox(acc_exp) );
    }



    SECTION("Test case 3; negative position", "[particles]") {
        Eigen::Vector3d pos_test1(-4.0, -2.0, -5.0);
        Eigen::Vector3d vel_test1(2.0, 3.0, 1.0);
        Eigen::Vector3d acc_test1(4.0, 0.0, 1.0);
        double mass_test1 = 4.0;

        Eigen::Vector3d pos_test2(-1.0, -1.0, -2.0);
        Eigen::Vector3d vel_test2(4.0, 5.0, 7.0);
        Eigen::Vector3d acc_test2(1.0, 2.0, 3.0);
        double mass_test2 = 1.0;

        Particle p1(mass_test1, pos_test1, vel_test1, acc_test1);
        Particle p2(mass_test2, pos_test2, vel_test2, acc_test2);

        Eigen::Vector3d acceleration = calcAcceleration(p1, p2);
        Eigen::Vector3d acc_exp( 3.0/pow(19.0, 3.0/2.0), 1.0/pow(19.0, 3.0/2.0), 3.0/pow(19.0, 3.0/2.0) );

        REQUIRE( acceleration.isApprox(acc_exp) );
    }



    SECTION("Test case 4; negative positive", "[particles]") {
        Eigen::Vector3d pos_test1(-4.0, -2.0, -5.0);
        Eigen::Vector3d vel_test1(2.0, 3.0, 1.0);
        Eigen::Vector3d acc_test1(4.0, 0.0, 1.0);
        double mass_test1 = 4.0;

        Eigen::Vector3d pos_test2(1.0, 1.0, 2.0);
        Eigen::Vector3d vel_test2(4.0, 5.0, 7.0);
        Eigen::Vector3d acc_test2(1.0, 2.0, 3.0);
        double mass_test2 = 1.0;

        Particle p1(mass_test1, pos_test1, vel_test1, acc_test1);
        Particle p2(mass_test2, pos_test2, vel_test2, acc_test2);

        Eigen::Vector3d acceleration = calcAcceleration(p1, p2);
        Eigen::Vector3d acc_exp( 5.0/pow(83.0, 3.0/2.0), 3.0/pow(83.0, 3.0/2.0), 7.0/pow(83.0, 3.0/2.0) );

        REQUIRE( acceleration.isApprox(acc_exp) );
    }

}








TEST_CASE("Ensure that a list of particles that includes itself to a particle will not add any acceleration: sumAccelerations function", "[particle]") {

    Eigen::Vector3d pos_test1(0.0, 0.0, 0.0);
    Eigen::Vector3d vel_test1(2.0, 3.0, 1.0);
    Eigen::Vector3d acc_test1(-4.0, -2.0, -1.0);
    double mass_test1 = 4.0;

    Eigen::Vector3d pos_test2(1.0, 1.0, 2.0);
    Eigen::Vector3d vel_test2(4.0, 5.0, 7.0);
    Eigen::Vector3d acc_test2(-1.0, -2.0, -3.0);
    double mass_test2 = 1.0;

    Eigen::Vector3d pos_test3(2.0, 2.0, 2.0);
    Eigen::Vector3d vel_test3(5.0, 5.0, 5.0);
    Eigen::Vector3d acc_test3(1.0, 2.0, 3.0);
    double mass_test3 = 3.0;


    Particle p1{mass_test1, pos_test1, vel_test1, acc_test1};
    Particle p2{mass_test2, pos_test2, vel_test2, acc_test2};
    Particle p3{mass_test3, pos_test3, vel_test3, acc_test3};

    auto p1_ptr = std::make_shared<Particle>(p1);
    auto p2_ptr = std::make_shared<Particle>(p2);
    auto p3_ptr = std::make_shared<Particle>(p3);

    std::vector<std::shared_ptr<Particle>> list_with_self{p1_ptr, p2_ptr, p3_ptr};
    std::vector<std::shared_ptr<Particle>> list_wout_self{p2_ptr, p3_ptr}; // wout = without

    sumAccelerations(list_with_self, p1);
    const Particle p1_with_self = p1;

    sumAccelerations(list_wout_self, p1);
    const Particle p1_wout_self = p1;


    REQUIRE( p1_with_self.getAcceleration() == p1_wout_self.getAcceleration() );


}





TEST_CASE("Ensure a particle with two equally sized particles an equal distance away will have 0 acceleration: sumAccelerations function", "[particle]") {

    Eigen::Vector3d pos_test1(0.0, 0.0, 0.0);
    Eigen::Vector3d vel_test1(2.0, 3.0, 1.0);
    Eigen::Vector3d acc_test1(-4.0, -2.0, -1.00);
    double mass_test1 = 4.0;

    Eigen::Vector3d pos_test2(1.0, 0.0, 0.0);
    Eigen::Vector3d vel_test2(5.0, 0.0, 0.0);
    Eigen::Vector3d acc_test2(2.0, 0.0, 0.0);
    double mass_test2 = 2.0;

    Eigen::Vector3d pos_test3(-1.0, 0.0, 0.0);
    Eigen::Vector3d vel_test3(5.0, 0.0, 0.0);
    Eigen::Vector3d acc_test3(2.0, 0.0, 0.0);
    double mass_test3 = 2.0;


    Particle p1{mass_test1, pos_test1, vel_test1, acc_test1};
    Particle p2{mass_test2, pos_test2, vel_test2, acc_test2};
    Particle p3{mass_test3, pos_test3, vel_test3, acc_test3};

    auto p1_ptr = std::make_shared<Particle>(p1);
    auto p2_ptr = std::make_shared<Particle>(p2);
    auto p3_ptr = std::make_shared<Particle>(p3);

    std::vector<std::shared_ptr<Particle>> list{p1_ptr, p2_ptr, p3_ptr};

    sumAccelerations(list, p1);
    Eigen::Vector3d acc_zero(0.0, 0.0, 0.0);


    REQUIRE( p1.getAcceleration() == acc_zero );
}









TEST_CASE("Test initial condition generator class", "[SolarSystem]") {
    SolarSystem solar_system;
    solar_system.generateInitialConditions();

    SECTION("Ensure Sun is instantiated correctly", "[SolarSystem]") {
        double mass_exp = 1.0;
        Eigen::Vector3d pos_exp{0.0, 0.0, 0.0};
        Eigen::Vector3d vel_exp{0.0, 0.0, 0.0};
        Eigen::Vector3d acc_exp{0.0, 0.0, 0.0};

        Particle sun = *(solar_system.getCelestialBodyList()[0]);

        REQUIRE( sun.getMass() == mass_exp );
        REQUIRE( sun.getPosition() == pos_exp );
        REQUIRE( sun.getVelocity() == vel_exp );
        REQUIRE( sun.getAcceleration() == acc_exp );
    }


    SECTION("Ensure size of list is correct", "[SolarSystem]") {

        REQUIRE( solar_system.getCelestialBodyList().size() == 9 );
    }


    SECTION("Ensure mass of planets is correct", "[SolarSystem]") {

        double mercury_mass = solar_system.getCelestialBodyList()[1]->getMass();
        double venus_mass = solar_system.getCelestialBodyList()[2]->getMass();
        double earth_mass = solar_system.getCelestialBodyList()[3]->getMass();
        double mars_mass = solar_system.getCelestialBodyList()[4]->getMass();
        double jupiter_mass = solar_system.getCelestialBodyList()[5]->getMass();
        double saturn_mass = solar_system.getCelestialBodyList()[6]->getMass();
        double uranus_mass = solar_system.getCelestialBodyList()[7]->getMass();
        double neptune_mass = solar_system.getCelestialBodyList()[8]->getMass();

        double mercury_mass_exp = 1.0/6023600.0;
        double venus_mass_exp = 1.0/408524.0;
        double earth_mass_exp = 1.0/332946.038;
        double mars_mass_exp = 1.0/3098710.0;
        double jupiter_mass_exp = 1.0/1047.55;
        double saturn_mass_exp = 1.0/3499.0;
        double uranus_mass_exp = 1.0/22962.0;
        double neptune_mass_exp = 1.0/19352.0;


        REQUIRE( mercury_mass == mercury_mass_exp );
        REQUIRE( venus_mass == venus_mass_exp );
        REQUIRE( earth_mass == earth_mass_exp );
        REQUIRE( mars_mass == mars_mass_exp );
        REQUIRE( jupiter_mass == jupiter_mass_exp );
        REQUIRE( saturn_mass == saturn_mass_exp );
        REQUIRE( uranus_mass == uranus_mass_exp );
        REQUIRE( neptune_mass == neptune_mass_exp );

    }

}





TEST_CASE("Check that solar system evolves correctly", "[SolarSystem]") {
    SolarSystem solar_system;
    solar_system.generateInitialConditions();

    std::shared_ptr<Particle> sun = solar_system.getCelestialBodyList()[0];



    SECTION("Check that system evolves correctly for sun and 1 body", "[SolarSystem]") {

        Eigen::Vector3d pos_test(1.0, 1.0, 1.0);
        Eigen::Vector3d vel_test(1.0, 1.0, 1.0);
        Eigen::Vector3d acc_test(0.0, 0.0, 0.0);
        double mass_test = 0.5; // Mass of body is half of sun's

        Particle body_test(mass_test, pos_test, vel_test, acc_test);

        std::vector<std::shared_ptr<Particle>> sun_and_body{sun, std::make_shared<Particle>(body_test)};
        SolarSystem small_system(sun_and_body);

        evolutionOfSystem(small_system.getCelestialBodyList(), 0.1, 0.1); // After one time steps
        const Eigen::Vector3d body_pos_final = small_system.getCelestialBodyList()[1]->getPosition();
        const Eigen::Vector3d body_vel_final = small_system.getCelestialBodyList()[1]->getVelocity();
        const Eigen::Vector3d body_acc_final = small_system.getCelestialBodyList()[1]->getAcceleration();

        const Eigen::Vector3d sun_pos_final = small_system.getCelestialBodyList()[0]->getPosition();
        const Eigen::Vector3d sun_vel_final = small_system.getCelestialBodyList()[0]->getVelocity();
        const Eigen::Vector3d sun_acc_final = small_system.getCelestialBodyList()[0]->getAcceleration();


        // Expected values calculated by hand:

        Eigen::Vector3d body_acc_exp(-1.0/pow(3, 3.0/2.0), -1.0/pow(3, 3.0/2.0), -1.0/pow(3, 3.0/2.0));
        Eigen::Vector3d body_pos_exp(1.1, 1.1, 1.1);
        Eigen::Vector3d body_vel_exp(1 + -0.1/pow(3, 3.0/2.0), 1 + -0.1/pow(3, 3.0/2.0), 1 + -0.1/pow(3, 3.0/2.0));

        Eigen::Vector3d sun_acc_exp(0.5/pow(3, 3.0/2.0), 0.5/pow(3, 3.0/2.0), 0.5/pow(3, 3.0/2.0));
        Eigen::Vector3d sun_pos_exp(0.0, 0.0, 0.0); // Position should be same since position is taken relative to sun
        Eigen::Vector3d sun_vel_exp(0.05/pow(3, 3.0/2.0), 0.05/pow(3, 3.0/2.0), 0.05/pow(3, 3.0/2.0));


        REQUIRE( sun_acc_final.isApprox(sun_acc_exp, 1e-2) );
        REQUIRE( sun_pos_final.isApprox(sun_pos_exp) );
        REQUIRE( sun_vel_final.isApprox(sun_vel_exp, 1e-2) );

        REQUIRE( body_acc_final.isApprox(body_acc_exp, 1e-2) );
        REQUIRE( body_pos_final.isApprox(body_pos_exp, 1e-2) );
        REQUIRE( body_vel_final.isApprox(body_vel_exp, 1e-2) );
    }


    SECTION("Confirm that earth initial and final position is similar over 2pi time (one year)", "[SolarSystem]") {

        std::shared_ptr<Particle> earth = solar_system.getCelestialBodyList()[3];
        const Eigen::Vector3d earth_pos_initial = earth->getPosition();

        std::vector<std::shared_ptr<Particle>> sun_and_earth{sun, earth};
        SolarSystem small_system(sun_and_earth);

        evolutionOfSystem(small_system.getCelestialBodyList(),0.01, 2 * M_PI);
        const Eigen::Vector3d earth_pos_final = small_system.getCelestialBodyList()[1]->getPosition();

        REQUIRE( earth_pos_final.isApprox(earth_pos_initial, 0.6) ); // Close to original position (but slightly moved due to gravitational force of sun)
    }


    SECTION("Confirm that earth initial and final position is similar for unnecessarily small dt over one year", "[SolarSystem]") {

        std::shared_ptr<Particle> earth = solar_system.getCelestialBodyList()[3];
        const Eigen::Vector3d earth_pos_initial = earth->getPosition();

        std::vector<std::shared_ptr<Particle>> sun_and_earth{sun, earth};
        SolarSystem small_system(sun_and_earth);

        evolutionOfSystem(small_system.getCelestialBodyList(), 0.0001, 2 * M_PI);
        const Eigen::Vector3d earth_pos_final = small_system.getCelestialBodyList()[1]->getPosition();

        REQUIRE( earth_pos_final.isApprox(earth_pos_initial, 1e-2) );
    }
}



TEST_CASE("Testing energy functions for SolarSystem class", "[SolarSystem]") {
    SolarSystem solar_system;

    // Simulate solar system and it's evolution
    solar_system.generateInitialConditions();
    double kin_before = totalKineticEnergy(solar_system.getCelestialBodyList());
    double pot_before = totalPotentialEnergy(solar_system.getCelestialBodyList());
    double tot_before = totalEnergy(solar_system.getCelestialBodyList());

    evolutionOfSystem(solar_system.getCelestialBodyList(), 0.001, 200 * M_PI); // Run evolution simulation
    double kin_after = totalKineticEnergy(solar_system.getCelestialBodyList());
    double pot_after = totalPotentialEnergy(solar_system.getCelestialBodyList());
    double tot_after = totalEnergy(solar_system.getCelestialBodyList());


    // Expected values calculated by hand
    double kin_before_exp = 0.000113441;
    double pot_before_exp = -0.000224712;
    double tot_before_exp = -0.000113489;
    double kin_after_exp = 0.0001134455;
    double pot_after_exp =  -0.000222011; 
    double tot_after_exp = -0.000113557;

    REQUIRE_THAT( kin_before, WithinRel(kin_before_exp, 0.1) );
    REQUIRE_THAT( pot_before, WithinRel(pot_before_exp, 0.1) );
    REQUIRE_THAT( tot_before, WithinRel(tot_before_exp, 0.1) );
    REQUIRE_THAT( kin_after, WithinRel(kin_after_exp, 0.1) );
    REQUIRE_THAT( pot_after, WithinRel(pot_after_exp, 0.1) );
    REQUIRE_THAT( tot_after, WithinRel(tot_after_exp, 0.1) );

}



TEST_CASE("Testing energy functions for RandomSystem class", "[RandomSystem]") {
    RandomSystem random_system(8);

    // Simulate random system and it's evolution
    random_system.generateInitialConditions();
    double kin_before = totalKineticEnergy(random_system.getCelestialBodyList());
    double pot_before = totalPotentialEnergy(random_system.getCelestialBodyList());
    double tot_before = totalEnergy(random_system.getCelestialBodyList());

    evolutionOfSystem(random_system.getCelestialBodyList(), 0.01, M_PI); // Run evolution simulation
    double kin_after = totalKineticEnergy(random_system.getCelestialBodyList());
    double pot_after = totalPotentialEnergy(random_system.getCelestialBodyList());
    double tot_after = totalEnergy(random_system.getCelestialBodyList());

    // Expected values calculated by hand
    double kin_before_exp = 0.000156534;
    double pot_before_exp = -0.000312047;
    double tot_before_exp = -0.000154055;
    double kin_after_exp = 0.000150578;
    double pot_after_exp =  -0.000311248; 
    double tot_after_exp = -0.00015781;

    REQUIRE_THAT( kin_before, WithinRel(kin_before_exp, 0.1) );
    REQUIRE_THAT( pot_before, WithinRel(pot_before_exp, 0.1) );
    REQUIRE_THAT( tot_before, WithinRel(tot_before_exp, 0.1) );
    REQUIRE_THAT( kin_after, WithinRel(kin_after_exp, 0.1) );
    REQUIRE_THAT( pot_after, WithinRel(pot_after_exp, 0.1) );
    REQUIRE_THAT( tot_after, WithinRel(tot_after_exp, 0.1) );

}