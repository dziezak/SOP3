#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

//time to use more than one thread

#define THREAD_COUNT 16
pthread_mutex_t counter_lock;

int counter = 0;
//niepoprawne udostepnianie srodkow do plikow
void *incrementer_thread0(void *arg) {
    pthread_t thread_id = pthread_self();
    printf("Start thread {%d}.\n", thread_id);
    int temp = counter;
    sleep(1);
    counter = temp + 1;
    printf("Done thread {%d}.\n", thread_id);
}

void *incrementer_thread(void *arg){
    pthread_t thread_id = pthread_self();
    printf("Start thread {%d}.\n", thread_id);
    pthread_mutex_lock(&counter_lock);
    int temp = counter;
    sleep(1);
    counter = temp + 1;
    pthread_mutex_unlock(&counter_lock);
    printf("Done thread {%d}.\n", thread_id);
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