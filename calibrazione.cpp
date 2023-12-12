/*LIBRARIES*/
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <cstring>
#include <string>
#include "../csvlogger/CsvLogger.hpp"
#include "../distance_sensor/include/DistanceSensor.hpp"
#include "../distance_sensor/include/UltrasonicSensor.hpp"
#include "../distance_sensor/include/InfraredSensor.hpp"
#include "../meca500_ethercat_cpp/Robot.hpp"
#include <string.h>
#include <map>

#define SENSOR_COMMAND "sensor"                       // REQUIRED sensor specifier command [--sensor]
#define INFRARED_SENSOR_VALUE "infrared"              // infrared sensor specifier [--sensor=infrared]
#define ULTRASONIC_SENSOR_VALUE "ultrasonic"          // ultrasonic sensor specifier [--sensor=ultrasonic]
#define SURFACE_TYPE_COMMAND "surface"                // surface specifier [--surface="surface_name"]
#define NUMBER_OF_MEASUREMENTS_COMMAND "measurements" // number of measurements per cycle [--measurements=number_of_measurements]
#define USE_ROBOT_COMMAND "userobot"                  // command flag to use meca500 robot [--userobot]
#define MEASURE_DELAY_US_COMMAND "delay"              // delay between measurements in micro seconds [--delay=microseconds]

/* CONSTANTS */
#define MEASURES_PER_CYCLE 100 // default number of measurements per cycle
#define ECHO_PIN 23            // default ECHO GPIO PIN for the ultrasonic sensor
#define TRIG_PIN 22            // default TRIG GPIO PIN for the ultrasonic sensor
#define MEASURE_DELAY_US 200   // default delay between measurements in micro seconds

using namespace std;

/********HELPER FUNCTIONS********/
// SETUP
map<string, string> parseCommandLine(int argc, char *argv[]); // function to parse the appropriate command line arguments
int setupOptions(map<string, string> options);                // function to setup the program based on the command line arguments
int setupMeasurementsParameters();                            // function to setup the measurements parameters
void displayUsage();                                          // function to display usage message from help command

// CALCULATIONS
map<float, float> calculateProbabilityDistribution(const vector<float> &numbers);
float calculateWeightedAverage(const vector<float> &numbers, const map<float, float> &probabilityDistribution);

// MEASUREMENTS
void make_measurements(DistanceSensor &sensor, int number_of_measurements, vector<float> &measurements, unsigned int delay_us);
void write_measurements_to_csv(vector<float> measurments, string file_path);

// ROBOT MOVEMENT
void movePose(float robot_position[6]);

/********************************/

// GLOBAL VARIABLES
DistanceSensor *sensor = nullptr;                      // Sensor to use for measuring
Robot *robot = nullptr;                                // Robot object to handle meca500 communication
int number_of_measurements = MEASUREMENTS_PER_CYCLE;   // Number of measurements per cycle
bool use_robot = false;                                // Flag to enable meca500 usage
float robot_position[6] = {140, -170, 120, 90, 90, 0}; // Robot starting position
string surface_name = "";                              // surface name for saving measurements
long measurement_delay = MEASURE_DELAY_US;
float min_measurement, max_measurement, step_size, current_measurement, robot_position_offset;
string sensor_type;

int main(int argc, char *argv[])
{
    // setup from command line arguments
    // if return value is != 0 there was an error
    if (setupOptions(parseCommandLine(argc, argv)) != 0)
        return 1;
    if (setupMeasurementsParameters() != 0)
        return 1;
    vector<float> measurements;
    string file_path = "measurements/" + sensor_type + "/" + surface_name + "/";
    string csv_file_name;

    if (use_robot)
    {
        cout << "Please position the obstacle in front of the sensor" << endl
             << "Press any button to continue..." << endl;
        char c = getchar();
        measurements.clear();
        cout << "Measuring robot position offset" << endl;
        make_measurements(*sensor, MEASURES_PER_CYCLE, measurements, 0.02e+6);
        cout << "Calculating robot position offset" << endl;
        map<float, float> probabilityDistribution = calculateProbabilityDistribution(measurements);
        robot_position_offset = calculateWeightedAverage(measurements, probabilityDistribution);
        cout << "Robot position offset: " << robot_position_offset << endl;
    }

    while (current_measurement <= max_measurement)
    {
        // clear the array of measurements to prepare for next set of measurements
        measurements.clear();
        csv_file_name = (current_measurement < 100 ? "0" : "") + to_string((int)current_measurement) + "mm.csv";

        cout << "Currently measuring: " << current_measurement << " mm\n";
        if (use_robot)
        {
            cout << "Moving robot to position..." << endl;
            robot_position[0] = robot_position[0] - current_measurement + robot_position_offset;
            movePose(robot);
        }
        else
        {
            cout << "Please position the obstacle in front of the sensor" << endl
                 << "Press any button to continue..." << endl;
            char c = getchar();
        }
        cout << "Measuring distance...";
        make_measurements(*sensor, number_of_measurements, measurements, measurement_delay);
        cout << "Writing measurements to csv file";
        write_measurements_to_csv(measurements, file_path + csv_file_name);
    }
    return 0;
}
// Function to calculate the probability distribution for each number in the list
map<float, float> calculateProbabilityDistribution(const vector<float> &numbers)
{
    map<float, float> probabilityDistribution;

    // Count occurrences of each number
    for (const float &num : numbers)
    {
        probabilityDistribution[num]++;
    }

    // Calculate probabilities
    for (auto &pair : probabilityDistribution)
    {
        pair.second /= numbers.size();
    }

    return probabilityDistribution;
}

// Function to calculate the weighted average using the probability distribution
float calculateWeightedAverage(const vector<float> &numbers, const map<float, float> &probabilityDistribution)
{
    float weightedSum = 0.0;

    // Calculate weighted sum
    for (const float &num : numbers)
    {
        weightedSum += num * probabilityDistribution.at(num);
    }

    return weightedSum;
}

int setupMeasurementsParameters()
{
    string input_fil_path = "input_files/misure_test.txt";
    ifstream input_file(input_fil_path);
    if (!input_file.is_open())
    {
        cerr << "Error opening input file!" << endl;
        cerr << "Program will now exit..." << endl;
        return 1; // Return an error code
    }

    input_file >> min_measurement;
    input_file >> max_measurement;
    input_file >> step_size;
    current_measurement = min_measurement;
    return 0;
}

void make_measurements(DistanceSensor &sensor, int number_of_measurements, vector<float> &measurements, unsigned int delay_us)
{
    // create file which name is string (see Constructor)
    float distance;
    for (int i = 0; i < number_of_measurements; i++)
    {
        distance = sensor.getDistanceInMillimeters();
        measurements.push_back(distance);
        usleep(delay_us);
    }
}
void write_measurements_to_csv(vector<float> measurments, string file_path)
{
    CsvLogger measurements_logger(file_path);
    measurements_logger.write("distance\n");
    for (float measurement : measurments)
    {
        measurements_logger << measurement;
        measurements_logger.end_row();
    }

    measurements_logger.close();
}
void movePose(float robot_position[6])
{
    robot->move_pose(
        robot_position[0],
        robot_position[1],
        robot_position[2],
        robot_position[3],
        robot_position[4],
        robot_position[5]);
}

void setupRobot()
{

    use_robot = true;
    robot = new Robot(40, 240, 5000, "eth0", 0.0, 10);
    robot->reset_error();
    robot->set_conf(1, 1, -1);
    robot->print_pose();
    movePose(robot_position);
}

int setupOptions(map<string, string> options)
{
    // Handle each option
    for (const auto &option : options)
    {
        string command = option.first;
        string value = option.second;

        // You can assign any behavior based on the option
        if (command == "help")
        {
            displayUsage();
            return 1;
        }
        else if (command == SENSOR_COMMAND)
        {
            cout << "Sensor used: " << value << "\n";
            if (value == INFRARED_SENSOR_VALUE)
                sensor = new InfraredSensor(InfraredSensor::ENABLE_FIRST);
            else if (value == ULTRASONIC_SENSOR_VALUE)
                sensor = new UltrasonicSensor(TRIG_PIN, ECHO_PIN);
            else
            {
                cerr << "Invalid sensor type. Supported types: ultrasonic, infrared" << endl;
                cerr << "Program will now exit..." << endl;
                return 1;
            }
            sensor_type = value;
        }
        else if (command == NUMBER_OF_MEASUREMENTS_COMMAND)
        {

            int int_value = stoi(value);
            if (int_value < 0)
            {
                cerr << "Invalid number of measures value" << endl;
                cerr << "Program will now exit..." << endl;
                return 1;
            }
            cout << "Number of measures per cycle: " << value << "\n";
            number_of_measurements = int_value;
        }
        else if (command == USE_ROBOT_COMMAND)
        {
            cout << "Using Meca500 robot\n"
                 << "Initialising robot EtherCAT interface\n";
            setupRobot();
        }
        else if (command == SURFACE_TYPE_COMMAND)
        {
            cout << "Surface used: " << value << "\n";
            surface_name = value;
        }
        else if (command == MEASURE_DELAY_US_COMMAND)
        {
            int int_value = stoi(value);
            if (int_value < 0)
            {
                cerr << "Invalid number of measures value" << endl;
                cerr << "Program will now exit..." << endl;
                return 1;
            }
            cout << "Measurement delay in us used: " << value << "\n";
            measurement_delay = int_value;
        }
        else
        {
            cout << "Unknown option: " << command << "\n";
        }
    }
    if (sensor == nullptr)
    {
        cerr << "Sensor type not set!!" << endl;
        cerr << "Please specify the sensor type with" << endl;
        cerr << "--" << SENSOR_COMMAND << "=[infrared, ultrasonic]";
        cerr << "Program will now exit..." << endl;
        return 1;
    }
    return 0;
}

map<string, string> parseCommandLine(int argc, char *argv[])
{
    map<string, string> options;

    for (int i = 1; i < argc; ++i)
    {
        string arg = argv[i];
        if (arg.substr(0, 2) == "--")
        {
            string command;
            // Found an option
            size_t pos = arg.find('=');
            if (pos != string::npos)
                command = arg.substr(2, pos - 2);
            else
                command = arg.substr(2);
            string value = (pos != string::npos) ? arg.substr(pos + 1) : "";

            options[command] = value;
        }
    }

    return options;
}
void displayUsage()
{
    cout << "Usage: ./myprogram [OPTIONS]\n"
         << "Options:\n"
         << "  --help               Display this help message\n"
         << "  --sensor=TYPE        Specify sensor type (e.g., infrared, ultrasonic)\n"
         << "  --surface=TYPE       Specify surface type for measurements\n"
         << "  --measures=COUNT     Specify the number of measurements to take\n"
         << "  --userobot           Use robot for measurements\n"
         << "  --delay=VALUE        Specify the delay in microseconds between measurements\n\n"
         << "Example Usage:\n"
         << "  ./myprogram --sensor=infrared --surface=wood --measures=10 --userobot --delay=100000\n";
}