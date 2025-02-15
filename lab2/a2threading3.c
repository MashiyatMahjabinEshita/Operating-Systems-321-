#include <stdio.h>
#include <pthread.h>
#include <string.h>

#define NUM_THREADS 3

int sum_of_ascii_values(const char* name) { // ascii char er sum in str
    int sum = 0;
    for (int i = 0; name[i] != '\0'; i++) {
        sum += name[i]; 
    }
    return sum;
}

int results[NUM_THREADS]; // threads theke result store korar global array

void* calculate_ascii_sum(void* arg) { //given name er ascii calc
    const char* name = (const char*)arg;
    int result = sum_of_ascii_values(name);
    printf("Sum of ASCII values for '%s' is: %d\n", name, result);

    for (int i = 0; i < NUM_THREADS; i++) { //store the result in global array
        if (results[i] == 0) {  //faka jaiga of array khuji
            results[i] = result;
            break;
        }
    }

    return NULL;
}

void* compare_results(void* arg) { //thread to compare and print msg
    int a = results[0], b = results[1], c = results[2];
    
    if (a == b && b == c) {
        printf("Youreka\n");
    } else if (a == b || b == c || a == c) {
        printf("Miracle\n");
    } else {
        printf("Hasta la vista\n");
    }
    
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS + 1];  // 3 calc 1 comprae , array to keep them
    char names[NUM_THREADS][100];  //user er input rakhtesi

  
    for (int i = 0; i < NUM_THREADS; i++) { //user theke nicchi 3 ta
        printf("Enter name %d: ", i + 1);
        fgets(names[i], 100, stdin);
        names[i][strcspn(names[i], "\n")] = '\0';  //newline er char remove
    }

    for (int i = 0; i < NUM_THREADS; i++) { //thread create to cal the ascii sum
        pthread_create(&threads[i], NULL, calculate_ascii_sum, names[i]);
    }


    for (int i = 0; i < NUM_THREADS; i++) { //sum er mora wait
        pthread_join(threads[i], NULL);
    }


    pthread_create(&threads[NUM_THREADS], NULL, compare_results, NULL); //thread to compare 
    pthread_join(threads[NUM_THREADS], NULL); //compare ses na houa porjonto wait and end

    return 0;
}

