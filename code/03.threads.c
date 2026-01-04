#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *func_sum(void *);
int sum;
int main(int argc, char *argv[])
{
    pthread_t tid;
    int val[2];
    val[0] = atoi(argv[1]);
    val[1] = atoi(argv[2]);
    pthread_create(&tid, NULL, func_sum, val);
    pthread_join(tid, NULL);
    printf(" sum = %d\n", sum);
    return 0;
}
void *func_sum(void *arg)
{
    int *val = (int *)arg;
    sum = val[0] + val[1];
    pthread_exit(NULL);
}
