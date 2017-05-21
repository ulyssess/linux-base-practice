#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

pthread_mutex_t mutex;

void * thread1(void *arg)
{
    printf("thread 1 try lock\n");
    pthread_mutex_lock(&mutex);
    printf("thread 1 locked\n");
    printf("thread 1, wait 10s\n");
    sleep(10);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void * thread2(void *arg)
{
    printf("thread 2 try lock\n");
    pthread_mutex_lock(&mutex);
    printf("thread 2 locked\n");
    printf("thread 2\n");
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void * thread3(void *arg)
{
    int ret;

    printf("thread 3 try lock\n");
    ret = pthread_mutex_trylock(&mutex);
    if (ret != 0) {
        //man里面说的设置errno是有问题的，errno没设置，倒是在返回值里面设置了.....
        printf("ret = %d errno = %d , %s\n", ret, errno, strerror(errno));
        if (ret == EBUSY) {
            printf("Mutex is already locked.\n");
            return NULL;
        } else if (ret == EINVAL) {
            printf("The value specified by mutex is invalid.\n");
        } else {
            printf("try lock error\n");
        }
    }

    printf("thread 3 locked\n");
    printf("thread 3\n");
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main()
{
    printf("Test thread mutex\n");

    pthread_t tpid1;
    pthread_t tpid2;
    pthread_t tpid3;

    if (pthread_mutex_init(&mutex, NULL) != 0) {
        fprintf(stderr, "mutex init error: %s\n", strerror(errno));
    }

    pthread_create(&tpid1, NULL, thread1, NULL);
    pthread_create(&tpid2, NULL, thread2, NULL);
    pthread_create(&tpid3, NULL, thread3, NULL);

    sleep(50);

    return 0;
}
