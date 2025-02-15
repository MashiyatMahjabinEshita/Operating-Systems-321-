#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  // mutex for sync

void* thread_function(void* arg) { // for simulate thread execution
    int thread_id = *((int*)arg); // thread id passed as argument

    pthread_mutex_lock(&mutex); 

    printf("thread-%d running\n", thread_id);

    sleep(1); // simulate by the thread sleep 1 sec

    printf("thread-%d closed\n", thread_id);

    pthread_mutex_unlock(&mutex); // mutex unlock to run the next p

    return NULL;
}

int main() {
    pthread_t threads[5];
    int thread_ids[5];

    for (int i = 0; i < 5; i++) {  //5 ta thread banai
        thread_ids[i] = i + 1;  // id dei 1 to 5
        if (pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]) != 0) {
            perror("pthread_create failed");
            return 1;
        }
    }

    for (int i = 0; i < 5; i++) {  
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex); 

    return 0;
}

