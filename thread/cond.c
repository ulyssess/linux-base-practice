#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <pthread.h> 
  
int num = 0; 
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 

void* thread_func(void *arg)
{
    int i;
    int param = *(int *)arg;
    
    for(i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);
        
        while(param != num)
            pthread_cond_wait(&cond, &mutex);
        
        printf("%c\n", param + 'A');
        num = (num + 1) % 3;
        
        pthread_mutex_unlock(&mutex);
        pthread_cond_broadcast(&cond);
    }
    
    return NULL;
}

int main()
{
    int i;
    int order[3];
    pthread_t ptid[3];

    for(i = 0; i < 3; i++) {
        order[i] = i;
        pthread_create(&ptid[i], NULL, thread_func, (void *)&order[i]);
    }

    for(i = 0; i < 3; i++)
        pthread_join(ptid[i], NULL);    
}
