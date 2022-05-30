#include "queue.h"

#define PROCESS_NUM 4
#define MAX_LINE_LENGTH 100

bool run = true;
int counter = -1;
pthread_mutex_t mutex;

void* processingThread(void* arg)
{
    while(true) {
        pthread_mutex_lock(&mutex);
        if(!is_empty()) {
            // if has student in line, get first
            student_info s = first_element();
            pop();
            printf("Sit %d\n", s.id);
            pthread_mutex_unlock(&mutex);
            // get out time
            s.total_wating_time = (int)(time(NULL) - s.arrival_time);
            s.turnaround_time = s.total_wating_time + s.eat_time;
            // eating ...
            sleep(s.eat_time);
            // leaving
            printf("Leave %d Turnaround %d Wait %d\n", s.id, s.turnaround_time, s.total_wating_time);
        }
        else {
            pthread_mutex_unlock(&mutex);
            if(!run) {
                break;
            }
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    char *file_path;
    FILE *file = NULL;
    while(file == NULL) {
        printf("Input the input file path: ");
        scanf("%s", file_path);
        file = fopen(file_path, "r");
        if(file == NULL) {
            printf("Invalid input file path!\n\n");
        }
        else {
            printf("Valid file, starting ...\n\n");
        }
    }
    
    pthread_t threadID[PROCESS_NUM];
    for(int i = 0; i < PROCESS_NUM; ++i) {
        if(pthread_create(&threadID[i], NULL, processingThread, NULL) != 0) {
            printf("Error creating thread!\n");
        }
    }

    char line [MAX_LINE_LENGTH];
    char *token_ptr = NULL;
    char *saveptr = NULL;
    int v1, v2;
    while(fgets(line, MAX_LINE_LENGTH - 1, file) != NULL) {
        counter++;
        // ignore first line in fifo algorithm:
        if(counter == 0)
            continue;

        token_ptr = strtok_r(line, " =\r\n", &saveptr);
        if(token_ptr != NULL) {
            v1 = atoi(token_ptr);
        }
        token_ptr = strtok_r(NULL, " =\r\n", &saveptr);
        if(token_ptr != NULL) {
            v2 = atoi(token_ptr);
        }
        // wait student arrival
        sleep(v1);
        printf("Arrive %d\n", counter);
        // studen come, push into queue
        pthread_mutex_lock(&mutex);
        push(student_info(counter, v2, time(NULL)));
        //printf("Preempt %d\n", counter);
        pthread_mutex_unlock(&mutex);
    }

    run = false;
    for(int i = 0; i < PROCESS_NUM; ++i){
        pthread_join(threadID[i], NULL);
    }

    clear_queue();
    fclose(file);
    printf("PROGRAM SUCCESS!\n");
    return 0;
}