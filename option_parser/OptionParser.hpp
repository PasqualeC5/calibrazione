#ifndef OPTION_PARSER_H
#define OPTION_PARSER_H

#include <iostream>
#include <cstring>
#include <vector>

// Forward declaration of the handler function type
using OptionHandler = void (*)(const char*);

// Struct to represent an option
struct Option {
    const char* name;
    bool hasArgument;
    const char* description;
    OptionHandler handler; // Function pointer for option handling
};

class OptionParser {
public:
    OptionParser(std::vector<Option> options);

    // Function to handle options
    void handleOption(const Option& option, const char* argument = nullptr);

    // Function to find the corresponding Option for a given command line argument
    const Option* findOption(const char* arg) const;

    // Main function to parse command line arguments
    void parse(int argc, char* argv[]) const;

private:
    std::vector<Option> options;
};

#endif // OPTION_PARSER_H
