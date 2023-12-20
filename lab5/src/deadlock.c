#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void *thread_func_1(void *arg) {
    pthread_mutex_lock(&mutex1);
    printf("thread 1 mutex1 is locked\n");

    sleep(2);
    for(int i = 0; i< 1000000;i++){}

    // Here is deadlock
    pthread_mutex_lock(&mutex2);
    printf("thread 1 mutex2 is locked\n");


    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);

    pthread_exit(NULL);
}

void *thread_func_2(void *arg) {
    pthread_mutex_lock(&mutex2);
    printf("thread 2 mutex2 is locked\n");

    sleep(2);

    // Here is deadlock
    pthread_mutex_lock(&mutex1);
    printf("thread 2 mutex1 is locked\n");


    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);

    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, thread_func_1, NULL);
    pthread_create(&thread2, NULL, thread_func_2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}