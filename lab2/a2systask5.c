#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    printf("Parent process ID: %d\n", getpid()); // Parent pID
    pid_t pid_c = fork();     //creating the child p; child = pid_c

    if (pid_c == -1) {
        perror("Failed to fork child process");     // fork hocche na
        return 1;
    }

    if (pid_c == 0) {
        printf("Child process ID: %d\n", getpid()); //child block
        for (int i = 0; i < 3; i++) { //3 ta gran child banaisi
            pid_t pid_gc = fork(); //grandchild =pid_gc
  
            if (pid_gc == -1) {   // fork hocche na
                perror("Failed to fork grandchild process");
                return 1;
            }

            if (pid_gc == 0) {
                printf("Grandchild process ID: %d\n", getpid()); //block
                return 0;
            }
        }
        
        return 0; //c more after gc
    }
    wait(NULL); //p wait to mora of c

    return 0;
}

