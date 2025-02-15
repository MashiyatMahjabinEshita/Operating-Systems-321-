#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int tulona(const void *a, const void *b) {
    return (*(int*)b - *(int*)a); // large to small
}

void evenoddcheck(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 != 0) {
            printf("%d is Odd\n", arr[i]);
        } else {
            printf("%d is Even\n", arr[i]);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Put the numbers\n");
        return 1;
    }

    int n = argc - 1;
    int *arr = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("Fork failed");
        free(arr);
        return 1;
    }

    if (pid == 0) {
        qsort(arr, n, sizeof(int), tulona); //child p array sort kortese
        printf("Child Process: sort in descending order: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        exit(0); // child ded 
    } else {
        wait(NULL); //parent wait to child ded
        printf("Parent Process: checking odd or even status:\n"); //parent checking status
        evenoddcheck(arr, n);
    }

    //free(arr);
    return 0;
}

