

/*LIBRARIES*/
#include <stdio.h>
#include <time.h>
#include "../csvlogger/CsvLogger.hpp"
#include <pigpio.h>

/* CONSTANTS */
#define SOUND_SPEED 340
#define MAX_SENSOR_DISTANCE 200 // Maximum sensor distance can be as high as 500cm, no reason to wait for ping longer than sound takes to travel this distance and back. Default=500
#define US_ROUNDTRIP_CM 57      // Microseconds (uS) it takes sound to travel round-trip 1cm (2cm total), uses integer to save compiled code space. Default=57
#define US_ROUNDTRIP_IN 146     // Microseconds (uS) it takes sound to travel round-trip 1 inch (2 inches total), uses integer to save compiled code space. Default=146
#define ROUNDING_ENABLED false  // Set to "true" to enable distance rounding which also adds 64 bytes to binary size. Default=false // Set to "true" to enable support for the URM37 sensor in PWM mode. Default=false
#define TRIGGER_WIDTH 12
#define MAX_SENSOR_DELAY 5800 // Maximum uS it takes for sensor to start the ping. Default=5800

int main()
{
      using namespace std;
      const int attachedEchoPin = 17;
      const int attachedTrigPin = 18;
      std::ifstream file_misure("misure_da_prendere.txt");
      float cm_distance;
      char name_file_to_create[20];
      int choice;
      unsigned int _maxEchoTime = (unsigned int)MAX_SENSOR_DISTANCE * US_ROUNDTRIP_CM;
      unsigned long _max_time;
      unsigned long elapsed_time;

      gpioInitialise();
      gpioSetMode(attachedTrigPin, PI_OUTPUT);
      gpioSetMode(attachedEchoPin, PI_INPUT);

      while (file_misure >> cm_distance)
      {
            printf("Next measure: %fcm\n\nType '1' to start, other to stop immediately : ", cm_distance);
            scanf("%d", &choice);
            if (choice != 1)
            {
                  printf("Exiting program\n");
                  break;
            }
            sprintf(name_file_to_create, "prova%f.csv", cm_distance);
            CsvLogger logger(name_file_to_create);
            // create file which name is string (see Constructor)
            for (int i = 0; i < 100; i++)
            {
                  gpioTrigger(attachedTrigPin, 10, 1);
                  if (gpioRead(attachedEchoPin))
                  {
                        // Previous ping hasn't finished, abort.
                        i--;
                        continue;
                  }
                  _max_time = gpioTick() + _maxEchoTime + MAX_SENSOR_DELAY;
                  while (!gpioRead(attachedEchoPin))
                        if (gpioTick() > _max_time)
                        {
                              printf("Echo timed out\n");
                              i--;
                              continue;
                        }
                  elapsed_time = gpioTick() - _max_time - _maxEchoTime - MAX_SENSOR_DELAY;
                  float distance = (float)elapsed_time / 1000000 * SOUND_SPEED / 2;

                  printf("%d, %5f m\n", i, distance);

                  logger << i;
                  logger << (float)pingTimeMicros / 1000000 * SOUND_SPEED / 2;
                  logger.end_row();
                  gpioDelay(500);
            }

            logger.close();
      }
      gpioTerminate();
}

bool ping(float *distance)
{
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
