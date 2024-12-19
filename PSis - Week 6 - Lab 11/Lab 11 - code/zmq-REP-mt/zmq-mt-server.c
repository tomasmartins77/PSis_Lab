#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>

// void *context;
void *context;
int verify_prime(int value)
{

    int divisor = 2;
    if (value < 4)
    {
        return 1;
    }
    while (value % divisor != 0)
    {
        divisor++;
    }
    if (value == divisor)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void *thread_function(void *ptr)
{

    long int thread_number = (long int)ptr;

    void *responder = zmq_socket(context, ZMQ_REP);
    int rc = zmq_connect(responder, "inproc://back-end");
    assert(rc == 0);

    void *pusher = zmq_socket(context, ZMQ_PUSH);
    rc = zmq_connect(pusher, "inproc://xxxx");
    assert(rc == 0);

    int n;
    int result;
    printf("Thread ready\n");
    while (1)
    {
        zmq_recv(responder, &n, sizeof(n), 0);
        sleep(1);

        if (verify_prime(n))
        {
            result = 1;
            zmq_send(responder, &result, sizeof(result), 0);
            zmq_send(pusher, &n, sizeof(n), 0);
            printf("Thread %ld sent %d\n", thread_number, n);
        }
        else
        {
            result = 0;
            zmq_send(responder, &result, sizeof(result), 0);
        }
    }
    return 0;
}

void *thread_function_print_primes(void *arg)
{
    void *puller = zmq_socket(context, ZMQ_PULL);
    int rc = zmq_bind(puller, "inproc://xxxx");
    assert(rc == 0);
    printf("printer ready\n");
    int n;
    while (1)
    {
        zmq_recv(puller, &n, sizeof(n), 0);
        printf("Prime number: %d\n", n);
    }
}

int main(void)
{

    context = zmq_ctx_new();

    //  Socket facing clients
    void *frontend = zmq_socket(context, ZMQ_ROUTER);
    int rc = zmq_bind(frontend, "ipc:///tmp/fifo-pipe-front-end");
    assert(rc == 0);

    //  Socket facing services
    void *backend = zmq_socket(context, ZMQ_DEALER);
    rc = zmq_bind(backend, "inproc://back-end");
    assert(rc == 0);

    long int worker_nbr;
    for (worker_nbr = 0; worker_nbr < 2; worker_nbr++)
    {
        pthread_t worker;
        pthread_create(&worker, NULL, thread_function, (void *)worker_nbr);
    }

    pthread_t primes;
    pthread_create(&primes, NULL, thread_function_print_primes, NULL);

    //  Start the proxy
    zmq_proxy(frontend, backend, NULL);

    //  We never get here...
    return 0;
}