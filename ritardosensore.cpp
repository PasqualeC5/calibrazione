#include <iostream>
#include <unistd.h>
#include <chrono>
#include <math.h>
#include "distance_sensor/include/InfraredSensor.hpp"
#include "meca500_ethercat_cpp/Robot.hpp"
#include "csvlogger/CsvLogger.hpp"

// Function to get current time in microseconds
uint64_t getCurrentTimeMicros()
{
    return std::chrono::duration_cast<std::chrono::microseconds>(
               std::chrono::system_clock::now().time_since_epoch())
        .count();
}

void delayMicroseconds(uint64_t microseconds)
{
    auto start = std::chrono::high_resolution_clock::now();
    auto end = start + std::chrono::microseconds(microseconds);

    while (std::chrono::high_resolution_clock::now() < end)
    {
        // Busy-wait loop
    }
}

int main()
{
    InfraredSensor sensor(InfraredSensor::USER_INPUT);

    /*robot, setup*/
    Robot robot(40, 240, 5000, "eth0", 0.0, 10);
    robot.reset_error();
    // robot.main();

    robot.set_conf(1, 1, -1);
    robot.move_pose(130, -170, 120, 90, 90, 0);
    robot.print_pose();

    /*files to write, setup*/
    CsvLogger input_logger("delay/velocity_control");
    input_logger.write("time, value\n");

    CsvLogger output_position_logger("delay/position_response");
    output_position_logger.write("time, value\n");

    CsvLogger sensor_output_logger("delay/sensor_response");
    sensor_output_logger.write("time, value\n");

    float velocity[6] = {0, 0, 0, 0, 0, 0};

    float currentDistance, currentPosition;

    double freq = 1; // frequenza del segnale di controllo in hertz

    /*time variables setup*/
    uint64_t currentTime, t0;
    double tc = 0.02; /** tempo di campionamento in secondi pari al
                       tempo di campionamento del sensore **/
    double t;         // current time in seconds

    velocity[0] = 0;

    const float Ta = 10; // time of analysis in seconds

    t0 = getCurrentTimeMicros(); // time to start analyzing response

    while (t < 10)
    {
        currentTime = getCurrentTimeMicros();
        t = (currentTime - t0) / 1e6;
        // input
        velocity[0] = 50 * sin(2 * M_PI * freq * t);

        robot.move_lin_vel_wrf(velocity);

        currentPosition = robot.get_position();
        currentDistance = sensor.getDistanceInMillimeters();

        // log data
        input_logger << t;
        input_logger << velocity[0];
        input_logger.end_row();

        sensor_output_logger << t;
        sensor_output_logger << currentDistance;
        sensor_output_logger.end_row();

        output_position_logger << t;
        output_position_logger << currentPosition;
        output_position_logger.end_row();

        delayMicroseconds(tc * 1e6 - (getCurrentTimeMicros() - currentTime));
    }
    // stop the robot
    velocity[0] = 0;
    robot.move_lin_vel_wrf(velocity);

    // save the data
    output_position_logger.close();
    sensor_output_logger.close();

    return 0;
}
