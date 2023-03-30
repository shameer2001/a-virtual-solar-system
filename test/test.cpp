#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "particle.hpp"
#include <iostream>
using Catch::Matchers::WithinRel;

TEST_CASE( "Particle sets mass correctly", "[particle]" ) {
    Particle p{3.14};
    REQUIRE_THAT( p.getMass(), WithinRel(3.14, 0.01) );
}



TEST_CASE( "Particle calculates velocity and postion correctly with 0 acceleration", "[particle]" ) {
    Eigen::Vector3d pos_test(2.3, 2.3, 2.3);
    Eigen::Vector3d vel_test(4, 4, 4);
    Eigen::Vector3d acc_test(0, 0, 0);

    Particle p{3.14, pos_test, vel_test, acc_test};
    p.update(2);

    Eigen::Vector3d pos_exp(10.3, 10.3, 10.3); // Using equation and calculator
    Eigen::Vector3d vel_exp(4, 4, 4); // Velocity shouldn't change with 0 acceleration

    REQUIRE( p.getPosition().isApprox(pos_exp) );
    REQUIRE( p.getVelocity().isApprox(vel_exp) );

}



TEST_CASE( "Particle calculates velocity and postion correctly with constant acceleration", "[particle]" ) {
    Eigen::Vector3d pos_test(2.3, 2.3, 2.3);
    Eigen::Vector3d vel_test(4, 4, 4);
    Eigen::Vector3d acc_test(1, 1, 1); 

    Particle p{3.14, pos_test, vel_test, acc_test};
    p.update(2);

    Eigen::Vector3d pos_exp(10.3, 10.3, 10.3); 
    Eigen::Vector3d vel_exp(6, 6, 6); 

    REQUIRE( p.getPosition().isApprox(pos_exp) );
    REQUIRE( p.getVelocity().isApprox(vel_exp) );

}




TEST_CASE( "Particle calculates velocity and postion correctly with artificial acceleration", "[particle]" ) {
    Eigen::Vector3d pos_test(1, 0, 0);
    Eigen::Vector3d vel_test(0, 1, 0);
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




