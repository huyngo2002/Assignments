#include <stdlib.h> //standard stuff
#include <sys/mman.h> //mmap()
#include <stdio.h> //io
#include <unistd.h> //sleep
#include <semaphore.h> //semaphore
#include <time.h> //time
#include <pthread.h> //pthread_create(), pthread_join()
#include <signal.h> //signal()
#include <stdint.h>
#include <math.h>

#define NRUN 3
#define NPHI 5

int countLoop[NPHI];
int sum[NPHI];
int totalAveTime;

int chopsticks;

sem_t waiterPro;
sem_t chopNum;
sem_t waitLChop;
pthread_cond_t eatenCond;
pthread_mutex_t eatenMutex;
uint8_t eaten;
int currChop;

void *philosopher(void* arg);

bool run = true;
void sig_handler(int signum)
{
    printf("Terminate program, stop running all threads\n");
    run = false;
    eaten = 0;
    pthread_cond_broadcast(&eatenCond);
}

void requestLeftChop(int pos)
{
    pthread_mutex_lock(&eatenMutex);
    while(eaten & pos) {
        pthread_cond_wait(&eatenCond, &eatenMutex);
    } 
    pthread_mutex_unlock(&eatenMutex);

    while(true) {
        sem_wait(&waiterPro);
        sem_getvalue(&chopNum, &currChop);
        if(currChop < 2) {
            sem_post(&waiterPro);
            sem_wait(&waitLChop);
        }
        else {
            sem_wait(&chopNum);
            sem_post(&waiterPro);
            break;
        }
    }
}

void requestRightChop(int pos)
{
    sem_wait(&waiterPro);
    sem_getvalue(&chopNum, &currChop);
    if(currChop > 0) {
        sem_wait(&chopNum);
        sem_post(&waiterPro);
    }
    else {
        sem_post(&waiterPro);
        sem_wait(&chopNum);
    }
    pthread_mutex_lock(&eatenMutex);
    eaten |= 1 << pos;
    if(eaten == 62) {
        eaten = 0;
        pthread_cond_broadcast(&eatenCond);
    }
    pthread_mutex_unlock(&eatenMutex);
}

void releaseChops(int pos)
{
    sem_wait(&waiterPro);
    sem_post(&chopNum);
    sem_post(&chopNum);
    int temp;
    sem_getvalue(&waitLChop, &temp);
    if(temp <= 0) {
        sem_post(&waitLChop); 
    }  
    sem_post(&waiterPro); 
}

int main()
{
    //Input number of chopsticks
    chopsticks = -1;
    while (chopsticks < 5 || chopsticks > 10)
    {
        printf("Please input the number of chopsticks(from 5 to 10): ");
        scanf("%d", &chopsticks);
    }

    //Register handle signal
    signal(SIGINT, sig_handler);
    signal(SIGQUIT, sig_handler);

    //Init semaphore
    sem_init(&waiterPro, 0, 1);
    sem_init(&waitLChop, 0, 0);
    sem_init(&chopNum, 0, chopsticks);

    totalAveTime = 0;
    eaten = 0;
    pthread_t Philosopher[NPHI];
    int result;
    int pID[NPHI] = {1, 2, 3, 4, 5};
    for(int i = 0; i < NPHI; ++i) {
        countLoop[i] = 3;
        sum[i] = 0;
        result = pthread_create(&Philosopher[i], NULL, philosopher, (void*)&pID[i]);
        if (result != 0)
        {
            printf("Error creating thread\n");
        }
        else
        {
            printf("-> Philosopher %d starts with id: %ld\n", pID[i], Philosopher[i]);
        }
    }

    for(int i = 0; i < NPHI; i++) {
        pthread_join(Philosopher[i], NULL);
    }

    for(int i = 0; i < NPHI; i++) {
        totalAveTime += sum[i];
    }

    printf("\nAverage waiting time of a philosopher is %.2f seconds\n\n", (double)totalAveTime/NRUN/NPHI);

    printf("Program SUCCESS!\n");
    exit(0);
}

void* philosopher(void* arg)
{
    int id = *((int*)arg);
    int index = id - 1;

    time_t begin, end;
    while(run && countLoop[index] > 0)
    {
        printf("Philosopher %d is thinking...\n", id);
        sleep(1 + rand() % 5);  //Thinking
        printf("Philospher %d is hungry\n", id);
        
        begin = time(NULL);
        requestLeftChop((int)pow(2, id));
        printf("Philospher %d has picked up left chopstick\n", id);
        
        requestRightChop(id);
        printf("Philospher %d has picked up right chopstick\nPhilosopher %d is eating...\n", id, id);
        end = time(NULL);
        //calculate
        sum[index] += (end - begin);
        if(countLoop[index] == 1) {
            printf("Average waiting time of Philosopher %d is %.2f seconds\n", id, (double)sum[index]/NRUN);
        }
        sleep(5);   //Eating
        printf("Philospher %d is done eating\n", id);
        releaseChops(id);
        countLoop[index]--;
    }
    pthread_exit(NULL);
}
