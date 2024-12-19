#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

int *rand_num_array;

#define LIMIT 100000000

void *n_mult(void *arg)
{
    int n = *(int *)arg;
    long int c = 0;
    for (int i = 0; i < LIMIT; i++)
    {
        if (rand_num_array[i] % n == 0)
            c++;
    }
    return (void *)c;
}
int main()
{
    pthread_t thread_id;
    int n_threads = 5;
    pthread_t *threads_ids = (pthread_t *)malloc(n_threads * sizeof(pthread_t));
    int primes[] = {2, 3, 5, 7, 11};
    void *counter;
    rand_num_array = calloc(LIMIT, sizeof(int));

    for (int i = 0; i < LIMIT; i++)
    {
        rand_num_array[i] = random();
    }

    for (int i = 0; i < n_threads; i++)
    {
        pthread_create(&thread_id, NULL, n_mult, &primes[i]);
        threads_ids[i] = thread_id;
    }

    for (int i = 0; i < n_threads; i++)
    {
        pthread_join(threads_ids[i], &counter);
        printf("Number of multiples of %d: %ld\n", primes[i], (long int)counter);
    }
    exit(0);
}