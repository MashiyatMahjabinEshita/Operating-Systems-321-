#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <fcntl.h>

struct share {
    char sel[100];
    int balance;
};

void process(int shmid, int fd[2]) {
    struct share *child_s_m = (struct share *)shmat(shmid, NULL, 0); //attaching shared money
    if (child_s_m == (void *)-1) {
        perror("shmat");
        exit(1);
    }

    char selecting_user[100];
    strcpy(selecting_user, (*child_s_m).sel);
    if (strcmp(selecting_user, "a") == 0) {
        printf("Enter amount to be added: ");
        int amount;
        scanf("%d", &amount);
        if (amount > 0) {
            (*child_s_m).balance += amount; 
            printf("Balance added successfully\n");
            printf("Updated balance after addition: %d\n", (*child_s_m).balance);
        } else {
            printf("Adding failed, Invalid amount\n");
        }
    } else if (strcmp(selecting_user, "w") == 0) {
        // Withdraw Money
        printf("Enter amount to be withdrawn: ");
        int amount;
        scanf("%d", &amount);
        if (amount > 0 && amount <= (*child_s_m).balance) { 
            (*child_s_m).balance -= amount;  
            printf("Balance withdrawn successfully\n");
            printf("Updated balance after withdrawal: %d\n", (*child_s_m).balance);
        } else {
            printf("Withdrawal failed, Invalid amount\n");
        }
    } else if (strcmp(selecting_user, "c") == 0) {
        printf("Your current balance is: %d\n", (*child_s_m).balance);  
    } else {
        printf("Invalid selection\n");
    }

    char msg[] = "Thank you for using\n"; // pipe e likhtesi
    write(fd[1], msg, strlen(msg));
    shmdt(child_s_m); //removing shared memory
    close(fd[1]);

    exit(0);
}

int main(void) {
    int shmid = shmget(IPC_PRIVATE, sizeof(struct share), IPC_CREAT | 0666);//shared memory banai
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    struct share *child_s_m = (struct share *)shmat(shmid, NULL, 0); //attaching share memory
    if (child_s_m == (void *)-1) {
        perror("shmat");
        exit(1);
    }

    (*child_s_m).balance = 1000; //share mem initialize
    int fd[2];  //pipe banai 
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    printf("Provide Your Input From Given Options:\n1. Type a to Add Money\n2. Type w to Withdraw Money\n3. Type c to Check Balance\n");
    scanf("%s", (*child_s_m).sel);
    printf("Your selection: %s\n", (*child_s_m).sel);

    pid_t pid = fork();
    if (pid == 0) { 
        close(fd[0]); // Closing read end of pipe in child process
        process(shmid, fd);
    } else if (pid > 0) {  
        close(fd[1]); //pipe er sesh
        wait(NULL); 
        char buffer[100];
        read(fd[0], buffer, sizeof(buffer));
        printf("%s", buffer);
        shmdt(child_s_m); //remove shared  memory
        shmctl(shmid, IPC_RMID, NULL); 
        close(fd[0]);
    } else {
        perror("fork");
        exit(1);
    }

    return 0;
}

