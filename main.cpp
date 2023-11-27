

/*LIBRARIES*/
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <cstring>
#include <string>
#include "../csvlogger/CsvLogger.hpp"
#include "../distance_sensor/include/DistanceSensor.hpp"
#include "../distance_sensor/include/UltrasonicSensor.hpp"
#include "../distance_sensor/include/InfraredSensor.hpp"
#include <pigpio.h>
#include "../meca500_ethercat_cpp/Robot.hpp"

/* CONSTANTS */
#define MISURE_PER_CICLO 100
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
            cerr << "Usage: " << argv[0] << " <sensor_type> <surface>" << endl;
            cerr << "Usage: " << argv[0] << " <sensor_type> <surface> <number_of_measures>" << endl;
            return 1;
      }

      // Convert the command line argument to lowercase for case-insensitive comparison
      string sensorType = argv[1];
      string surface = "";
      bool use_robot = false;
      unsigned int misure_per_ciclo = MISURE_PER_CICLO;
      Robot *robot = nullptr;
      if (argc > 2)
            surface = argv[2];
      if (argc > 3)
      {
            misure_per_ciclo = stoi(argv[3]);
      }
      if (argc > 4 && argv[4] == "r")
      {
            use_robot = true;
            robot = new Robot(200, 5000, "eth0", 0.0, 10);
            robot->reset_error();
            // robot.main();
            robot->set_conf(1, 1, -1);
            robot->move_pose(0, -240, 190, 90, 0, 0);
            robot->print_pose();
      }

      DistanceSensor *sensore = nullptr;

      if (sensorType == "ultrasonic")
      {
            sensore = new UltrasonicSensor(TRIG_PIN, ECHO_PIN);
      }
      else if (sensorType == "infrared")
      {
            sensore = new InfraredSensor(1U, Line(0.9838294117647063,-3.314615686274564));
      }
      else
      {
            cerr << "Invalid sensor type. Supported types: ultrasonic, infrared" << endl;
            return 1;
      }
      float offset = 0;
      if (use_robot)
      {
            offset = sensore->getDistanceInMillimeters();
      }

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
            if (!use_robot)
            {
                  cout << "Next measure: " << misura_attuale << " mm\n\nType '1' to start, other to stop immediately : ";
                  scanf("%d", &choice);
                  if (choice != 1)
                  {
                        printf("Exiting program\n");
                        break;
                  }
            }
            else
            {
                  // cout << "Next measure: " << misura_attuale << " mm\n";
                  // cout << "Moving robot to position..." << endl;
                  // robot->move_lin_rel_trf(misura_attuale, -240, 190, 90, 0, 0);
                  // printf("waiting for robot to finish moving");
                  // while (!robot->movement_ended())
                  // {
                  //       printf(".");
                  //       usleep(1e+6);
                  // }
                  // printf("\n");
                  // while (!robot->movement_ended())
                  //       ;
                  // cout << "Robot in position" << endl;
                  // cout << "Measuring" << endl;
            }

            effettua_misure(*sensore, misura_attuale, misure_per_ciclo, misure, DELAY_MISURA_US);
            for(float misura : misure)
                  cout << misura << endl;

            nome_file = "misure/" + sensorType + "/" + surface + "/misura" + to_string((int)misura_attuale) + ".csv";
            for (auto misura : misure)
            {
                  misura = misura - offset;
            }
            scrivi_database(misure, nome_file);
            misura_attuale += passo_misura;
      }
      if (use_robot)
      {
            robot->deactivate();
      }
      return 0;
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
