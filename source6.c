#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define PUSH_THREAD_COUNT 8
#define POP_THREAD_COUNT 2
#define STACK_SIZE 6

int stack[STACK_SIZE];
int stack_pointer = 0;

pthread_mutex_t stack_lock;
pthread_cond_t stack_condition;

void *push_thread(void* arg){
    int value = *((int *) arg);

    pthread_mutex_lock(&stack_lock);

    //Stack is full: wait (release mutex for the duration)
    while (stack_pointer >= STACK_SIZE){
        printf("Waiting to push value %d\n", value);
        pthread_cond_wait(&stack_condition, &stack_lock);
    }

    //There's room in the stack: put more stuff on and notify all
    printf("Pushing value %d.\n", value);
    stack[stack_pointer++] = value;
    sleep(1);
    pthread_cond_broadcast(&stack_condition);

    pthread_mutex_unlock(&stack_lock);
}

void *pop_thread(void * arg){
    pthread_mutex_lock(&stack_lock);
    
    //Stack is empty: wait (release mutex for the duration)
    while (stack_pointer <= 0){
        printf("Waiting to pop value.\n");
        pthread_cond_wait(&stack_condition, &stack_lock);
    }

    //There's room in the stack: put more stuff on and notify all
    int value = stack[--stack_pointer];
    stack[stack_pointer] = 0;
    printf("Popping value %d\n", value);
    sleep(1);
    pthread_cond_broadcast(&stack_condition);

    pthread_mutex_unlock(&stack_lock);
}

int main(int argc, char* argv[]){
    pthread_t pop_threads[POP_THREAD_COUNT];
    pthread_t push_threads[PUSH_THREAD_COUNT];

    pthread_mutex_init(&stack_lock, NULL);
    pthread_cond_init(&stack_condition, NULL);

    for(int i=0; i<POP_THREAD_COUNT; i++){
        int result = pthread_create(&(pop_threads[i]), NULL, pop_thread, NULL);
        if(result != 0){
            perror("Could not create pop thread.");
        }
    }

    for(int i=0; i< PUSH_THREAD_COUNT; i++){
        int *value = (int*) malloc(sizeof(int));
        (*value) = i + 1;
        int result = pthread_create(&(push_threads[i]), NULL, push_thread, value);
        if(result != 0){
            perror("Could not create push thread.");
        }
    }

    for(int i=0; i<PUSH_THREAD_COUNT; i++){
        pthread_join(push_threads[i], NULL);
    }

    for(int i=0; i<PUSH_THREAD_COUNT; i++){
        pthread_join(pop_threads[i], NULL);
    }

    pthread_mutex_destroy(&stack_lock);
    printf("\n Stack after execution od %d push and %d pop threads.\n", PUSH_THREAD_COUNT, POP_THREAD_COUNT);
    for(int i=0; i<stack_pointer; i++){
        printf("[%d] => %d\n", i, stack[i]);
    }
    return 0;
}