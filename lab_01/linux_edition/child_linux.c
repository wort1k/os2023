#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

volatile sig_atomic_t flag = 0; 
void signal_handler(int signal)
{
    switch (signal) {
    case SIGINT:
        printf("Signal: SIGINT (%d)\n", signal);
        break;
    case SIGTERM:
        printf("Signal: SIGTERM (%d)\n", signal);
        break;
    default:
        printf("Unknown signal\n");
        break;
    }

    flag = 1;
}

int main(int argc, char** argv)
{
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    while (!flag) {
        usleep(100000); 
    }

    printf("Exiting the program.\n");
    return 0;
}
