
#include "meca500_ethercat_cpp/Robot.hpp"
#include "csvlogger/CsvLogger.hpp"
#include <pigpio.h>
#include <unistd.h>
#include <iostream>
#include <chrono>

int main(int argc, char *argv[])
{
    /*robot, setup*/
    Robot robot(40, 240, 5000, "eth0", 0.0, 10);
    robot.reset_error();
    // robot.main();

    robot.set_conf(1, 1, -1);
    robot.move_pose(130, -170, 120, 90, 90, 0);
    robot.print_pose();

    /*files to write, setup*/
    CsvLogger input_logger("control/velocity_control");
    input_logger.write("time, value\n");

    CsvLogger output_logger("control/velocity_response");
    output_logger.write("time, value\n");

    /*squarewave generation, setup*/
    float input_velocity_mms = 10; // 10mm/s    (amplitude)
    double period_s = 6;           // 6sec      (period)
    float velocity[6] = {0, 0, 0, 0, 0, 0};
    /*squarewawe T = 6s, A=10mm/s*/

    /*time variables setup*/
    uint32_t startTime, currentTime, t0;
    auto t0 = std::chrono::high_resolution_clock::now();

    /*process*/
    while (true)
    {
        velocity[0] = input_velocity_mms;
        // input
        robot.move_lin_vel_wrf(velocity); // give 10mm/s or -10mm/s

        auto startTime = std::chrono::high_resolution_clock::now();

        // Your code here

        // Record the end time

        // Ou
        while (1) // Run the loop for 3 seconds
        {
            // Check if 3 secone passed. Exit cycle if true
            auto endTime = std::chrono::high_resolution_clock::now();

            // Calculate the duration between start and end times
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

            if (duration.count() >= period_s / 2 * 1e3)
            {
                break; // Exit the loop after 3 seconds
            }

            // get datas
            input_logger << (currentTime - t0);
            input_logger << input_velocity_mms;
            input_logger.end_row();

            output_logger << (currentTime - t0);
            output_logger << robot.get_velocity();
            output_logger.end_row();

            // short delay:
            usleep(1000);
        }

        input_velocity_mms = -input_velocity_mms;
    }
}
