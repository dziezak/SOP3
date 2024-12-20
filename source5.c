#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_COUNT 16


int counter = 0;
pthread_mutex_t counter_lock;

void *reader_thread0(void *arg) {
    pthread_t thread_id = pthread_self();
    printf("{%d} Start reader.\n", thread_id);
    pthread_mutex_lock(&counter_lock);
    int temp = counter;
    sleep(1);
    pthread_mutex_unlock(&counter_lock);
    printf("{%d} Read %d.\n ", thread_id, temp);
}

void *writer_thread0(void *arg) {
    pthread_t thread_id = pthread_self();
    printf("{%d} Start writer.\n", thread_id);
    pthread_mutex_lock(&counter_lock);
    int temp = counter;
    temp += 1;
    sleep(1);
    counter = temp;
    pthread_mutex_unlock(&counter_lock);
    printf("{%d} Written %d.\n", thread_id, temp);
}

void *reader_thread(void *arg){
    pthread_t thread_id = thead_self();
    printf("{%d} Start readed\n", thread_id);
    pthread_rwlock_rdlock(&counter_lock);
    int temp = counter;
    sleep(1);
    pthread_rwlock_rdlock(&counter_lock);
    printf("{%d} Read %d\n", thread_id, temp);
}

void *writer_thread(void *arg){
    pthread_t thread_id = thead_self();
    printf ("{%d} Start writing")
}

int main(int argc, char* argv[]) {
    pthread_t threads[THREAD_COUNT];

    pthread_mutex_init(&counter_lock, NULL);

    for (int i = 0; i < THREAD_COUNT; i++) {
        int result;
        if ((i == 4) || (i == 12)) {
          result = pthread_create(&(threads[i]), NULL, writer_thread, NULL);
        } else {
          result = pthread_create(&(threads[i]), NULL, reader_thread, NULL);
        }
        if (result != 0) {
            perror("Could not create thread.");
        }
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&counter_lock);

    printf("\nCounter value after executing %d threads is %d.\n", THREAD_COUNT, counter);
    return 0;
}