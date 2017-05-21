// 实现三个线程A B C，按照顺序循环输出 A B C

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int seq = 0;
pthread_mutex_t mutex;

void *thread1(void *arg)
{
    int i;

    for (i = 0; i < 10; ) {
        pthread_mutex_lock(&mutex);
        if (seq == 0) {
            printf("A\n");
            i++;
            seq = 1;
        }
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void *thread2(void *arg)
{
    int i;

    for (i = 0; i < 10; ) {
        pthread_mutex_lock(&mutex);
        if (seq == 1) {
            printf("B\n");
            i++;
            seq = 2;
        }
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void *thread3(void *arg)
{
    int i;

    for (i = 0; i < 10; ) {
        pthread_mutex_lock(&mutex);
        if (seq == 2) {
            printf("C\n");
            i++;
            seq = 0;
        }
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main()
{
    
    pthread_t tpid1;
    pthread_t tpid2;
    pthread_t tpid3;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&tpid1, NULL, thread1, NULL);
    pthread_create(&tpid2, NULL, thread2, NULL);
    pthread_create(&tpid3, NULL, thread3, NULL);

    sleep(10);
    
    return 0;
}
