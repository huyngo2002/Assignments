#include <stdlib.h> //standard stuff
#include <sys/mman.h> //mmap()
#include <stdio.h> //io
#include <unistd.h> //sleep
#include <semaphore.h> //semaphore
#include <time.h> //time
#include <pthread.h> //pthread_create(), pthread_join()
#include <signal.h> //signal()

#define BUFFER_SIZE 10

int *vegan_tray = NULL;
int *nonVegan_tray = NULL;

sem_t mutex_v;
sem_t full_v;
sem_t empty_v;
sem_t mutex_nv;
sem_t full_nv;
sem_t empty_nv;

int in_v = 0;
int out_v = 0;
int in_nv = 0;
int out_nv = 0;

void *vegan_chef(void* arg);
void *nonVegan_chef(void* arg);
void *vegan_customer(void* arg);
void *nonVegan_customer(void* arg);
void *hybrid_customer(void* arg);

bool run = true;
void sig_handler(int signum)
{
    printf("Terminate program, stop running all threads\n");
    run = false;
}

int main()
{
    //Create memory
    vegan_tray = (int*)malloc(BUFFER_SIZE * sizeof(int));
    nonVegan_tray = (int*)malloc(BUFFER_SIZE * sizeof(int));

    if(vegan_tray == NULL || nonVegan_tray == NULL)
    {
        printf("Cannot allocate buffer!\n");
        exit(0);
    }

    //Initialize buffer to be all 0's
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        vegan_tray[i] = 0;
        nonVegan_tray[i] = 0;
    }

    //Register handle signal
    signal(SIGINT, sig_handler);
    signal(SIGQUIT, sig_handler);

    //Init semaphore
    sem_init(&mutex_v, 0, 1);
    sem_init(&empty_v, 0, BUFFER_SIZE);
    sem_init(&full_v, 0, 0);
    sem_init(&mutex_nv, 0, 1);
    sem_init(&empty_nv, 0, BUFFER_SIZE);
    sem_init(&full_nv, 0, 0);

    pthread_t vegan_chef_id, nonVegan_chef_id;
    pthread_t vegan_customer_id, nonVegan_customer_id,hybrid_customer_id;

    int result;
    // thread 1:
    result = pthread_create(&vegan_chef_id, NULL, vegan_chef, NULL);
    if (result != 0)
    {
        printf("Error creating thread\n");
    }
    else
    {
        printf("-> Vegan chef thread starts with id: %ld\n", vegan_chef_id);
    }
    // thread 2:
    result = pthread_create(&nonVegan_chef_id, NULL, nonVegan_chef, NULL);
    if (result != 0)
    {
        printf("Error creating thread\n");
    }
    else
    {
        printf("-> Non Vegan chef thread starts with id: %ld\n", nonVegan_chef_id);
    }
    // thread 3:
    result = pthread_create(&vegan_customer_id, NULL, vegan_customer, NULL);
    if (result != 0)
    {
        printf("Error creating thread\n");
    }
    else
    {
        printf("-> Vegan customer thread starts with id: %ld\n", vegan_customer_id);
    }
    // thread 4:
    result = pthread_create(&nonVegan_customer_id, NULL, nonVegan_customer, NULL);
    if (result != 0)
    {
        printf("Error creating thread\n");
    }
    else
    {
        printf("-> Non Vegan customer thread starts with id: %ld\n", nonVegan_customer_id);
    }
    // thread 5:
    result = pthread_create(&hybrid_customer_id, NULL, hybrid_customer, NULL);
    if (result != 0)
    {
        printf("Error creating thread\n");
    }
    else
    {
        printf("-> Hybrid customer thread starts with id: %ld\n", hybrid_customer_id);
    }
    
    // main thread:
    int s_v, s_nv;
    while(run)
    {
        sem_wait(&mutex_v);
        sem_wait(&mutex_nv);
        
        s_v = 0;
        s_nv = 0;
        for(int i = 0; i < BUFFER_SIZE; i++) {
            if(vegan_tray[i] > 0) {
                s_v ++;
            }
            if(nonVegan_tray[i] > 0) {
                s_nv ++;
            }
        }
        printf("-> Items in Vegan tray: %d/%d, Non-Vegan tray: %d/%d\n", s_v, BUFFER_SIZE, s_nv, BUFFER_SIZE);
        
        sem_post(&mutex_v);
        sem_post(&mutex_nv);
        sleep(10);
    }

    pthread_join(vegan_chef_id, NULL);
    pthread_join(nonVegan_chef_id, NULL);
    pthread_join(vegan_customer_id, NULL);
    pthread_join(nonVegan_customer_id, NULL);
    pthread_join(hybrid_customer_id, NULL);

    free(vegan_tray);
    free(nonVegan_tray);

    printf("Program SUCCESS!\n");
    exit(0);
}

void* vegan_chef(void* arg)
{
    bool dish = false;
    while(run)
    {
        sem_wait(&empty_v);
        sem_wait(&mutex_v);
        
        if(vegan_tray[in_v] != 0) {
            printf("X Vegan chef: Handle error\n");
        }
        else {
            if(dish) {
                vegan_tray[in_v] = 1;
                printf("+ Portecelli creates vegan dish: Pistachio Pesto Pasta\n");
            }
            else {
                vegan_tray[in_v] = 2;
                printf("+ Portecelli creates vegan dish: Avocado Fruit Salad\n");
            }
            dish = !dish;
        }
        in_v = (in_v + 1) % BUFFER_SIZE;
        
        sem_post(&full_v);
        sem_post(&mutex_v);

        //Sleep between 1 and 5 seconds
        //srand(time(NULL));
        sleep(1 + rand() % 4);
    }
    pthread_exit(NULL);
}

void* nonVegan_chef(void* arg)
{
    bool dish = false;
    while(run)
    {
        sem_wait(&empty_nv);
        sem_wait(&mutex_nv);
        
        if(nonVegan_tray[in_nv] != 0) {
            printf("X Non-Vegan chef: Handle error\n");
        }
        else {
            if(dish) {
                nonVegan_tray[in_nv] = 1;
                printf("+ Donatello creates non-vegan dish: Fettuccine Chicken Alfredo\n");
            }
            else {
                nonVegan_tray[in_nv] = 2;
                printf("+ Donatello creates non-vegan dish: Garlic Sirloin Steak\n");
            }
            dish = !dish;
        }
        in_nv = (in_nv + 1) % BUFFER_SIZE;
        
        sem_post(&full_nv);
        sem_post(&mutex_nv);

        //Sleep between 1 and 5 seconds
        //srand(time(NULL));
        sleep(1 + rand() % 4);
    }
    pthread_exit(NULL);
}

void* vegan_customer(void* arg)
{
    while(run)
    {
        sem_wait(&full_v);
        sem_wait(&mutex_v);
        
        if(vegan_tray[out_v] == 1) {
            printf("- Vegan customer gets dish: Pistachio Pesto Pasta\n");   
        }
        else if(vegan_tray[out_v] == 2) {
            printf("- Vegan customer gets dish: Avocado Fruit Salad\n");   
        }
        else {
            printf("X Vegan customer: Handle error\n");
        }
        vegan_tray[out_v] = 0;
        out_v = (out_v + 1) % BUFFER_SIZE;

        sem_post(&mutex_v);
        sem_post(&empty_v);

        //Sleep between 10 and 15 seconds
        //srand(time(NULL));
        sleep(10 + rand() % 5);
    }
    pthread_exit(NULL);
}

void* nonVegan_customer(void* arg)
{
    while(run)
    {
        sem_wait(&full_nv);
        sem_wait(&mutex_nv);
        
        if(nonVegan_tray[out_nv] == 1) {
            printf("- Non-Vegan customer gets dish: Fettuccine Chicken Alfredo\n");   
        }
        else if(nonVegan_tray[out_nv] == 2) {
            printf("- Non-Vegan customer gets dish: Garlic Sirloin Steak\n");   
        }
        else {
            printf("X Non-Vegan customer: Handle error\n");
        }
        nonVegan_tray[out_nv] = 0;
        out_nv = (out_nv + 1) % BUFFER_SIZE;

        sem_post(&mutex_nv);
        sem_post(&empty_nv);

        //Sleep between 10 and 15 seconds
        //srand(time(NULL));
        sleep(10 + rand() % 5);
    }
    pthread_exit(NULL);
}

void* hybrid_customer(void* arg)
{
    while(run)
    {
        sem_wait(&full_v);
        sem_wait(&mutex_v);
        sem_wait(&full_nv);
        sem_wait(&mutex_nv);
        
        printf("- Hybrid customer gets ");
        if(vegan_tray[out_v] == 1) {
            printf("vegan dish: Pistachio Pesto Pasta ");   
        }
        else if(vegan_tray[out_v] == 2) {
            printf("vegan dish: Avocado Fruit Salad ");   
        }
        else {
            printf("X Handle error X ");
        }

        if(nonVegan_tray[out_nv] == 1) {
            printf("and non-vegan dish: Fettuccine Chicken Alfredo\n");   
        }
        else if(nonVegan_tray[out_nv] == 2) {
            printf("and non-vegan dish: Garlic Sirloin Steak\n");   
        }
        else {
            printf("and X Handle error X\n");
        }

        vegan_tray[out_v] = 0;
        out_v = (out_v + 1) % BUFFER_SIZE;
        nonVegan_tray[out_nv] = 0;
        out_nv = (out_nv + 1) % BUFFER_SIZE;

        sem_post(&mutex_v);
        sem_post(&empty_v);
        sem_post(&mutex_nv);
        sem_post(&empty_nv);

        //Sleep between 10 and 15 seconds
        //srand(time(NULL));
        sleep(10 + rand() % 5);
    }
    pthread_exit(NULL);
}




