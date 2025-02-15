#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5
#define NUM_PRINTS 5


void* print_numbers(void* arg) { //taking 5 num
    int start_value = *((int*)arg);  // thread suru
    for (int i = 0; i < NUM_PRINTS; i++) {
        printf("Thread %d prints %d\n", start_value / NUM_PRINTS, start_value + i);  
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];  //thread id array kortesi
    int start_values[NUM_THREADS];   // sob thread er suru id rakhtesi array te

    for (int i = 0; i < NUM_THREADS; i++) {
        start_values[i] = i * NUM_PRINTS + 1;  // straings:  1, 6, 11, 16, 21
    }

    for (int i = 0; i < NUM_THREADS; i++) { //all 5 t create
        if (pthread_create(&threads[i], NULL, print_numbers, &start_values[i]) != 0) {
            perror("pthread_create failed");
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) { //thread morar wait
        pthread_join(threads[i], NULL);
    }

    return 0;
}

