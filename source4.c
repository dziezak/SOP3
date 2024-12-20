#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

//time to use more than one thread
#define THREAD_COUNT 16

int counter = 0;

//tworzymy thread
void *incrementer_thread(void *arg) {
    printf("Start thread.");
    int temp = counter;
    sleep(1);
    counter = temp + 1;
    printf("Done.");
}

int main(int argc, char* argv[]) {
    pthread_t incrementer_threads[THREAD_COUNT];

    for (int i = 0; i < THREAD_COUNT; i++) {
        int result = pthread_create(&(incrementer_threads[i]), NULL, incrementer_thread, NULL);
            if (result != 0) {
                perror("Could not create thread.");
        }
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
            pthread_join(incrementer_threads[i], NULL);
    }

    printf("\nCounter value after executing %d threads is %d.\n", THREAD_COUNT, counter);
    return 0;
}