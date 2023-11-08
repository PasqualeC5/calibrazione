

/*LIBRARIES*/
#include <stdio.h>
#include <time.h>
#include "../csvlogger/CsvLogger.hpp"
#include "../distance_sensor/DistanceSensor.hpp"
#include "../distance_sensor/UltrasonicSensor.hpp"
#include <pigpio.h>

/* CONSTANTS */
#define SOUND_SPEED_MS 343
#define MAX_SENSOR_DISTANCE_CM 200 // Maximum sensor distance can be as high as 500cm, no reason to wait for ping longer than sound takes to travel this distance and back. Default=500
#define US_ROUNDTRIP_CM 57         // Microseconds (uS) it takes sound to travel round-trip 1cm (2cm total), uses integer to save compiled code space. Default=57
#define US_ROUNDTRIP_IN 146        // Microseconds (uS) it takes sound to travel round-trip 1 inch (2 inches total), uses integer to save compiled code space. Default=146
#define TRIGGER_WIDTH 30
#define MAX_SENSOR_DELAY 5800 // Maximum uS it takes for sensor to start the ping. Default=5800
#define NUMERO_MISURE 1000
#define ECHO_PIN 23
#define TRIG_PIN 22
#define DELAY_MISURA_US 500

void effettua_misure(float riferimento, int numeroMisure, CsvLogger &logger);

int main()
{
      using namespace std;
      ifstream file_misure("input_files/misure_test.txt");
      ifstream file_superfici("input_files/superfici_test.txt");
      DistanceSensor sensoreUltrasuoni = UltrasonicSensor(ECHO_PIN, TRIG_PIN);
      float cm_distance;
      char name_file_to_create[20];
      int choice;

      // lettura iniziale del file
      // assegno il range di misura
      float misura_minima;
      float misura_massima;
      int numero_misure;

      file_misure >> misura_minima;
      file_misure >> misura_massima;
      file_misure >> numero_misure;

      float passo_misura = (misura_massima - misura_minima) / numero_misure;

      int misura_attuale = misura_minima;

      char superficie[20];

      while (misura_attuale <= misura_massima)
      {
            printf("Next measure: %fcm\n\nType '1' to start, other to stop immediately : ", cm_distance);
            scanf("%d", &choice);
            if (choice != 1)
            {
                  printf("Exiting program\n");
                  break;
            }
            sprintf(name_file_to_create, "misura_%f.csv", misura_attuale);
            CsvLogger logger(name_file_to_create, logger);

            effettua_misure(sensoreUltrasuoni, misura_attuale, NUMERO_MISURE, logger);
            misura_attuale += passo_misura;
            logger.close();
      }
}
}

void effettua_misure(DistanceSensor &sensore, float riferimento, int numero_misure, CsvLogger &logger)
{
      // create file which name is string (see Constructor)
      float distance;
      for (int i = 0; i < numero_misure; i++)
      {
            distance = sensore.getDistanceInCentimeters();
            // salvo i valori su file
            logger << i;
            logger << distance;
            logger.end_row();
            gpioDelay(DELAY_MISURA_US);
      }
}