/*
    DISCRETE-TIME REGULATOR:

    y[k] = 9.1 * u[k]  -  3.986 * u[k-1]  -  0.531 y[k-1]


    IMPORTANT:
    y is R output -> Meca next velocity
    u is R input -> error = reference - measured distance

*/



#include "distance_sensor/include/DistanceSensor.hpp"
#include "distance_sensor/include/InfraredSensor.hpp"
#include "meca500_ethercat_cpp/Robot.hpp"
#include <pigpio.h>
#include "csvlogger/CsvLogger.hpp"
#include <unistd.h>


/*costants*/
#define Tc_s 0.1                   //passo camp
#define RANGEINF_mm 20             //range for reference_distance (inferior)
#define RANGESUP_mm 150            //range for reference_distance (superior)
#define DEFAULTREFERENCE_mm 50     //reference (desired distance Meca-Obstacle)


/*global*/
float reference_distance = DEFAULTREFERENCE_mm;                             //5 cm default
DistanceSensor sensor = new InfraredSensor(InfraredSensor::USER_INPUT);
bool take_data = false;                                                     //no take data default


/*functions*/
void menu(int n_par, char* par[]);


int main(int argc, char *argv[])
{

    if (gpioInitialise() < 0)
        exit(1);

    /*menu display - control*/
    menu(argc, argv);

    
    /*robot, setup*/
    Robot robot(40, 240, 5000, "eth0", 0.0, 10);
    robot.reset_error();
    // robot.main();
    robot.set_conf(1, 1, -1);
    robot.move_pose(130, -170, 120, 90, 90, 0); //bring Meca to 0_position
    //robot.print_pose();

     
    /*files to write, setup*/
    CsvLogger data_test("data_test.csv");
    data_test.write("time,distance\n");     //if !take_data -> empy file

    /*time variables setup*/
    uint32_t startTime, currentTime, t0;
    t0 = gpioTick(); // time to start analysing response
    


    /*state variables*/
    float y_k1 = 0;     //y[k-1]
    float u_k1 = 0;     //u[k-1]

    float d;

    /*process variables*/
    float u_k;          //u[k]
    float y_k;          //y[k]


    /*process*/
    while (true)
    {
        /*compute*/
        d = sensor.getDistanceInMillimeters();

        u_k = reference_distance - d;
        y_k = 9.1 * u_k - 3.968 * u_k1 - 0.531 * y_k1;

        /*check position limits. if not sure for Meca -> y_k = 0 (stop)*/
        if((y_k > y_k1) ? y_k : y_k1 * Tc_s + robot.get_position() > robot.POS_LIMIT_SUP || 
           (y_k < y_k1) ? y_k : y_k1 * Tc_s + robot.get_position() < robot.POS_LIMIT_INF)
            y_k = 0;

        /*give meca velocity command*/
        robot.move_lin_vel_wrf(y_k); 


        /*if take_date requested*/
        if(take_data)
        {
            currentTime = gpioTick();
            data_test << (currentTime - t0) / 1e6;
            data_test << d;
            data_test.end_row();
        }
            
        /*prepare for next */
        u_k1 = u_k;
        y_k1 = y_k;

        usleep(Tc_s * 1e6); //????
    }
}


/*
    cmmd line -> 
    R 
    R distance
    R distance take_data(1-0)
*/
void menu(int n_par, char* par[])
{
    /* if distance_reference is passed and correct, so set, else default*/
    if(argc == 2 || argc ==3)
    {
        if(reference_distance < RANGEINF_mm || reference_distance > RANGESUP_mm) 
            printf("OUT OF RANGE [%d, %d]. Refence set to default: %d mm", RANGEINF_mm, RANGESUP_mm, DEFAULTREFERENCE_mm);
        else
            reference_distance = atof(argv[1]);
    }

    if(argc == 3)
    {
        take_data = atoi(par[2]);
    }
   
}