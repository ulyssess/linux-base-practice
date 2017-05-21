// 实现三个线程A B C，按照顺序循环输出 A B C

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t sem1;
sem_t sem2;
sem_t sem3;


void *thread1(void *arg)
{
    int i;

    for (i = 0; i < 10; i++) {
        sem_wait(&sem1);
        printf("A\n");
        sem_post(&sem2);
    }

    return NULL;
}

void *thread2(void *arg)
{
    int i;

    for (i = 0; i < 10; i++) {
        sem_wait(&sem2);
        printf("B\n");
        sem_post(&sem3);
    }

    return NULL;
}

void *thread3(void *arg)
{
    int i;

    for (i = 0; i < 10; i++) {
        sem_wait(&sem3);
        printf("C\n");
        sem_post(&sem1);
    }

    return NULL;
}

int main()
{

    pthread_t tpid1;
    pthread_t tpid2;
    pthread_t tpid3;

    sem_init(&sem1, 0, 1);
    sem_init(&sem2, 0, 0);
    sem_init(&sem3, 0, 0);

    pthread_create(&tpid1, NULL, thread1, NULL);
    pthread_create(&tpid2, NULL, thread2, NULL);
    pthread_create(&tpid3, NULL, thread3, NULL);

    pthread_join(tpid1, NULL);
    pthread_join(tpid2, NULL);
    pthread_join(tpid3, NULL);
    
    return 0;
}
