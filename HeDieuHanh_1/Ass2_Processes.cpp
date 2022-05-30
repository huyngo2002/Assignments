#include <stdlib.h> //standard stuff
#include <sys/mman.h> //mmap()
#include <stdio.h> //io stuff
#include <unistd.h> //sleep()
#include <semaphore.h> //semaphore()
#include <time.h> //time()
#include <signal.h> //signal()


#define BUFFER_SIZE 10

int *vegan_tray;
int *non_vegan_tray;

bool run = true;
void sig_handler(int signum)
{
    printf("Terminate program, stop running process - pid: %d\n", getpid());
    run = false;
}

int main()
{
    //Create shared memory
    vegan_tray = (int*)mmap(NULL, sizeof(int*)*BUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    non_vegan_tray = (int*)mmap(NULL, sizeof(int*)*BUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    //Create shared semaphores
    sem_t *mutex_v = (sem_t*)mmap(NULL, sizeof(sem_t*), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_t *full_v = (sem_t*)mmap(NULL, sizeof(sem_t*), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_t *empty_v = (sem_t*)mmap(NULL, sizeof(sem_t*), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_t *mutex_nv = (sem_t*)mmap(NULL, sizeof(sem_t*), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_t *full_nv = (sem_t*)mmap(NULL, sizeof(sem_t*), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_t *empty_nv = (sem_t*)mmap(NULL, sizeof(sem_t*), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    sem_init(mutex_v, 1, 1);
    sem_init(empty_v, 1, BUFFER_SIZE);
    sem_init(full_v, 1, 0);
    sem_init(mutex_nv, 1, 1);
    sem_init(empty_nv, 1, BUFFER_SIZE);
    sem_init(full_nv, 1, 0);

    //Create shared in/out pointers
    int* in_v = (int*)mmap(NULL, sizeof(int*), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    int* out_v = (int*)mmap(NULL, sizeof(int*), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    int* in_nv = (int*)mmap(NULL, sizeof(int*), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    int* out_nv = (int*)mmap(NULL, sizeof(int*), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    //In and out initially point to empty elements
    *in_v = 0;
    *out_v = 0;
    *in_nv = 0;
    *out_nv = 0;

    //Initialize buffer to be all 0's
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        vegan_tray[i] = 0;
        non_vegan_tray[i] = 0;
    }

    //Register handle signal
    signal(SIGINT, sig_handler);
    signal(SIGQUIT, sig_handler);

    //Forking
    pid_t vegan_chef;
    pid_t non_vegan_chef;
    pid_t vegan_customer;
    pid_t non_vegan_customer;
    pid_t hybrid_customer;

    //Child producer process
    if((vegan_chef = fork()) == 0)
    {
        bool dish = false;
        while(run)
        {
            sem_wait(empty_v);
            sem_wait(mutex_v);
           
            if(vegan_tray[*in_v] != 0) {
                printf("X Vegan chef: Handle error\n");
            }
            else {
                if(dish) {
                    vegan_tray[*in_v] = 1;
                    printf("+ Portecelli creates vegan dish: Pistachio Pesto Pasta\n");
                }
                else {
                    vegan_tray[*in_v] = 2;
                    printf("+ Portecelli creates vegan dish: Avocado Fruit Salad\n");
                }
                dish = !dish;
            }
            *in_v = (*in_v + 1) % BUFFER_SIZE;
           
            sem_post(full_v);
            sem_post(mutex_v);

            //Sleep between 1 and 5 seconds
            srand(time(NULL));
            sleep(1 + rand() % 4);
        }
        return 0;
    }
    printf("-> Vegan chef starts with pid: %d\n", vegan_chef);

    if((non_vegan_chef = fork()) == 0)
    {
        bool dish = false;
        while(run)
        {
            sem_wait(empty_nv);
            sem_wait(mutex_nv);
           
            if(non_vegan_tray[*in_nv] != 0) {
                printf("X Non-Vegan chef: Handle error\n");
            }
            else {
                if(dish) {
                    non_vegan_tray[*in_nv] = 1;
                    printf("+ Donatello creates non-vegan dish: Fettuccine Chicken Alfredo\n");
                }
                else {
                    non_vegan_tray[*in_nv] = 2;
                    printf("+ Donatello creates non-vegan dish: Garlic Sirloin Steak\n");
                }
                dish = !dish;
            }
            *in_nv = (*in_nv + 1) % BUFFER_SIZE;
           
            sem_post(full_nv);
            sem_post(mutex_nv);

            //Sleep between 1 and 5 seconds
            srand(time(NULL));
            sleep(1 + rand() % 4);
        }
        return 0;
    }
    printf("-> Non-Vegan chef starts with pid: %d\n", non_vegan_chef);

    //Child consumer process
    if((vegan_customer = fork()) == 0)
    {
        while(run)
        {
            sem_wait(full_v);
            sem_wait(mutex_v);
            
            if(vegan_tray[*out_v] == 1) {
                printf("- Vegan customer gets dish: Pistachio Pesto Pasta\n");   
            }
            else if(vegan_tray[*out_v] == 2) {
                printf("- Vegan customer gets dish: Avocado Fruit Salad\n");   
            }
            else {
                printf("X Vegan customer: Handle error\n");
            }
            vegan_tray[*out_v] = 0;
            *out_v = (*out_v + 1) % BUFFER_SIZE;

            sem_post(mutex_v);
            sem_post(empty_v);

            //Sleep between 10 and 15 seconds
            srand(time(NULL));
            sleep(10 + rand() % 5);
        }
        return 0;
    }
    printf("-> Vegan customer starts with pid: %d\n", vegan_customer);

    if((non_vegan_customer = fork()) == 0)
    {
        while(run)
        {
            sem_wait(full_nv);
            sem_wait(mutex_nv);
            
            if(non_vegan_tray[*out_nv] == 1) {
                printf("- Non-Vegan customer gets dish: Fettuccine Chicken Alfredo\n");   
            }
            else if(non_vegan_tray[*out_nv] == 2) {
                printf("- Non-Vegan customer gets dish: Garlic Sirloin Steak\n");   
            }
            else {
                printf("X Non-Vegan customer: Handle error\n");
            }
            non_vegan_tray[*out_nv] = 0;
            *out_nv = (*out_nv + 1) % BUFFER_SIZE;

            sem_post(mutex_nv);
            sem_post(empty_nv);

            //Sleep between 10 and 15 seconds
            srand(time(NULL));
            sleep(10 + rand() % 5);
        }
        return 0;
    }
    printf("-> Non-Vegan customer starts with pid: %d\n", non_vegan_customer);

    if((hybrid_customer = fork()) == 0)
    {
        while(run)
        {
            sem_wait(full_v);
            sem_wait(mutex_v);
            sem_wait(full_nv);
            sem_wait(mutex_nv);
            
            printf("- Hybrid customer gets ");
            if(vegan_tray[*out_v] == 1) {
                printf("vegan dish: Pistachio Pesto Pasta ");   
            }
            else if(vegan_tray[*out_v] == 2) {
                printf("vegan dish: Avocado Fruit Salad ");   
            }
            else {
                printf("X Handle error X ");
            }

            if(non_vegan_tray[*out_nv] == 1) {
                printf("and non-vegan dish: Fettuccine Chicken Alfredo\n");   
            }
            else if(non_vegan_tray[*out_nv] == 2) {
                printf("and non-vegan dish: Garlic Sirloin Steak\n");   
            }
            else {
                printf("and X Handle error X\n");
            }

            vegan_tray[*out_v] = 0;
            *out_v = (*out_v + 1) % BUFFER_SIZE;
            non_vegan_tray[*out_nv] = 0;
            *out_nv = (*out_nv + 1) % BUFFER_SIZE;

            sem_post(mutex_v);
            sem_post(empty_v);
            sem_post(mutex_nv);
            sem_post(empty_nv);

            //Sleep between 10 and 15 seconds
            srand(time(NULL));
            sleep(10 + rand() % 5);
        }
        return 0;
    }
    printf("-> Hybrid customer starts with pid: %d\n", hybrid_customer);

    //Parent
    int s_v, s_nv;
    while(run)
    {
        sem_wait(mutex_v);
        sem_wait(mutex_nv);
        
        s_v = 0;
        s_nv = 0;
        for(int i = 0; i < BUFFER_SIZE; i++) {
            if(vegan_tray[i] > 0) {
                s_v ++;
            }
            if(non_vegan_tray[i] > 0) {
                s_nv ++;
            }
        }
        printf("-> Items in Vegan tray: %d/%d, Non-Vegan tray: %d/%d\n", s_v, BUFFER_SIZE, s_nv, BUFFER_SIZE);
        
        sem_post(mutex_v);
        sem_post(mutex_nv);
        sleep(10);
    }
    munmap(vegan_tray, sizeof(int*) * BUFFER_SIZE);
    munmap(non_vegan_tray, sizeof(int*) * BUFFER_SIZE);
    munmap(mutex_v, sizeof(sem_t*));
    munmap(mutex_nv, sizeof(sem_t*));
    munmap(full_v, sizeof(sem_t*));
    munmap(full_nv, sizeof(sem_t*));
    munmap(empty_v, sizeof(sem_t*));
    munmap(empty_nv, sizeof(sem_t*));
    munmap(in_v, sizeof(int*));
    munmap(out_v, sizeof(int*));
    munmap(in_nv, sizeof(int*));
    munmap(out_nv, sizeof(int*));
    return 0;
}