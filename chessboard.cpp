#include "distance_sensor/include/DistanceSensor.hpp"
#include "distance_sensor/include/UltrasonicSensor.hpp"
#include "distance_sensor/include/InfraredSensor.hpp"
#include "meca500_ethercat_cpp/Robot.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    InfraredSensor sensor(InfraredSensor::USER_INPUT);
    Robot robot(100, 200, 5000, "eth0", 0.0, 10);
    robot.reset_error();
    // robot.main();
    robot.set_conf(1, 1, -1);
    robot.move_pose(130, -170, 120, 90, 0, 0);
    robot.print_pose();
    float velocity[6] = {0, 0, 0, 0, 0, 0};
    float position[6];

    

}
