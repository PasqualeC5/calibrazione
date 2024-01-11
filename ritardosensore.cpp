#include <iostream>
#include <unistd.h>
#include <chrono>
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
    CsvLogger output_position_logger("delay/position_response");
    output_position_logger.write("time, value\n");

    CsvLogger sensor_output_logger("delay/sensor_response");
    sensor_output_logger.write("time, value\n");

    /*squarewave generation, setup*/
    float input_velocity_mms = 10; // 10mm/s    (amplitude)
    double period_s = 3;           // 6sec      (period)
    float velocity[6] = {0, 0, 0, 0, 0, 0};
    /*squarewawe T = 6s, A=10mm/s*/

    /*time variables setup*/
    uint64_t startTime, currentTime, t0;
    t0 = getCurrentTimeMicros(); // time to start analyzing response

    velocity[0] = input_velocity_mms;
    int cycles = 0;

    while (cycles < 3)
    {
        // input

        startTime = getCurrentTimeMicros();
        currentTime = getCurrentTimeMicros();
        robot.move_lin_vel_wrf(velocity); // give 10mm/s or -10mm/s

        while (currentTime - startTime <= period_s * 1e6) // Run the loop for 3 seconds
        {

            // Check if 3 seconds passed. Exit cycle if true
            currentTime = getCurrentTimeMicros();
            // get data
            sensor_output_logger << (currentTime - t0) / 1e6;
            sensor_output_logger << sensor.getDistanceInMillimeters();
            sensor_output_logger.end_row();

            output_position_logger << (currentTime - t0) / 1e6;
            output_position_logger << robot.get_position();
            output_position_logger.end_row();
        }
        //stop the robot
        velocity[0] = 0;
        robot.move_lin_vel_wrf(velocity);

        std::cout << "Waiting for 1 second" << std::endl;
        delayMicroseconds(1e6);

        input_velocity_mms = - input_velocity_mms;
        velocity[0] = input_velocity_mms;

        cycles++;
    }
    // stop the robot
    velocity[0] = 0;
    robot.move_lin_vel_wrf(velocity);

    // save the data
    output_position_logger.close();
    sensor_output_logger.close();

    return 0;
}
