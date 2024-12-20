#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

//Let's kill thread earlier
//Remember about memory

void *hello_world(void *arg) {
    char *s = (char *) arg;
    printf("Hello %s!\n", s);

    pthread_t thread_id = pthread_self();
    printf("Thread {%d} said: %s\n", thread_id, s);

    int *result = malloc(sizeof(int));
    *result = 15;
    pthread_exit(result);

    printf("Not shown\n");
}

int main(int argc, char* argv[]) {
    pthread_t hello_world_thread;
    int result = pthread_create(&hello_world_thread, NULL, hello_world, (void *) argv[1]);
    if (result != 0) {
        perror("Could not create thread.");
    }

    int *hello_world_result;
    pthread_join(hello_world_thread, (void **) &hello_world_result);
    printf("Thread returned, %d.\n", *hello_world_result);

    free(hello_world_result); // fajna rzecz na zadanie aby pamietac o zwolnieniu pamieci

    return 0;
}