
#include "../csvlogger/CsvLogger.hpp"
//#include "CsvLogger.hpp"
#include <time.h>



int main(int argc, char *argv[])
{
    
    /*files to write, setup*/
    CsvLogger input_logger("velocity_control");
    input_logger.write("time, value\n");
    
    /*squarewave generation, setup*/
    double input_velocity_mms = 10;         //10mm/s    (amplitude)
    double period_s = 6;                    //6sec      (period)

    /*squarewawe T = 6s, A=10mm/s*/


    /*time variables setup*/
    time_t startTime, currentTime, t0;
    time(&t0); //time to start analysing response

    
    /*process*/
    while (true)
    {
        //input
        //robot.move_lin_vel_wrf(input_velocity_mms); //give 10mm/s or -10mm/s


        time(&startTime);
        while (1) // Run the loop for 3 seconds
        {
            // Check if 3 seconds have passed. Exit cycle if true
            time(&currentTime);
            if (currentTime - startTime >= period_s/2) {
                break; // Exit the loop after 3 seconds
            }


            //get datas
            input_logger << (currentTime-t0);
            input_logger << input_velocity_mms;
            input_logger.end_row();


            // short delay:
            // usleep(putyourdelayhere);
        }


        input_velocity_mms = - input_velocity_mms;
    }
}



