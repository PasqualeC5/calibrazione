

/*LIBRARIES*/
#include <stdio.h>
#include <time.h>
#include "../csvlogger/CsvLogger.hpp"
#include <pigpio.h>

/* CONSTANTS */
#define SOUND_SPEED 340

int main()
{
      using namespace std;

      /*INITIALISE PIN*/
      gpioInitialise();
      // printf("GPIO INITIALISED\n");
      gpioSetMode(18, PI_OUTPUT);
      gpioSetMode(17, PI_INPUT);
      int attachedEchoPin = 17;
      int attachedTrigPin = 18;

      /* INITIALISE CYCLE*/
      std::ifstream file_misure("misure_da_prendere.txt");
      // FILE* fp = fopen("misure_da_prendere.txt", "r"); //standard delle misure da prendere
      float cm_distance;
      char name_file_to_create[20];
      int choice;

      while (file_misure >> cm_distance) // read from file to cm_distance
      {
            /*TAKE INPUT FROM USER*/
            printf("Next measure: %fcm\n\nType '1' to start, other to stop immediately : ", cm_distance);
            scanf("%d", &choice);

            if (choice != 1) // stop
                  break;

            /*FILE TO WRITE*/
            // empty string
            sprintf(name_file_to_create, "prova%f.csv", cm_distance);
            std::cout << "Nome file creato: " << name_file_to_create << "\n"; // write in string
            CsvLogger logger(name_file_to_create);                    // create file which name is string (see Constructor)

            // /* TAKE MEASURES */
            // for (int i = 0; i < 1000; i++)
            // {
            //       /* GENERATE TRIG*/
            //       gpioWrite(attachedTrigPin, 1);
            //       gpioDelay(10);
            //       gpioWrite(attachedTrigPin, 0);

            //       /* READ TIME ECHO IS HIGH*/
            //       int seconds;
            //       int micros;

            //       while (!gpioRead(attachedEchoPin))
            //             std::cout << "Waiting for echo\n";         // wait til echo L -> H
            //       gpioTime(PI_TIME_RELATIVE, &seconds, &micros); // take time

            //       int currentMicros;
            //       int currentSeconds;
            //       while (gpioRead(attachedEchoPin))
            //             std::cout << "Waiting for echo to go down\n";
            //       // wait till echo H -> L
            //       gpioTime(PI_TIME_RELATIVE, &currentSeconds, &currentMicros); // take time

            //       /* COMPUTE DISTANCE */
            //       int pingTimeMicros = currentMicros - micros;
            //       float distance = (float)pingTimeMicros / 1000000 * SOUND_SPEED / 2;
            //       printf("%d, %f\n", i, distance);

            //       /* DELETE SPIKES*/
            //       float max_value = ((float)cm_distance + 2) / 100,
            //             min_value = ((float)cm_distance - 2) / 100;

            //       if (distance < min_value || distance > max_value) // ho superato cm_dist +-2 -> spike
            //       {
            //             printf("Spike detected\n");
            //             i--;
            //             continue; // don't show output and don't write files
            //       }

            //       /* SHOW OUTPUT AND WRITE DATA ON FILE*/
            //       printf("%d, %f\n", i, distance);

            //       logger << i;
            //       logger << (float)pingTimeMicros / 1000000 * SOUND_SPEED / 2;
            //       logger.end_row();

            //       /*ADD DELAY*/
            //       // gpioDelay(200000);
            // }

            // logger.close();
            for (int i = 0; i < 100; i++)
            {
                  gpioWrite(attachedTrigPin, 1);
                  // delay(1/1000);
                 
                  gpioDelay(15);
                  gpioWrite(attachedTrigPin, 0);
                
                  // int elapsed = 0;
                  // int start_time = 0;
                  // int s = 0;
                  // gpioTime(PI_TIME_RELATIVE, &s, &start_time);
                  // start_time = s * 1000000 + start_time;
                  // elapsed = 0;
                  // while (!gpioRead(attachedEchoPin) && elapsed < 1000000 && elapsed >= 0)
                  // {

                  //       gpioTime(PI_TIME_RELATIVE, &s, &elapsed);
                  //       elapsed = s * 1000000 + elapsed;
                  //       elapsed = elapsed - start_time;
                  // }
                  // cout << "TIME ELAPSED: " << elapsed << "\n";
                  // if (elapsed >= 1000000 || elapsed < 0)
                  // {
                  //       cout << "TIMED OUT]n";
                  //       i--;
                  //       continue;
                  // }
                  while(!gpioRead(attachedEchoPin));
                  int seconds;
                  int micros;
                  gpioTime(PI_TIME_RELATIVE, &seconds, &micros);
                  while (gpioRead(attachedEchoPin))   
                  {
                  }
                  int currentMicros;
                  int currentSeconds;
                  gpioTime(PI_TIME_RELATIVE, &currentSeconds, &currentMicros);
                  int pingTimeSeconds = currentSeconds - seconds;
                  int pingTimeMicros = currentMicros - micros;
                  float distance = (float)pingTimeMicros / 1000000 * SOUND_SPEED / 2;
                  /* DELETE SPIKES*/
                  // float max_value = ((float)cm_distance + 5) / 100,
                  //       min_value = ((float)cm_distance - 5) / 100;

                  if (distance < 0.0 || distance > 1.0) // ho superato cm_dist +-2 -> spike
                  {
                        printf("Spike detected\n");
                        i--;
                        continue; // don't show output and don't write files
                  }

                  printf("%d, %5f m\n", i, distance);

                  logger << i;
                  logger << (float)pingTimeMicros / 1000000 * SOUND_SPEED / 2;
                  logger.end_row();
                  gpioDelay(500);
                  // delay(0.2);
                  // gpioDelay(200000);
            }
            logger.close();
      }

      gpioTerminate();
}

/* unused function
void delay(long int micro_seconds)
{
      // Storing start time
      long int start_time = clock() / CLOCKS_PER_SEC * 1000000;

      // looping till required time is not achieved
      while (clock() / CLOCKS_PER_SEC * 1000000 < start_time + micro_seconds)
            ;
}
*/
