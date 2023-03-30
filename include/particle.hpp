#include <Eigen/Core>

class Particle {
    public:
        // Constructors:
        Particle(double in_mass);
        Particle(double in_mass, Eigen::Vector3d& in_pos, Eigen::Vector3d& in_vel, Eigen::Vector3d& in_acc); 

        // get functions:
        Eigen::Vector3d getPosition() const;
        Eigen::Vector3d getVelocity() const;
        double getMass() const;

        // Update functions:
        Eigen::Vector3d updateAcceleration(Eigen::Vector3d& acc);
        void update(double dt);

    private:
        double mass;
        Eigen::Vector3d position;
        Eigen::Vector3d velocity;
        Eigen::Vector3d acceleration;
        

};