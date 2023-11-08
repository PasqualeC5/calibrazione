

/*LIBRARIES*/
#include <stdio.h>
#include <time.h>
#include "../csvlogger/CsvLogger.hpp"
#include <pigpio.h>

/* CONSTANTS */
#define SOUND_SPEED_MS 343
#define MAX_SENSOR_DISTANCE_CM 200 // Maximum sensor distance can be as high as 500cm, no reason to wait for ping longer than sound takes to travel this distance and back. Default=500
#define US_ROUNDTRIP_CM 57         // Microseconds (uS) it takes sound to travel round-trip 1cm (2cm total), uses integer to save compiled code space. Default=57
#define US_ROUNDTRIP_IN 146        // Microseconds (uS) it takes sound to travel round-trip 1 inch (2 inches total), uses integer to save compiled code space. Default=146
#define TRIGGER_WIDTH 12
#define MAX_SENSOR_DELAY 5800 // Maximum uS it takes for sensor to start the ping. Default=5800
#define NUMERO_MISURE 1000
#define attachedEchoPin 23
#define attachedTrigPin 22
int main()
{
      using namespace std;
      ifstream file_misure("input_files/misure_test.txt");
      ifstream file_superfici("input_files/superfici_test.txt");
      float cm_distance;
      char name_file_to_create[20];
      int choice;
      unsigned int _maxEchoTime = (unsigned int)MAX_SENSOR_DISTANCE_CM * US_ROUNDTRIP_CM; // tempo massimo di attesa echo in micro-secondi us
      unsigned long _max_time;
      unsigned int tempo = 0;
      unsigned long elapsed_time;

      gpioInitialise();
      gpioSetMode(attachedTrigPin, PI_OUTPUT);
      gpioSetMode(attachedEchoPin, PI_INPUT);

      cout << "massimo tempo di attesa: " << _maxEchoTime << "us" << endl;

      //lettura iniziale del file
      //assegno il range di misura
      float misura_minima; 
      float misura_massima;
      int numero_misure;

      file_misure >> misura_minima;
      file_misure >> misura_massima;
      file_misure >> numero_misure;

      float passo_misura = (misura_massima - misura_minima) / numero_misure;

      int misura_attuale = misura_minima;

      char superficie[20];
      while(file_superfici >> superficie){
            
      }

      while (misura_attuale <= misura_massima)
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
            gpioWrite(attachedTrigPin, 0);
            for (int i = 0; i < NUMERO_MISURE; i++)
            {
                  // Invia un impulso di trigger di durata TRIGGER_WIDTH
                  // cout << "Trigger: " << gpioTrigger(attachedTrigPin, TRIGGER_WIDTH, 1) << endl;

                  gpioWrite(attachedTrigPin, 1);
                  gpioDelay(30);
                  gpioWrite(attachedTrigPin, 0);

                  // Se il pin di echo ha un valore alto vuol dire che sto processando un trigger precendete
                  if (gpioRead(attachedEchoPin))
                  {
                        // Previous ping hasn't finished, abort.
                        i--;
                        gpioDelay(500);
                        continue;
                  }
                  // calcolo il massimo valore di attesa per l'ecbo
                  _max_time = gpioTick() + _maxEchoTime + MAX_SENSOR_DELAY;

                  // attendo che il pin di echo si alzi
                  while (!gpioRead(attachedEchoPin) && gpioTick() < _max_time)
                  {
                  }
                  if (gpioTick() >= _max_time)
                  {
                        // se il tempo trascorso supera il valore massimo vado in time out
                        printf("Echo timed out\n");
                        cout << gpioTick() << endl;
                        i--;
                        continue;
                  }
                  tempo = gpioTick();
                  while (gpioRead(attachedEchoPin))
                  {
                  }

                  // calcolo il tempo trascorso tra trigger e ricezione di echo (ping time)
                  elapsed_time = gpioTick() - tempo;
                  // calcolo la distanza in base al tempo trascorso
                  float distance = (float)elapsed_time / 1000000 * SOUND_SPEED_MS / 2;

                  // spike detection
                  if (distance < 0.0 || distance > 1.0) // ho superato cm_dist +-2 -> spike
                  {
                        printf("Spike detected\n");
                        i--;
                        continue; // don't show output and don't write files
                  }
                  printf("%d, %5f m\n", i, distance);

                  // salvo i valori su file
                  logger << i;
                  logger << (float)elapsed_time / 1000000 * SOUND_SPEED_MS / 2;
                  logger.end_row();
                  gpioDelay(500);
            }

            logger.close();

            misura_attuale += passo_misura;
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
