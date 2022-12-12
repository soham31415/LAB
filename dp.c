#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>

sem_t f[5];

void *philosopher(void *n)
{
    int np = *(int *)n;
    printf("\nPhilosopher %d is hungry", np);
    printf("\nPhilosopher %d tries to pick up his left fork", np);
    sem_wait(&f[np]);
    printf("\nPhilosopher %d picks up his left fork", np);
    printf("\nPhilosopher %d tries to pick up his right fork", np);
    sem_wait(&f[(np+1)%5]);
    printf("\nPhilosopher %d picks up his right fork", np);
    printf("\nPhilosopher %d is eating", np);
    sleep(2);
    printf("\nPhilosopher %d is done eating", np);
    sem_post(&f[np]);
    printf("\nPhilosopher %d puts down his left fork", np);
    sem_post(&f[(np+1)%5]);
    printf("\nPhilosopher %d puts down his right fork", np);
}

int main()
{
    int i, p[5];
    pthread_t t[5]; //5 threads for 5 philosophers

    for(i=0; i<5; i++)
    {
        sem_init(&f[i], 0, 1);
    }

    for(i=0; i<5; i++)
    {
        p[i] = i;
        pthread_create(&t[i], NULL, philosopher, (void *)&p[i]);
    }

    for(i=0; i<5; i++)
    {
        pthread_join(t[i], NULL);
    }
}
