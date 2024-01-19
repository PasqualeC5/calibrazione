/*
    DISCRETE-TIME REGULATOR:

    y[k] = 4.6129 * u[k]  -  3.8864 * u[k-1]  + 0.7 * y[k-1]


    LEGENDA:
    y is R output -> Meca next velocity
    u is R input -> error = reference - measured distance

*/

#include "distance_sensor/include/DistanceSensor.hpp"
#include "distance_sensor/include/InfraredSensor.hpp"
#include "meca500_ethercat_cpp/Robot.hpp"
#include "csvlogger/CsvLogger.hpp"
#include <unistd.h>
#include <iostream>
#include <math.h>
#include <chrono>

/*costants*/
#define Tc_s 0.02               // passo camp
#define DEFAULTREFERENCE_mm -50 // reference (desired distance Meca-Obstacle)

using namespace std;


/*GLOBAL*/
    /*variable for interpolation
        reference_user: desired distance meca - obastacle
        reference_distance: reference variable  (desidered to be reference_user)
        interpolate: flag to smooth reference distance when required
    */
    float reference_distance = DEFAULTREFERENCE_mm; // 5 cm default
    float reference_user = DEFAULTREFERENCE_mm;
    bool interpolate = true;

    /*sensor initialize
        m & q = parameters for calibration line -> y=mx+q
    */
    InfraredSensor sensor(InfraredSensor::USER_INPUT);
    float m = 1;
    float q = 0;

/*FUNCTIONS*/
    void menu(int n_par, char *par[]);              //manage user input from cmd
    uint64_t getCurrentTimeMicros();                //return current time in microseconds
    void delayMicroseconds(uint64_t microseconds);  //stop execution 

int main(int argc, char *argv[])
{

    /*menu control*/
    menu(argc, argv);

    sensor.useCalibrationCurve(m, q);

    /*robot, setup*/
    Robot robot(30, 200, 5000, "eth0", 0.0, 10);
    robot.reset_error();
    // robot.main();
    robot.set_conf(1, 1, -1);
    robot.move_pose(115, -170, 120, 90, 90, 0); // bring Meca to 0_position
    // robot.print_pose();

    /*files to write, setup*/
    CsvLogger data_test("test_closed_loop/data_test.csv");
    data_test.write("time,reference,position,measured_distance,error,velocity_control\n"); // if !take_data -> empy file

    /*time variables setup*/
    uint64_t t0, start;
    float current_time = 0;
    float delay_time;

    /*state variables*/
    float y_k1 = 0; // y[k-1]
    float u_k1 = 0; // u[k-1]
    float starting_reference = -sensor.getDistanceInMillimeters();
    float rise_time = 0.5;
    float slope = (reference_user - starting_reference) / rise_time;

    float d;

    /*process variables*/
    float u_k; // u[k]
    float y_k; // y[k]

    float velocity[] = {0, 0, 0, 0, 0, 0};

    bool out_of_range = false;

    current_time = 0;
    float interpolate_time = 0;
    /*process*/
    while (true)
    {
        start = getCurrentTimeMicros();

        /*compute*/
        d = -sensor.getDistanceInMillimeters();

        if (d < -200)
        {
            cout << endl
                 << "Sensor out of range" << endl;
            cout << "Stopping robot" << endl;
            velocity[0] = 0;
            robot.move_lin_vel_wrf(velocity);

            y_k1 = 0;
            u_k1 = 0;

            interpolate = true;

            cout << "Waiting for Obstacle in range" << endl;
            while (d < -200)
            {
                d = -sensor.getDistanceInMillimeters();

                data_test << current_time;
                data_test << reference_distance;
                data_test << robot.get_position();
                data_test << d;
                data_test << 0;
                data_test << 0;
                data_test.end_row();

                delay_time = Tc_s * 1e6 - (getCurrentTimeMicros() - start);
                delayMicroseconds(Tc_s * 1e6);
                current_time += Tc_s;
            }

            cout << "Obstacle in range" << endl;
            cout << "Resuming control" << endl;

            starting_reference = d;
            slope = (reference_user - starting_reference) / rise_time;
            interpolate_time = current_time;
        }

        if (interpolate)
        {
            reference_distance = slope * (current_time - interpolate_time) + starting_reference;
            if ((slope > 0 && reference_distance >= reference_user) || (slope <= 0 && reference_distance <= reference_user))
            {
                reference_distance = reference_user;
                interpolate = false;
            }
        }

        u_k = reference_distance - d;
        y_k = 4.6129 * u_k - 3.8864 * u_k1 + 0.7 * y_k1;

        // checking robot position limits
        if (robot.get_position() >= robot.POS_LIMIT_SUP)
        {
            if (y_k > 0) // if velocity is positive
            {
                y_k = 0;
            }
        }
        else if (robot.get_position() <= robot.POS_LIMIT_INF)
        {
            if (y_k < 0) // if velocity is negative
            {
                y_k = 0;
            }
        }
        velocity[0] = y_k;
        /*give meca velocity command*/
        robot.move_lin_vel_wrf(velocity);

        /*if take_date requested*/
        // data_test.write("time,reference,position,measured_distance,error,velocity_control\n"); // if !take_data -> empy file

        data_test << current_time;
        data_test << reference_distance;
        data_test << robot.get_position();
        data_test << d;
        data_test << u_k;
        data_test << y_k;
        data_test.end_row();

        /*prepare for next */
        u_k1 = u_k;
        y_k1 = y_k;

        delay_time = Tc_s * 1e6 - (getCurrentTimeMicros() - start);
        delayMicroseconds(delay_time); // delay by time remaining
        current_time += Tc_s;          // increse time by Tc_s for reference smoothing
    }
}


void menu(int n_par, char *par[])
{
    /*
        cmmd line ->
        regolatore 
        regolatore distance
        regolatore distance m q 
    */

    /* if distance_reference is passed and correct, so set, else default*/
    if (n_par >= 2)
    {
        reference_user = -atof(par[1]);
    }

    /* if calibration parameters are passed and correct, so set, else default*/
    if (n_par >= 4)
    {
        m = -atof(par[2]);
        q = -atof(par[3]);
    }
}

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
