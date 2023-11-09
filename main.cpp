

/*LIBRARIES*/
#include <stdio.h>
#include <time.h>
#include <vector>
#include <string>
#include "../csvlogger/CsvLogger.hpp"
#include "../distance_sensor/include/DistanceSensor.hpp"
#include "../distance_sensor/include/UltrasonicSensor.hpp"
#include "../distance_sensor/include/InfraredSensor.hpp"
#include <pigpio.h>

/* CONSTANTS */
#define NUMERO_MISURE 100
#define ECHO_PIN 23
#define TRIG_PIN 22
#define DELAY_MISURA_US 200

using namespace std;

void effettua_misure_cm(DistanceSensor &sensore, float riferimento, int numero_misure, vector<float> &misure);
void scrivi_database(vector<float> misure, string name_file_to_create);
int main()
{
      gpioInitialise();

      ifstream file_misure("input_files/misure_test.txt");
      UltrasonicSensor sensoreUltrasuoni(TRIG_PIN, ECHO_PIN);
      //InfraredSensor sensoreInfrarossi(1);
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

      float misura_attuale = misura_minima;

      vector<float> misure;
      string nome_file;

      while (misura_attuale <= misura_massima)
      {
            misure.clear();
            cout << "Next measure: " << misura_attuale << " cm\n\nType '1' to start, other to stop immediately : ";
            scanf("%d", &choice);
            if (choice != 1)
            {
                  printf("Exiting program\n");
                  break;
            }

            effettua_misure_cm(sensoreUltrasuoni, misura_attuale, NUMERO_MISURE, misure);
            nome_file = "misure/misura" + to_string(misura_attuale) + ".csv";
            scrivi_database(misure,nome_file);
            misura_attuale += passo_misura;
      }

}

void effettua_misure_cm(DistanceSensor &sensore, float riferimento, int numero_misure, vector<float> &misure)
{
      // create file which name is string (see Constructor)
      float distance;
      for (int i = 0; i < numero_misure; i++)
      {
            distance = sensore.getDistanceInCentimeters();
            if (distance < 0)
            {
                  i--;
                  continue;
            }
            // salvo i valori su file
            misure.push_back(distance);
            gpioDelay(DELAY_MISURA_US);
      }
}

void scrivi_database(vector<float> misure, string name_file_to_create)
{
      CsvLogger database_misure(name_file_to_create);
      database_misure.write("index,distance\n");
      float misura;
      for(unsigned int i = 0; i < misure.size();i++){
            cout<< misure[i]<<endl;
            database_misure << i;
            misura = misure[i];
            database_misure << misura;
            database_misure.end_row();
      }

      database_misure.close();
}
