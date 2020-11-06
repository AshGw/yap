#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 2

char buffer[BUFFER_SIZE];
int buffer_index = 0;

sem_t empty, full;
pthread_mutex_t mutex;

void *produce(void *arg) {
    char item = *((char *)arg);
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);
    buffer[buffer_index] = item;
    printf("Produced: %c\n", item);
    buffer_index = (buffer_index + 1) % BUFFER_SIZE;
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
    pthread_exit(NULL);
}


int main() {
    pthread_t threadA, threadB, threadC;
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    char itemA = 'A';
    char itemB = 'B';
    char itemC = 'C';
    
    pthread_create(&threadA, NULL, produce, (void *)&itemA);
    pthread_create(&threadB, NULL, produce, (void *)&itemB);
    pthread_create(&threadC, NULL, produce, (void *)&itemC);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    return 0;
}
