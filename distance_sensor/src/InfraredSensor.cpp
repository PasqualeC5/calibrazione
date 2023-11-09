
#include "DistanceSensor.hpp"
#include "InfraredSensor.hpp"
#include <pigpio.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
// Constructor implementation
InfraredSensor::InfraredSensor(int a)
{

    // Open serial port ("/dev/ttyUSB0" is the default for USB serial communication)
}
void InfraredSensor::testDevice()
{
    int serial_port = serOpen("/dev/ttyUSB0", 9600, 0);
    if (serial_port < 0)
    {
        std::cerr << "Failed to open serial port." << std::endl;
    }

    // Send data over serial port
    serWrite(serial_port, "a", 1);

    // Read data from serial port
    char buffer[256];

    int bytesRead = serRead(serial_port, buffer, sizeof(buffer) - 1);
    if (bytesRead > 0)
    {
        std::cout << buffer << std::endl;
    }
}

void sendMessageToDevices(const std::vector<std::string> &deviceIdentifiers, const std::string &message)
{
    for (const auto &device : deviceIdentifiers)
    {
        std::cout << device;
        // Use GPIO pins for communication with USB devices here
        // std::cout << "Sending message to device " << device << ": " << message << std::endl;
        // Implement communication logic using GPIO pins and device identifier here
    }
}

// Implementation of virtual method to get distance in centimeters
float InfraredSensor::getDistanceInCentimeters()
{
    return getDistanceInMeters() / 10;
}

float InfraredSensor::getDistanceInMillimeters()
{
    return 0;
}

// Implementation of virtual method to get distance in millimeters
float InfraredSensor::getDistanceInMeters()
{
    return getDistanceInMillimeters() / 1000;
}
