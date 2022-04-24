#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define MaxThreads 1000//the number of maximum threads to work 
void *count3s_thread(void *id);
pthread_t tid[MaxThreads];

int t; /* number of threads */
int *array;
int length;
int count;

void count3s()
{
    int i;
    count = 0;
    /* Create t threads */
    for (i = 0; i < t; i++)
    {
        pthread_create(&tid[i], NULL, count3s_thread, (void *)i);
    }

    /*** wait for the threads to finish ***/
    for (i = 0; i < t; i++)
    {
        pthread_join(tid[i], NULL);
    }
}

void *count3s_thread(void *id)
{
    int i;
    /* Compute portion of the array that this thread should work on */
    int length_per_thread = length / t;
    int start = (intptr_t)id * length_per_thread;

    for (i = start; i < start + length_per_thread; i++)
    {
        if (array[i] == 3)
        {
            count += 1;
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int i;
    length = 1048576;
    t = 40;

    array = calloc(length, sizeof(int));

    srand(time(NULL));
    for (i = 0; i < length; i++)
    {
        array[i] = rand() % 10;
    }

    clock_t begin = clock();
    count3s();
    clock_t end = clock();
    double time_spent = ((double)(end - begin) / CLOCKS_PER_SEC) * 1000.0;
    printf("It took %fms\n", time_spent);

    printf("Parallel: The number of 3's is %d\n", count);

    count = 0;
    for (i = 0; i < length; i++)
        if (array[i] == 3)
            count++;
    printf("Serial: The number of 3's is %d\n", count);

    return 0;
}