#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5
#define TIMES 2   // reduce iterations

sem_t chopstick[N];
sem_t room;

void* philosopher(void* arg) {
    int i = *(int*)arg;

    for (int k = 0; k < TIMES; k++) {

        sem_wait(&room);

        sem_wait(&chopstick[i]);
        sem_wait(&chopstick[(i + 1) % N]);

        // Only print important event
        printf("Philosopher %d is eating (%d/%d)\n", i, k+1, TIMES);

        sleep(1);

        sem_post(&chopstick[i]);
        sem_post(&chopstick[(i + 1) % N]);

        sem_post(&room);
    }

    return NULL;
}

int main() {
    pthread_t t[N];
    int id[N];

    sem_init(&room, 0, N - 1);

    for (int i = 0; i < N; i++)
        sem_init(&chopstick[i], 0, 1);

    for (int i = 0; i < N; i++) {
        id[i] = i;
        pthread_create(&t[i], NULL, philosopher, &id[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(t[i], NULL);

    return 0;
}
