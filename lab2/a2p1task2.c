#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid, grandchild_pid;
    child_pid = fork();     // 1st child process

    if (child_pid < 0) {
        perror("Fork failed");
        return 1;
    } 
    else if (child_pid == 0) { //child process er inside
        grandchild_pid = fork();         // making grandchild process

        if (grandchild_pid < 0) {
            perror("Fork failed");
            return 1;
        }
        else if (grandchild_pid == 0) {
            printf("I am grandchild\n"); // insiding grandchild process
            return 0;  // grandchild ded
        }
        else {
            // Inside child process after creating grandchild
            wait(NULL);  // child e gelam after the grand child, Wait for granchild to ded
            printf("I am child\n");
            return 0;  // Cchild morlo
        }
    } 
    else {

        wait(NULL);  // parent er moddhe , child morar jonno daray ase
        printf("I am parent\n");
    }

    return 0;
}

