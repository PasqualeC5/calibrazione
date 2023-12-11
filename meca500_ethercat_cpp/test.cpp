#include "Robot.hpp"

int main(int argc, char *argv[])
{
    Robot robot(40,240 5000, "eth0", 0.0, 100);
    robot.reset_error();
    // robot.main();
    robot.set_conf(1, 1, -1);
    robot.move_pose(130, -170, 120, 90, 90, 0);
    robot.print_pose();
    while (true)
    {
        static float speed = 10e-3;
        speed *= -1;
        robot.move_lin_vel_wrf(speed);
        robot.print_pose();
        usleep(1e+6);
    }
}
