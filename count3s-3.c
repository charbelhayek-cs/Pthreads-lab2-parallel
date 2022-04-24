#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define MaxThreads 1000
void *count3s_thread(void *id);
pthread_t tid[MaxThreads];

int t;
int *array;
int length;
int count;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void count3s()
{
    int i;
    count = 0;
    for (i = 0; i < t; i++)
    {
        pthread_create(&tid[i], NULL, count3s_thread, (void *)i);
    }

    for (i = 0; i < t; i++)
    {
        pthread_join(tid[i], NULL);
    }
}

void *count3s_thread(void *id)
{
    int i;
    int length_per_thread = length / t;
    int start = (int)id * length_per_thread;

    for (i = start; i < start + length_per_thread; i++)
    {
        if (array[i] == 3)
        {
            pthread_mutex_lock(&m);
            count += 1;
            pthread_mutex_unlock(&m);
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    int i;
    length = 1048576;
    t = 48;

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