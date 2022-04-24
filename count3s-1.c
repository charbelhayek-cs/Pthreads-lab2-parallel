#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *array; 
int length;

int main()
{
    length = 10000000;// example length
    int c = 0; // counting
    array = calloc(length, sizeof(int));
    srand(time(NULL));
    clock_t begin = clock();// begin the clock to check the time that it took to complete the process
    for (int i = 0; i < length; i++)
    {
        array[i] = rand() % 10;
        if (array[i] == 3)
        {
            count++;
        }
    }
    clock_t end = clock();// time where it ended
    double time_spent = ((double)(end - begin) / CLOCKS_PER_SEC) * 1000.0;
    printf("There are %d 3s\nIt took %fms", count, time_spent);
    return 0;
}