#include <iostream>
#include <unistd.h>
#include <termios.h>

// Function to set the terminal to non-blocking mode
void setNonBlockingMode() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~ICANON;
    t.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

int main() {
    char targetChar = 'q';  // Change this to the character you want to be the exit condition
    char userInput;

    setNonBlockingMode();

    std::cout << "Press '" << targetChar << "' to exit the loop." << std::endl;

    while (true) {
        if (read(STDIN_FILENO, &userInput, 1) > 0) {
            std::cout << "You pressed: '" << userInput << "'. Keep going!" << std::endl;

            if (userInput == targetChar) {
                break;  // Exit the loop when the target character is pressed
            }
        }

        // Add some delay to avoid high CPU usage
        usleep(100000);  // Sleep for 100,000 microseconds (0.1 seconds)
    }

    std::cout << "Exiting the loop. You pressed '" << targetChar << "'." << std::endl;

    return 0;
}
