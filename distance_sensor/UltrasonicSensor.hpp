#ifndef LASERDISTANCESENSOR_HPP
#define LASERDISTANCESENSOR_HPP

#include "DistanceSensor.hpp"
#include "../csvlogger/CsvLogger.hpp"
#include <pigpio.h>
#include <stdint.h>

#define SOUND_SPEED_MS 343
#define MAX_SENSOR_DISTANCE_CM 200 // Maximum sensor distance can be as high as 500cm, no reason to wait for ping longer than sound takes to travel this distance and back. Default=500
#define US_ROUNDTRIP_CM 57         // Microseconds (uS) it takes sound to travel round-trip 1cm (2cm total), uses integer to save compiled code space. Default=57
#define US_ROUNDTRIP_IN 146        // Microseconds (uS) it takes sound to travel round-trip 1 inch (2 inches total), uses integer to save compiled code space. Default=146
#define TRIGGER_WIDTH 30
#define MAX_SENSOR_DELAY 5800 // Maximum uS it takes for sensor to start the ping. Default=5800

class UltrasonicSensor : public DistanceSensor {
private:
    double distance;
    unsigned int MAX_SENSOR_DISTANCE_MM;
    unsigned user_gpio attachedTrigPin;
    unsigned user_gpio attachedEchoPin;
    unsigned int _maxEchoTime;



public:
    // Constructor
    UltrasonicSensor();

    // Implementation of virtual methods to get distance in meters, centimeters, and millimeters
    float getDistanceInMeters() const override;
    float getDistanceInCentimeters() const override;
    float getDistanceInMillimeters() const override;
};

#endif // LASERDISTANCESENSOR_HPP
