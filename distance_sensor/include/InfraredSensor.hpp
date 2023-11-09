#ifndef INFRAREDSENSOR_HPP
#define INFRAREDSENSOR_HPP

class InfraredSensor : public DistanceSensor
{

private:
    const char *name1 = "ttyUSB";
    const char *name2 = "ttyACM";

public:
    InfraredSensor(int a);
    // Implementation of virtual methods to get distance in meters, centimeters, and millimeters
    float getDistanceInMeters() override;
    float getDistanceInCentimeters() override;
    float getDistanceInMillimeters() override;
    void testDevice();
};

#endif /* INFRAREDSENSOR_HPP */
