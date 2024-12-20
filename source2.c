#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

//gcc -pthread source.c -o o

void *hello_world(void *arg) {
    char *s = (char *) arg;
    pthread_t thread_id = pthread_self();
    printf("Thread ID: %ld, Hello! %s\n", thread_id, s);
    return (void*) thread_id;
}

int main(int argc, char* argv[]) {
    if(argc > 1){
        printf("argc = %d", argc);
        return EXIT_FAILURE;
    }
    pthread_t hello_world_thread;
    int result = pthread_create(&hello_world_thread, NULL, hello_world, (void *) argv[0]);
    if (result != 0) {
        perror("Could not create thread.");
        return 1;
    }

    void *thread_id;
    pthread_join(hello_world_thread, &thread_id);
    
    printf("Thread ID returned: %ld\n", (pthread_t) thread_id);
    printf("Main thread exiting\n");

    return 0;
}