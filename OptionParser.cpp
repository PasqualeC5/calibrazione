#include "OptionParser.hpp"

OptionParser::OptionParser(std::vector<Option> options) : options(std::move(options)) {}

void OptionParser::handleOption(const Option& option, const char* argument) {
    std::cout << "Option " << option.name << " specified";
    if (option.hasArgument && argument) {
        std::cout << " with value: " << argument;
    }
    std::cout << "\n";
    // Call the specified handler function
    if (option.handler) {
        option.handler(argument);
    }
}

const Option* OptionParser::findOption(const char* arg) const {
    auto it = std::find_if(options.begin(), options.end(),
                           [arg](const Option& opt) { return strcmp(opt.name, arg) == 0; });

    return (it != options.end()) ? &(*it) : nullptr;
}

void OptionParser::parse(int argc, char* argv[]) const {
    // Iterate through each command line argument
    for (int i = 1; i < argc; ++i) {
        // Check if the argument is an option (starts with '-')
        if (argv[i][0] == '-') {
            // Find the corresponding option in the options vector
            const Option* option = findOption(argv[i]);

            if (option) {
                // Process the option
                if (option->hasArgument) {
                    // Check if there is an additional argument
                    if (i + 1 < argc) {
                        // Handle the option with its additional argument
                        handleOption(*option, argv[i + 1]);
                        ++i;  // Skip the next argument as it has been processed
                    } else {
                        std::cerr << "Option " << option->name << " requires an additional argument.\n";
                        // Handle the case where the option is not followed by an argument
                    }
                } else {
                    // Handle the option without an additional argument
                    handleOption(*option);
                }
            } else {
                std::cerr << "Unknown option: " << argv[i] << "\n";
                // Handle unknown option
            }
        } else {
            // Process non-option arguments
            std::cout << "Non-option argument: " << argv[i] << "\n";
            // Handle non-option argument
        }
    }
}
