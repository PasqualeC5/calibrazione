#include <iostream>
#include <unistd.h>
#include <chrono>
#include <math.h>
#include "distance_sensor/include/InfraredSensor.hpp"
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

int main(int argc, char *argv[])
{
    float distance;
    DistanceSensor *sensor = nullptr;
    sensor = new InfraredSensor(InfraredSensor::USER_INPUT);
    if (argc >= 3)
    {

        sensor->useCalibrationCurve(stoi(argv[1]), stoi(argv[2]));
    }

    uint64_t currentTime, t;
    /*files to write, setup*/
    // CsvLogger output_logger("delay/ritardo_istruzione");
    // output_logger.write("value\n");

    for (int i = 0; i < 100; i++)
    {
        currentTime = getCurrentTimeMicros();
        distance = sensor->getDistanceInMillimeters();
        t = getCurrentTimeMicros() - currentTime;
        // output_logger << t;
        // output_logger.end_row();
        cout << distance << endl;
        // delayMicroseconds(0.05*1e6);
        delayMicroseconds(0.5 * 1e6);
    }

    // output_logger.close();

    return 0;
}
