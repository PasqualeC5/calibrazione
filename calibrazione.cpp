/*LIBRARIES*/
#include <stdio.h>
#include <iomanip>
#include <unistd.h>
#include <iostream>
#include <sstream>
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

// COMMAND LINE ARGUMENTS
#define HELP_COMMAND "help"
#define CONFIG_FROM_FILE_COMMAND "config"
#define SENSOR_COMMAND "sensor"                       // REQUIRED sensor specifier command [--sensor]
#define INFRARED_SENSOR_VALUE "infrared"              // infrared sensor specifier [--sensor=infrared]
#define ULTRASONIC_SENSOR_VALUE "ultrasonic"          // ultrasonic sensor specifier [--sensor=ultrasonic]
#define SURFACE_TYPE_COMMAND "surface"                // surface specifier [--surface="surface_name"]
#define NUMBER_OF_MEASUREMENTS_COMMAND "measurements" // number of measurements per cycle [--measurements=number_of_measurements]
#define USE_ROBOT_COMMAND "userobot"                  // command flag to use meca500 robot [--userobot]
#define MEASURE_DELAY_US_COMMAND "delay"              // delay between measurements in micro seconds [--delay=microseconds]
#define ROBOT_STARTING_POSITION_COMMAND "position"    // starting pose of the meca500

/* DEFAULT VALUES */
#define MEASUREMENTS_PER_CYCLE_DEFAULT 100   // default number of measurements per cycle
#define ECHO_PIN 23                          // default ECHO GPIO PIN for the ultrasonic sensor
#define TRIG_PIN 22                          // default TRIG GPIO PIN for the ultrasonic sensor
#define MEASUREMENT_DELAY_US_DEFAULT 0.02e+6 // default delay between measurements in micro seconds

using namespace std;

/********HELPER FUNCTIONS********/
// SETUP
map<string, string> parse_command_line(int argc, char *argv[]); // function to parse the appropriate command line arguments
map<string, string> parse_config_file(string config_file_path); // function to parse config file parameters
vector<float> parse_string_to_vector(string input);             // function to parse a string representing a vector like this {140, -170, 120, 90, 90, 0}
int setup_options(map<string, string> options);                 // function to setup the program based on the command line arguments
int setup_measurements_parameters();                            // function to setup the measurements parameters
void display_usage();                                           // function to display usage message from help command
void setup_robot_offset();                                      // function to measure the robot starting distance i.e. offset

// MEASUREMENTS
void make_measurements(DistanceSensor &sensor, int number_of_measurements, vector<float> &measurements, unsigned int delay_us);
void write_measurements_to_csv(vector<float> measurments, string file_path);

// ROBOT MOVEMENT
void move_robot_to_position(vector<float> robot_position);

/********************************/

// GLOBAL VARIABLES
long measurement_delay = MEASUREMENT_DELAY_US_DEFAULT;                    // delay between measurements in microseconds
int number_of_measurements = MEASUREMENTS_PER_CYCLE_DEFAULT;              // Number of measurements per cycle
const vector<float> default_robot_position = {200, -170, 120, 90, 90, 0}; // default robot starting position
vector<float> robot_position(default_robot_position);                     // Robot starting position
string surface_name = "";                                                 // surface name for saving measurements
bool use_robot = false;                                                   // Flag to enable meca500 usage
string sensor_type;                                                       // sensor name to be used i.e. [infrared, ultrasonic]
string config_file_path = "";                                             // path to config file
DistanceSensor *sensor = nullptr;                                         // Sensor to use for measuring
Robot *robot = nullptr;                                                   // Robot object to handle meca500 communication
float min_measurement,                                                    // minimum distance to be measured
    max_measurement,                                                      // maximum distance to be measured
    step_size,                                                            // step interval between measurements
    current_measurement,                                                  // current distance to be measured
    robot_position_offset = 8;                                            // distance offset for robot position

int main(int argc, char *argv[])
{
    // setup from command line arguments
    // if return value is != 0 there was an error
    if (setup_options(parse_command_line(argc, argv)) != 0)
        return 1;
    if (setup_measurements_parameters() != 0)
        return 1;

    vector<float> measurements;                                                  // vector storing all the measurements
    string file_path = "measurements/" + sensor_type + "/" + surface_name + "/"; // output file path
    string csv_file_name;                                                        // name of output file

    // measurement process
    cout << "Setup complete\nStarting measurements\n\n";

    if (use_robot)
        setup_robot_offset();

    while (current_measurement <= max_measurement)
    {
        // setup for next set of measurements
        measurements.clear();
        csv_file_name = (current_measurement < 100 ? "0" : "") + to_string((int)current_measurement) + "mm.csv";

        cout << "Currently measuring: " << current_measurement << " mm\n";
        if (use_robot)
        {
            cout << "Moving robot to position..." << endl;

            // decrease robot position x value by step size(moving away from the obstacle)
            // if its the first set of measurements account for the offset and position to the minimum distance
            robot_position[0] -= (current_measurement == min_measurement) ? (current_measurement - robot_position_offset) : step_size;

            move_robot_to_position(robot_position);
        }
        else
        {
            cout << "Please position the obstacle in front of the sensor" << endl
                 << "Press any button to continue..." << endl;
            char c = getchar();
            c = getchar(); // hack to fix infrared sensor user input (endl in buffer)
        }

        cout << "Measuring distance..." << endl;
        make_measurements(*sensor, number_of_measurements, measurements, measurement_delay);
        cout << "Writing measurements to csv file"
             << endl
             << endl;
        write_measurements_to_csv(measurements, file_path + csv_file_name);
        current_measurement += step_size;
    }
    return 0;
}

void setup_robot_offset()
{
    vector<float> measurements;
    cout << "Please position the obstacle in front of the sensor" << endl
         << "Press any button to continue..." << endl;
    char c = getchar();

    c = getchar(); // hack to fix infrared sensor user input (endl in buffer)

    cout << "Measuring robot position offset" << endl;
    make_measurements(*sensor, MEASUREMENTS_PER_CYCLE_DEFAULT, measurements, 0.02e+6);
    cout << "Calculating robot position offset" << endl;

    robot_position_offset = 0;
    for (float measurement : measurements)
    {
        robot_position_offset += measurement;
    }
    robot_position_offset /= measurements.size();

    cout << "Robot average position offset: " << robot_position_offset << endl;
}

int setup_measurements_parameters()
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
void move_robot_to_position(vector<float> robot_position)
{
    robot->move_pose(
        robot_position[0],
        robot_position[1],
        robot_position[2],
        robot_position[3],
        robot_position[4],
        robot_position[5]);
}

void initialise_robot()
{

    use_robot = true;
    robot = new Robot(40, 240, 5000, "eth0", 0.0, 10);
    robot->reset_error();
    robot->set_conf(1, 1, -1);
    robot->print_pose();
    move_robot_to_position(robot_position);
}

int setup_options(map<string, string> options)
{
    // Handle each options
    stringstream option_message;

    for (const auto &option : options)
    {
        string command = option.first;
        string value = option.second;

        // You can assign any behavior based on the option
        if (command == "help")
        {
            display_usage();
            return 1;
        }
        else if (command == ROBOT_STARTING_POSITION_COMMAND)
        {
            vector<float> robot_position_values = parse_string_to_vector(value);
            if (robot_position_values.size() < 6)
            {
                cerr << "Invalid robot position, not enough arguments" << endl;
                cerr << "Program will now exit..." << endl;
                return 1;
            }
            option_message << "Starting robot position: {";
            for (float pos : robot_position_values)
                option_message << pos << ", ";
            option_message << "}" << endl;
            robot_position = robot_position_values;
        }
        else if (command == SENSOR_COMMAND)
        {
            option_message << "Sensor used: " << value << "\n";
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
                cerr << "Invalid number of measurements value" << endl;
                cerr << "Program will now exit..." << endl;
                return 1;
            }
            option_message << "Number of measurements per cycle: " << value << "\n";
            number_of_measurements = int_value;
        }
        else if (command == USE_ROBOT_COMMAND)
        {
            option_message << "Using Meca500 robot\n"
                           << "Initialising robot EtherCAT interface\n";
            initialise_robot();
        }
        else if (command == SURFACE_TYPE_COMMAND)
        {
            option_message << "Surface used: " << value << "\n";
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
            option_message << "Measurement delay in us used: " << value << "\n";
            measurement_delay = int_value;
        }
        else if (command == CONFIG_FROM_FILE_COMMAND)
        {
            // value corresponds to the path of the config file given
            setup_options(parse_config_file(value));
        }
        else
        {
            option_message << "Unknown option: " << command << "\n";
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
    cout << option_message.str() << endl;
    return 0;
}

map<string, string> parse_command_line(int argc, char *argv[])
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
map<string, string> parse_config_file(string config_file_path)
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

vector<float> parse_string_to_vector(string input)
{
    vector<float> result;

    // Check if the string starts with a curly brace
    if (input.empty() || input[0] != '{')
    {
        cerr << "Error: Input string does not start with a curly brace.\n";
        return result;
    }

    stringstream ss(input);

    // Remove curly braces from the input string
    char discard;
    ss >> discard; // Discard the opening curly brace

    // Read the values into the vector
    float value;
    while (ss >> value)
    {
        result.push_back(value);

        // Check for comma and discard if present
        if (ss.peek() == ',')
            ss.ignore();
    }
    return result;
}
void display_usage()
{
    const int optionWidth = 40;
    const int descriptionWidth = 60;

    cout << left << setw(optionWidth) << "Usage: ./calibrazione [OPTIONS]" << endl
         << "Options:" << endl
         << "  --" << setw(optionWidth) << HELP_COMMAND << setw(descriptionWidth) << "Display this help message" << endl
         << "  --" << CONFIG_FROM_FILE_COMMAND << setw(optionWidth - strlen(CONFIG_FROM_FILE_COMMAND)) << "=\"path/to/configfile.txt\"" << setw(descriptionWidth) << "Parse options from text file" << endl
         << "  --" << SENSOR_COMMAND << setw(optionWidth - strlen(SENSOR_COMMAND)) << "=TYPE" << setw(descriptionWidth) << "Specify sensor type (e.g., infrared, ultrasonic)" << endl
         << "  --" << SURFACE_TYPE_COMMAND << setw(optionWidth - strlen(SURFACE_TYPE_COMMAND)) << "=TYPE" << setw(descriptionWidth) << "Specify surface type for measurements" << endl
         << "  --" << NUMBER_OF_MEASUREMENTS_COMMAND << setw(optionWidth - strlen(NUMBER_OF_MEASUREMENTS_COMMAND)) << "=COUNT" << setw(descriptionWidth) << "Specify the number of measurements to take" << endl
         << "  --" << setw(optionWidth) << USE_ROBOT_COMMAND << setw(descriptionWidth) << "Use robot for measurements" << endl
         << "  --" << MEASURE_DELAY_US_COMMAND << setw(optionWidth - strlen(MEASURE_DELAY_US_COMMAND)) << "=DELAY_VALUE_US" << setw(descriptionWidth) << "Specify the delay in microseconds between measurements" << endl
         << "  --" << ROBOT_STARTING_POSITION_COMMAND << setw(optionWidth - strlen(ROBOT_STARTING_POSITION_COMMAND)) << "=\"{x,y,z,alpha,beta,gamma}\"" << setw(descriptionWidth) << "Specify the starting pose of the meca500 [default {140, -170, 120, 90, 90, 0} ]" << endl
         << endl
         << setw(optionWidth) << "Example usage:" << endl
         << "  ./calibrazione --" << SENSOR_COMMAND << "=infrared --" << SURFACE_TYPE_COMMAND << "=wood --" << NUMBER_OF_MEASUREMENTS_COMMAND << "=10 --" << USE_ROBOT_COMMAND << " --" << MEASURE_DELAY_US_COMMAND << "=100000" << endl;
}