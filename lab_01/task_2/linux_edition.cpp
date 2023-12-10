
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t isRunning = 1;

void signalHandler(int signal) {
    if (signal == SIGINT) {
        printf("Ctrl-C event\n");
        isRunning = 0;
    }
}

void* printRandomNumber(void*) {
    while (isRunning) {
        printf("%f\n", (double)rand() / RAND_MAX);
        usleep(1500000);
    }
    return nullptr;
}

void* reverseString(void*) {
    while (isRunning) {
        char str[250];
        scanf("%s", str);
        int len = strlen(str);
        for (int i = len - 1; i >= 0; --i) {
            printf("%c", str[i]);
        }
        printf("\n");
    }
    return nullptr;
}

int main() {
    signal(SIGINT, signalHandler);

    pthread_t thread1, thread2;
    int first, second;

    first = pthread_create(&thread1, NULL, printRandomNumber, NULL);
    if (first != 0) {
        fprintf(stderr, "Error creating thread 1\n");
        return 1;
    }

    second = pthread_create(&thread2, NULL, reverseString, NULL);
    if (second != 0) {
        fprintf(stderr, "Error creating thread 2\n");
        isRunning = 0;  
        pthread_cancel(thread1);  
        pthread_join(thread1, NULL);  
        return 1;
    }


    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}


