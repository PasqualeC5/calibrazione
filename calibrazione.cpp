/*LIBRARIES*/
#include <stdio.h>
#include <iomanip>
#include <pigpio.h>
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

#define HELP_COMMAND "help"
#define CONFIG_FROM_FILE_COMMAND "config"
#define SENSOR_COMMAND "sensor"                       // REQUIRED sensor specifier command [--sensor]
#define INFRARED_SENSOR_VALUE "infrared"              // infrared sensor specifier [--sensor=infrared]
#define ULTRASONIC_SENSOR_VALUE "ultrasonic"          // ultrasonic sensor specifier [--sensor=ultrasonic]
#define SURFACE_TYPE_COMMAND "surface"                // surface specifier [--surface="surface_name"]
#define NUMBER_OF_MEASUREMENTS_COMMAND "measurements" // number of measurements per cycle [--measurements=number_of_measurements]
#define USE_ROBOT_COMMAND "userobot"                  // command flag to use meca500 robot [--userobot]
#define MEASURE_DELAY_US_COMMAND "delay"              // delay between measurements in micro seconds [--delay=microseconds]

/* CONSTANTS */
#define MEASUREMENTS_PER_CYCLE 100 // default number of measurements per cycle
#define ECHO_PIN 23                // default ECHO GPIO PIN for the ultrasonic sensor
#define TRIG_PIN 22                // default TRIG GPIO PIN for the ultrasonic sensor
#define MEASURE_DELAY_US 200       // default delay between measurements in micro seconds

using namespace std;

/********HELPER FUNCTIONS********/
// SETUP
map<string, string> parseCommandLine(int argc, char *argv[]); // function to parse the appropriate command line arguments
map<string, string> parseConfigFile(string config_file_path); // function to parse config file parameters
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
float min_measurement, max_measurement, step_size, current_measurement, robot_position_offset = 8;
string sensor_type;
string config_file_path = "";
bool use_config_file = false;

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
        c = getchar();

        // measurements.clear();
        // cout << "Measuring robot position offset" << endl;
        // make_measurements(*sensor, MEASUREMENTS_PER_CYCLE, measurements, 0.02e+6);
        // cout << "Calculating robot position offset" << endl;
        // map<float, float> probabilityDistribution = calculateProbabilityDistribution(measurements);
        // robot_position_offset = calculateWeightedAverage(measurements, probabilityDistribution);
        // float average = 0;
        // for (float measurement : measurements)
        // {
        //     average += measurement;
        // }
        // average /= measurements.size();
        // cout << "Robot weighted average position offset: " << robot_position_offset << endl;
        // cout << "Robot average position offset: " << average << endl;
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
            robot_position[0] = robot_position[0] - step_size;
            movePose(robot_position);
        }
        else
        {
            cout << "Please position the obstacle in front of the sensor" << endl
                 << "Press any button to continue..." << endl;
            char c = getchar();
            c = getchar(); // hack to fix infrared sensor user input
        }
        cout << "Measuring distance..." << endl;
        make_measurements(*sensor, number_of_measurements, measurements, measurement_delay);
        cout << "Writing measurements to csv file" << endl;
        write_measurements_to_csv(measurements, file_path + csv_file_name);
        current_measurement += step_size;
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
                sensor = new InfraredSensor(InfraredSensor::USER_INPUT);
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
        else if (command == CONFIG_FROM_FILE_COMMAND)
        {
            setupOptions(parseConfigFile(value));
        }
        else
        {
            cout << "Unknown option: " << command << "\n";
        }
    }
    if (sensor == nullptr)
    {
        cerr << "Sensor type not set!!" << endl
             << "Please specify the sensor type with" << endl
             << "--" << SENSOR_COMMAND << "=[infrared, ultrasonic]" << endl
             << "Program will now exit..." << endl;
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
map<string, string> parseConfigFile(string config_file_path)
{
    map<string, string> options;
    ifstream config_file(config_file_path);
    if (!config_file.is_open())
    {
        cerr << "Error opening config file!" << endl;
        cerr << "Program will now exit..." << endl;
        exit(1); // Return an error code
    }
    string config_row;

    while (getline(config_file, config_row))
    {
        size_t pos = config_row.find('=');
        string command;
        if (pos != string::npos)
            command = config_row.substr(0, pos);
        else
            command = config_row.substr(0);
        string value = (pos != string::npos) ? config_row.substr(pos + 1) : "";
        options[command] = value;
    }

    return options;
}
void displayUsage()
{
    const int optionWidth = 10;
    const int descriptionWidth = 60;

    cout << left << setw(optionWidth) << "Usage: ./calibrazione [OPTIONS]" << endl
         << setw(optionWidth) << "Options:" << endl
         << setw(optionWidth) << "  --" << HELP_COMMAND << setw(descriptionWidth) << "Display this help message" << endl
         << setw(optionWidth) << "  --" << CONFIG_FROM_FILE_COMMAND << "=config_file_path" << setw(descriptionWidth) << "Parse options from text file" << endl
         << setw(optionWidth) << "  --" << SENSOR_COMMAND << "=TYPE" << setw(descriptionWidth) << "Specify sensor type (e.g., infrared, ultrasonic)" << endl
         << setw(optionWidth) << "  --" << SURFACE_TYPE_COMMAND << "=TYPE" << setw(descriptionWidth) << "Specify surface type for measurements" << endl
         << setw(optionWidth) << "  --" << NUMBER_OF_MEASUREMENTS_COMMAND << "=COUNT" << setw(descriptionWidth) << "Specify the number of measurements to take" << endl
         << setw(optionWidth) << "  --" << USE_ROBOT_COMMAND << setw(descriptionWidth) << "Use robot for measurements" << endl
         << setw(optionWidth) << "  --" << MEASURE_DELAY_US_COMMAND << "=DELAY_VALUE_US" << setw(descriptionWidth) << "Specify the delay in microseconds between measurements" << endl
         << endl
         << setw(optionWidth) << "Example usage:" << endl
         << "  ./calibrazione --" << SENSOR_COMMAND << "=infrared --" << SURFACE_TYPE_COMMAND << "=wood --" << NUMBER_OF_MEASUREMENTS_COMMAND << "=10 --" << USE_ROBOT_COMMAND << " --" << MEASURE_DELAY_US_COMMAND << "=100000" << endl;
}