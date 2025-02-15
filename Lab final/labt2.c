#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int isPerfect(int num) {
    int sum = 1;
    for (int i = 2; i <= num / 2; i++) {
        if (num % i == 0) {
            sum += i;
        }
    }
    return sum == num;
}

int main() {
    int numbers[5];
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork Failed");
        return 1;
    } else if (pid > 0) {
        // Parent process
        FILE *fptr = fopen("24241331_Task2.txt", "w");
        if (fptr == NULL) {
            fprintf(stderr, "Error opening file");
            return 1;
        }

        printf("Enter 5 integer numbers:\n");
        for (int i = 0; i < 5; i++) {
            scanf("%d", &numbers[i]);
        }

        for (int i = 0; i < 5; i++) {
            if (isPerfect(numbers[i])) {
                fprintf(fptr, "%d is a perfect number\n", numbers[i]);
            } else {
                fprintf(fptr, "%d is not a perfect number\n", numbers[i]);
            }
        }

        fclose(fptr);
        wait(NULL); 
    } else {
        // Child process
        wait(NULL); //ensuring the parent is ded first
        printf("End\n");
    }

    return 0;
}
