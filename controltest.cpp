#include "distance_sensor/include/DistanceSensor.hpp"
#include "distance_sensor/include/UltrasonicSensor.hpp"
#include "distance_sensor/include/InfraredSensor.hpp"
#include "meca500_ethercat_cpp/Robot.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    InfraredSensor sensor(InfraredSensor::USER_INPUT);
    Robot robot(-30, 200, 5000, "eth0", 0.0, 100);
    robot.reset_error();
    // robot.main();
    robot.set_conf(1, 1, -1);
    robot.move_pose(130, -170, 120, 90, 90, 0);
    robot.print_pose();
    float velocity[6] = {0, 0, 0, 0, 0, 0};
    float position[6];

    float distance;
    while (true)
    {
        robot.get_pose(position);
        distance = sensor.getDistanceInMillimeters();
        cout << "Measured distance: " << distance << endl;
        if (distance < 255)
        {
            if (distance < 50)
            {
                if (position[0] < robot.POS_LIMIT_INF)
                    velocity[1] = 0;
                else
                    velocity[1] = -10;
                robot.move_lin_vel_trf(velocity);
            }
            else if (distance > 50)
            {
                if (position[0] < robot.POS_LIMIT_SUP)
                    velocity[1] = 0;
                else
                    velocity[1] = 10;
                robot.move_lin_vel_trf(velocity);
            }
        }
        else
        {
            velocity[1] = 0;
            robot.move_lin_vel_trf(velocity);
        }
    }
}
