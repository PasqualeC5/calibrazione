#include "CsvLogger.hpp"
#include <stdio.h>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdlib>

// #define LOGGING_DISABLED TRUE

CsvLogger::CsvLogger(const std::string filename) : FILENAME(filename.c_str())
{
    file.open(filename);
    if (!file.is_open())
    {
        printf("impossibile aprire il file di log. esco...");
        exit(1);
    }
    file.precision(5);
}

// Function to create directories in the given path
void CsvLogger::createDirectories(const std::string& path)
{
    size_t pos = 0;
    std::string token;
    std::string delimiter = "/";
    std::string directory;

    while ((pos = path.find(delimiter)) != std::string::npos)
    {
        token = path.substr(0, pos);
        directory += token + "/";
        if (mkdir(directory.c_str(), S_IRWXU) != 0 && errno != EEXIST)
        {
            std::cerr << "Error creating directories. Exiting..." << std::endl;
            exit(1);
        }
        path.erase(0, pos + delimiter.length());
    }
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