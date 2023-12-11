#include "Robot.hpp"

int main(int argc, char *argv[])
{
    Robot robot(-30, 200, 5000, "eth0", 0.0, 100);
    robot.reset_error();
    // robot.main();
    robot.set_conf(1, 1, -1);
    robot.move_pose(130, -170, 120, 90, 90, 0);
    robot.print_pose();
    double velocity = 10e-6;
    while (true)
    {
        robot.move_lin_vel_trf(velocity, -170, 120, 90, 90, 0);
        usleep(3e+6);
        robot.move_pose(-velocity, -170, 120, 90, 90, 0);
        usleep(3e+6);
    }
}
