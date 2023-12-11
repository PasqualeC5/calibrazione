#include "CsvLogger.hpp"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sys/stat.h>

// #define LOGGING_DISABLED TRUE

CsvLogger::CsvLogger(const std::string filename) : FILENAME(filename.c_str())
{
    std::ofstream file;

    // Check if the path exists
    // struct stat info;
    // if (stat(filename.c_str(), &info) != 0) {
    //     // Create the necessary folders
    //     int status = mkdir(filename.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    //     if (status != 0) {
    //         std::cerr << "Error creating directories" << std::endl;
    //         exit(1);
    //     }
    // }


    file.open(filename);
    if (!file.is_open())
    {
        printf("impossibile aprire il file di log. esco...");
        exit(1);
    }
    file.precision(5);
}

CsvLogger::~CsvLogger()
{
    flush();
    file.close();
}

void CsvLogger::write(const std::string header)
{
    file << header;
    file.flush();
}

void CsvLogger::flush()
{
    file.flush();
}

CsvLogger &CsvLogger::operator<<(const double new_val)
{
#ifndef LOGGING_DISABLED
    // file << std::scientific << new_val << ',';
    file << new_val << ',';
#endif
    return *this;
}

void CsvLogger::end_row()
{
#ifndef LOGGING_DISABLED
    file << '\n';
#endif
}

void CsvLogger::close()
{
    flush();
    file.close();
}