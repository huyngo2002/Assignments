#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <pthread.h>

#define SIZE 200000000
#define RANGEMAX 100000
int arr[SIZE];

int count = 0;
pthread_mutex_t mutex;

bool isComposite(int num)
{
	if (num < 4)
        return false;

	if (num%2 == 0 || num%3 == 0)
        return true;

	for (int i=5; i*i <= num; i = i+6)
		if (num%i == 0 || num%(i+2) == 0)
		    return true;

	return false;
}

void* checkingThread(void* arg)
{
    int thisCount = 0;
    if(arg != NULL) {
        int *cv = (int*)arg;
        for(int i = cv[0]; i < cv[1]; ++i){
            if(isComposite(arr[i]))
                thisCount ++;
        }
    }
    free(arg);
    pthread_mutex_lock(&mutex);
    count += thisCount;
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    time_t begin, end;
    begin = time(NULL);
    ////////////////////////////////////////////////////////////
    if(argc != 2 || argv[1][0] != '-') {
        printf("Invalid arguments!\n");
        return 0;
    }
    int threadNum = atoi(argv[1] + 1);
    if(threadNum < 1 || threadNum > 20) {
        printf("Invalid arguments!\n");
        return 0;
    }
    printf("Number of worker thread: %d\n\n", threadNum);
    // Generate random number
    printf("Generating %d number with ramdom interger in range(from %d to %d) ...\n\n", SIZE, 1, RANGEMAX);
    for(int i = 0; i < SIZE; ++i)
        arr[i] = 1 + rand()%RANGEMAX;

    pthread_t threadID[threadNum];
    int range = SIZE/threadNum;
    int d = SIZE % threadNum;
    int currInd = 0;
    int *arg;
    printf("Checking composite number ...\n\n");
    for(int num = 0; num < threadNum; ++num) {
        arg = NULL;
        arg = (int*)malloc(2 * sizeof(int));
        if(arg == NULL){
            printf("Cannot allocate memory!\n");
            return 0;
        }
        arg[0] = currInd;
        if(d == 0){
            currInd += range;
        }
        else{
            currInd += (range + 1);
            d--;
        }
        arg[1] = currInd;
        if(pthread_create(&threadID[num], NULL, checkingThread, arg) != 0) {
            printf("Error creating thread!\n");
            return 0;
        }
    }
    for(int num = 0; num < threadNum; ++num){
        pthread_join(threadID[num], NULL);
    }

    float per = (float)count / SIZE * 100;
    ////////////////////////////////////////////////////////////
    end = time(NULL);
    printf("Total number of composite numbers: %d\n", count);
    printf("Percent of composite numbers: %.2f%%\n\n", per);
    printf("Running time is %ld seconds\n", (end - begin));

    return 0;
}