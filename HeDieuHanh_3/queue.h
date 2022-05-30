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
#include <string.h>

// student infomation:
struct student_info {
    int id;
    int eat_time;
    time_t arrival_time;
    int total_wating_time;
    int turnaround_time;
    student_info() {}
    student_info(int id, int eat_time, time_t arrival_time) {
        this->id  = id;
        this->eat_time = eat_time;
        this->arrival_time = arrival_time;
        this->total_wating_time = 0;
        this->turnaround_time = 0;
    }
};

// queue node
struct node
{
    struct student_info data;
    struct node *link;
};

struct node *front = NULL;
struct node *rear = NULL;
int queue_size = 0;

// insert elements in queue
void push(student_info info)
{
    struct node *temp = NULL;
    temp = (struct node*)malloc(sizeof(struct node));
    if(temp == NULL) {
        printf("Can not allocate memory !\n");
        return;
    }
    temp->data = info;
    temp->link = NULL;
    if(rear == NULL) {
        front = temp;
        rear = temp;
    }
    else {
        rear->link = temp;
        rear = temp;
    }
    queue_size ++;
}

// pop elements from queue
void pop()
{
    if (front != NULL)
    {   
        struct node *temp = front; 
        front = front->link;
        free(temp);
        if(front == NULL) {
            rear = NULL;
        }
        queue_size --;
    }    
}

// check if queue is empty or not
bool is_empty()
{
    return (front == NULL);
}
 
// returns first element of queue
student_info first_element()
{
    return front->data;        
}

//clear queue
void clear_queue() {
    while(!is_empty())
        pop();
}