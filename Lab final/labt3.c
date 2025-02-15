#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <pthrad.h>

int A[3] = {12, 15, 9};
pthread_mutex_t lock;

void* thread1_func(void* arg) {
    pthread_mutex_lock(&lock);
    A[0] = A[0] + 2;
    A[1] = A[1] - 3;
    A[2] = A[2] * 2;
    pthread_mutex_unlock(&lock);
    return NULL;
}

void* thread2_func(void* arg) {
    pthread_mutex_lock(&lock);
    A[0] = A[0] / 2;
    A[1] = A[1] + 2;
    A[2] = A[2] + 3;
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_mutex_init(&lock, NULL);

    pthread_create(&thread1, NULL, thread1_func, NULL);
    pthread_create(&thread2, NULL, thread2_func, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&lock);

    //printf(" %d\n", A[0]);
    return 0;
}
