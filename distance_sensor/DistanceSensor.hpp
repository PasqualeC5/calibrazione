#ifndef DISTANCESENSOR_HPP
#define DISTANCESENSOR_HPP

class DistanceSensor {
public:
    virtual ~DistanceSensor() {}

    // Virtual method to get distance in meters
    virtual float getDistanceInMeters() const = 0;

    // Virtual method to get distance in centimeters
    virtual float getDistanceInCentimeters() const = 0;

    // Virtual method to get distance in millimeters
    virtual float getDistanceInMillimeters() const = 0;
};

#endif // DISTANCESENSOR_HPP
