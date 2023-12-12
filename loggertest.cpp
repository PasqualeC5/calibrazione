/*LIBRARIES*/
#include "../csvlogger/CsvLogger.hpp"
#include <vector>
#include <string>
using namespace std;
int main(int argc, char const *argv[])
{
    if (argc < 2)
        return 1;
    vector<float> values;
    for (int i = 0; i < 100; i++)
    {
        values.push_back(i);
    }

    write_measurements_to_csv(values, argv[1]);

    return 0;
}
void write_measurements_to_csv(vector<float> measurments, string file_path)
{
    CsvLogger measurements_logger(file_path);
    measurements_logger.write("distance\n");
    for (float measurement : measurments)
    {
        measurements_logger << measurement;
        measurements_logger.end_row();
    }

    measurements_logger.close();
}