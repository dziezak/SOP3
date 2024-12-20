#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *hello_world(void *arg) {
    char *s = (char *) arg;
    printf("Hello %s!\n", s);
    return 0;
}

int main(int argc, char* argv[]) {
    pthread_t hello_world_thread;
    int result = pthread_create(&hello_world_thread, NULL, hello_world, (void *) argv[0]);
    if (result != 0) {
        perror("Could not create thread.");
    }
    //One way to solve problem
    //sleep(3);
    //better way to solve problem
    pthread_join(hello_world_thread, NULL);
    printf("Main thread exiting.\n");
    return 0;
}