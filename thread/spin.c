// 实现三个线程A B C，按照顺序循环输出 A B C

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int seq = 0;
pthread_spinlock_t spin;

void *thread1(void *arg)
{
    int i;

    for (i = 0; i < 10; ) {
        pthread_spin_lock(&spin);
        if (seq == 0) {
            printf("A\n");
            i++;
            seq = 1;
        }
        pthread_spin_unlock(&spin);
    }

    return NULL;
}

void *thread2(void *arg)
{
    int i;

    for (i = 0; i < 10; ) {
        pthread_spin_lock(&spin);
        if (seq == 1) {
            printf("B\n");
            i++;
            seq = 2;
        }
        pthread_spin_unlock(&spin);
    }

    return NULL;
}

void *thread3(void *arg)
{
    int i;

    for (i = 0; i < 10; ) {
        pthread_spin_lock(&spin);
        if (seq == 2) {
            printf("C\n");
            i++;
            seq = 0;
        }
        pthread_spin_unlock(&spin);
    }

    return NULL;
}

int main()
{
    
    pthread_t tpid1;
    pthread_t tpid2;
    pthread_t tpid3;

    pthread_spin_init(&spin, PTHREAD_PROCESS_SHARED);

    pthread_create(&tpid1, NULL, thread1, NULL);
    pthread_create(&tpid2, NULL, thread2, NULL);
    pthread_create(&tpid3, NULL, thread3, NULL);

    pthread_join(tpid1, NULL);
    pthread_join(tpid2, NULL);
    pthread_join(tpid3, NULL);
    
    return 0;
}
