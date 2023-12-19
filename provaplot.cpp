
#include "../csvlogger/CsvLogger.hpp"
// #include "CsvLogger.hpp"
#include <time.h>
#include <pigpio.h>
#include <unistd.h>
#include <iostream>
#include <chrono>

int main(int argc, char *argv[])
{

    // Get the current time point
    auto currentTimePoint = std::chrono::high_resolution_clock::now();

    // Convert the time point to microseconds since the epoch
    auto currentTimeMicros = std::chrono::time_point_cast<std::chrono::microseconds>(currentTimePoint).time_since_epoch().count();

    gpioInitialise();

    /*files to write, setup*/
    CsvLogger input_logger("control/velocity_control.csv");
    input_logger.write("time, value\n");

    /*squarewave generation, setup*/
    double input_velocity_mms = 10; // 10mm/s    (amplitude)
    double period_s = 6;            // 6sec      (period)

    /*squarewawe T = 6s, A=10mm/s*/

    /*time variables setup*/
    auto startTime, currentTime, t0;
    t0 = currentTimeMicros; // time to start analysing response

    /*process*/
    while (true)
    {
        // input
        // robot.move_lin_vel_wrf(input_velocity_mms); //give 10mm/s or -10mm/s

        startTime = std::chrono::time_point_cast<std::chrono::microseconds>(currentTimePoint).time_since_epoch().count();

        while (1) // Run the loop for 3 seconds
        {
            // Check if 3 seconds have passed. Exit cycle if true
            currentTime = std::chrono::time_point_cast<std::chrono::microseconds>(currentTimePoint).time_since_epoch().count();

            if (currentTime - startTime >= (period_s * 1e6) / 2)
            {
                break; // Exit the loop after 3 seconds
            }

            // get datas
            input_logger << (currentTime - t0) / 1e6;
            input_logger << input_velocity_mms;
            input_logger.end_row();

            // short delay:
            usleep(1000);
        }

        input_velocity_mms = -input_velocity_mms;
    }
}
