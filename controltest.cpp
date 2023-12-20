#include "distance_sensor/include/DistanceSensor.hpp"
#include "distance_sensor/include/UltrasonicSensor.hpp"
#include "distance_sensor/include/InfraredSensor.hpp"
#include "meca500_ethercat_cpp/Robot.hpp"

int main(int argc, char *argv[])
{
    Robot robot(-30, 200, 5000, "eth0", 0.0, 100);
    robot.reset_error();
    // robot.main();
    robot.set_conf(1, 1, -1);
    robot.move_pose(130, -170, 120, 90, 90, 0);
    robot.print_pose();
    float velocity[6] = {0, 0, 0, 0, 0, 0};
    float position[6];
    float vel = 5;
    velocity[0] = vel;
    int i = 0;
    float setpoint = 50 InfraredSensor sensor(InfraredSensor::USER_INPUT);
    float distance;
    while (true)
    {
        robot.get_position(position);
        distance = sensor.getDistanceInMillimeters();
        if (distance < 255)
        {
            if (distance < 50)
            {
                if (position[3] < robot.POS_LIMIT_INF)
                    velocity[2] = 0;
                else
                    velocity[2] = -10;
                robot.move_lin_vel_trf(velocity);
            }
            else if (distance > 50)
            {
                if (position[3] < robot.POS_LIMIT_SUP)
                    velocity[2] = 0;
                else
                    velocity[2] = 10;
                robot.move_lin_vel_trf(velocity);
            }
        }
        else
        {
            velocity[2] = 0;
            robot.move_lin_vel_trf(velocity);
        }
    }
}
