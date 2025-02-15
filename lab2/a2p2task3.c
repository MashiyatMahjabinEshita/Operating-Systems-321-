#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(void) {
    int pipefds[2];
    if (pipe(pipefds) != 0) {
        printf("Pipe has error");
        return 1;
    }

    int total = 0;
    pid_t initial_p = getpid();

    write(pipefds[1], &total, sizeof(total));

    pid_t a, b, c;
    
    a = fork();
    if (a == 0) {
        pid_t current_p = getpid();
        printf("Parent: %d, Child: %d\n", getppid(), getpid());
        if (current_p % 2 != 0) {
            fork();
        }
    }

    b = fork();
    if (b == 0) {
        pid_t current_p = getpid();
        printf("Parent: %d, Child: %d\n", getppid(), getpid());
        if (current_p % 2 != 0) {
            fork();
        }
    }

    c = fork();
    if (c == 0) {
        pid_t current_p = getpid();
        printf("Parent: %d, Child: %d\n", getppid(), getpid());
        if (current_p % 2 != 0) {
            fork();
        }
    }

    pid_t current_p = getpid();
    if (current_p != initial_p) {
        read(pipefds[0], &total, sizeof(total));
        total++;
        write(pipefds[1], &total, sizeof(total));
        close(pipefds[1]);
        exit(0);
    }
    wait(NULL);
    wait(NULL);
    wait(NULL);

    if (getpid() == initial_p) {
        read(pipefds[0], &total, sizeof(total));
        printf("Total process number: %d\n", total + 1);
        close(pipefds[0]);
    }

    close(pipefds[1]);

    return 0;
}

