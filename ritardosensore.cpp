#include <iostream>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>

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
    sa.sa_handler = handleSignal;
    sigaction(SIGINT, &sa, nullptr);

    while (!stopFlag) {
        fd_set inputSet;
        FD_ZERO(&inputSet);
        FD_SET(STDIN_FILENO, &inputSet);

        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 100000;  // 100,000 microseconds (0.1 seconds)

        int ready = select(STDIN_FILENO + 1, &inputSet, nullptr, nullptr, &timeout);

        if (ready > 0 && FD_ISSET(STDIN_FILENO, &inputSet)) {
            if (read(STDIN_FILENO, &userInput, 1) > 0) {
                std::cout << "You pressed: '" << userInput << "'. Keep going!" << std::endl;

                if (userInput == targetChar) {
                    stopFlag = 1;
                }
            }
        }
    }

    std::cout << "Exiting the loop. You pressed '" << targetChar << "'." << std::endl;

    return 0;
}
