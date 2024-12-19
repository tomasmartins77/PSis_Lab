#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void *thread_function(void *arg)
{
    int n = 0;
    int time_r = *(int *)arg;
    free(arg);
    long int r = random() % 100;
    printf("Start Thread %lu\n", r);
    while (n < 10)
    {
        sleep(time_r);
        n++;
        printf("inside Thread %lu %d\n", r, n);
    }
    printf("End Thread %lu\n", r);
    return (void *)r;
}

int main()
{
    char line[100];
    int n_threads;
    printf("How many threads: ");
    fgets(line, 100, stdin);
    sscanf(line, "%d", &n_threads);
    pthread_t thread_id;
    pthread_t *threads = (pthread_t *)malloc(n_threads * sizeof(pthread_t));
    void *thread_result;
    int *time;
    int i = 0;
    while (i < n_threads)
    {
        time = (int *)malloc(sizeof(int));
        *time = random() % 5;
        pthread_create(&thread_id, NULL, thread_function, time);
        threads[i] = thread_id;
        i++;
    };
    for (i = 0; i < n_threads; i++)
    {
        pthread_join(threads[i], &thread_result);
        printf("Thread %ld finished\n", (long int)thread_result);
    }

    free(threads);
    exit(0);
}