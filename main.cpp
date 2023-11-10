

/*LIBRARIES*/
#include <stdio.h>
#include <time.h>
#include <vector>
#include <cstring>
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
#define AUTO 2U
#define USER_INPUT 1U

using namespace std;

void effettua_misure(DistanceSensor &sensore, float riferimento, int numero_misure, vector<float> &misure, unsigned int delay_us);
void scrivi_database(vector<float> misure, string name_file_to_create);
int main(int argc, char *argv[])
{
      gpioInitialise();

      ifstream file_misure("input_files/misure_test.txt");

      // Check if the correct number of command line arguments is provided
      if (argc < 2)
      {
            cerr << "Usage: " << argv[0] << " <sensor_type>" << endl;
            return 1;
      }

      // Convert the command line argument to lowercase for case-insensitive comparison
      string sensorType = argv[1];
      string surface = "";
      if (argc > 2)
            surface = argv[2];
      // transform(sensorType.begin(), sensorType.end(), sensorType.begin(), ::tolower);

      DistanceSensor *sensore = nullptr;

      if (sensorType == "ultrasonic")
      {
            sensore = new UltrasonicSensor(TRIG_PIN, ECHO_PIN);
      }
      else if (sensorType == "infrared")
      {
            sensore = new InfraredSensor(AUTO);
      }
      else
      {
            cerr << "Invalid sensor type. Supported types: ultrasonic, infrared" << endl;
            return 1;
      }

      // UltrasonicSensor sensoreUltrasuoni(TRIG_PIN, ECHO_PIN);
      // InfraredSensor sensoreInfrarossi(1U);

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
            cout << "Next measure: " << misura_attuale << " mm\n\nType '1' to start, other to stop immediately : ";
            scanf("%d", &choice);
            if (choice != 1)
            {
                  printf("Exiting program\n");
                  break;
            }

            effettua_misure(*sensore, misura_attuale, NUMERO_MISURE, misure, DELAY_MISURA_US);
            // effettua_misure(sensoreUltrasuoni, misura_attuale, NUMERO_MISURE, misure, DELAY_MISURA_US);

            nome_file = "misure/" + surface + "/" + sensorType + "_misura" + to_string((int)misura_attuale) + ".csv";
            scrivi_database(misure, nome_file);
            misura_attuale += passo_misura;
      }
}

void effettua_misure(DistanceSensor &sensore, float riferimento, int numero_misure, vector<float> &misure, unsigned int delay_us)
{
      // create file which name is string (see Constructor)
      float distance;
      for (int i = 0; i < numero_misure; i++)
      {
            distance = sensore.getDistanceInMillimeters();
            if (distance < 0)
            {
                  i--;
                  continue;
            }
            // salvo i valori su file
            misure.push_back(distance);
            gpioDelay(delay_us);
      }
}

void scrivi_database(vector<float> misure, string name_file_to_create)
{
      CsvLogger database_misure(name_file_to_create);
      database_misure.write("index,distance\n");
      float misura;
      for (unsigned int i = 0; i < misure.size(); i++)
      {
            // cout << misure[i] << endl;
            database_misure << i;
            misura = misure[i];
            database_misure << misura;
            database_misure.end_row();
      }

      database_misure.close();
}
