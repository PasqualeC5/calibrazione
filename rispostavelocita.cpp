#include "../distance_sensor/include/DistanceSensor.hpp"
#include "../distance_sensor/include/UltrasonicSensor.hpp"
#include "../distance_sensor/include/InfraredSensor.hpp"
#include "../meca500_ethercat_cpp/Robot.hpp"

int main(int argc, char *argv[])
{
    /*robot setup*/
    Robot robot(40, 240, 5000, "eth0", 0.0, 10);
    robot.reset_error();
    // robot.main();

    robot.set_conf(1, 1, -1);
    robot.move_pose(130, -170, 120, 90, 90, 0);
    robot.print_pose();


    /*velocity control on x-axis*/
    double velocity = 10;   //10mm/s 

    while (true)
    {
        //squarewawe T = 6ms, A=10mm/s

        robot.move_lin_vel_wrf(velocity);
            //here I have to take data -> getvelocity
        usleep(3e+6);                       //3s

            //here I have to take data -> get
        robot.move_lin_vel_wrf(-velocity);
        usleep(3e+6);                       //3s
    }
}
