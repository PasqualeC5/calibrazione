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
#define TRIGGER_WIDTH 15
#define MAX_SENSOR_DELAY 5800 // Maximum uS it takes for sensor to start the ping. Default=5800

class UltrasonicSensor : public DistanceSensor {
private:
    unsigned int MAX_SENSOR_DISTANCE_MM;
    uint8_t attachedTrigPin;
    uint8_t attachedEchoPin;
    unsigned int _maxEchoTime;



public:
    // Constructor
    UltrasonicSensor(uint8_t attachedTrigPin, uint8_t attachedEchoPin);
    // Implementation of virtual methods to get distance in meters, centimeters, and millimeters
    float getDistanceInMeters() override;
    float getDistanceInCentimeters() override;
    float getDistanceInMillimeters() override;

};

#endif // LASERDISTANCESENSOR_HPP
