#include <iostream>
#include <csignal>
#include <unistd.h>
#include <termios.h>
#include <cstring>

volatile sig_atomic_t stopFlag = 0;

// Function to handle the interrupt signal
void handleSignal(int signum) {
    if (signum == SIGINT) {
        stopFlag = 1;
    }
}

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

    // Register the signal handler
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handleSignal;
    sigaction(SIGINT, &sa, nullptr);

    while (!stopFlag) {
        if (read(STDIN_FILENO, &userInput, 1) > 0) {  // Check if a key is pressed without blocking
            std::cout << "You pressed: '" << userInput << "'. Keep going!" << std::endl;
        }

        // Add some delay to avoid high CPU usage
        usleep(100000);  // Sleep for 100,000 microseconds (0.1 seconds)
    }

    std::cout << "Exiting the loop. You pressed '" << targetChar << "'." << std::endl;

    return 0;
}
