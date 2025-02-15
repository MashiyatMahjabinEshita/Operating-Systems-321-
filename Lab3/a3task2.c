#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>

struct msg {
    long int type;
    char txt[6];
};

void otp_generator(int msgid, int pid) {
    struct msg msg;
    if (msgrcv(msgid, &msg, sizeof(msg.txt), 1, 0) == -1) {
        perror("msgrcv");
        exit(1);
    }
    printf("OTP generator received workspace name from log in: %s\n", msg.txt);
    snprintf(msg.txt, sizeof(msg.txt), "%d", pid);
    msg.type = 2;
    if (msgsnd(msgid, &msg, sizeof(msg.txt), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }
    printf("OTP sent to log in from OTP generator: %s\n", msg.txt);
    msg.type = 3;
    if (msgsnd(msgid, &msg, sizeof(msg.txt), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }
    printf("OTP sent to mail from OTP generator: %s\n", msg.txt);
    wait(NULL);
    
    exit(0);
}

void mail_process(int msgid) {
    struct msg msg;
    if (msgrcv(msgid, &msg, sizeof(msg.txt), 3, 0) == -1) {
        perror("msgrcv");
        exit(1);
    }
    printf("Mail received OTP from OTP generator: %s\n", msg.txt);
    msg.type = 4;
    if (msgsnd(msgid, &msg, sizeof(msg.txt), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }
    printf("OTP sent to log in from mail: %s\n", msg.txt);
    
    exit(0);
}

int main() {
    key_t key = ftok("progfile", 65);
    int msgid = msgget(1000, 0666 | IPC_CREAT); 
    struct msg msg;
    pid_t pid;

    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }
    printf("Please enter the workspace name: ");
    char workspace[10];
    scanf("%s", workspace);

    if (strcmp(workspace, "cse321") != 0) {
        printf("Invalid workspace name\n");
        msgctl(msgid, IPC_RMID, NULL);
        exit(1);
    } else {
        strcpy(msg.txt, workspace);
        msg.type = 1;
        if (msgsnd(msgid, &msg, sizeof(msg.txt), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }
        printf("Workspace name sent to otp generator from log in: %s\n", msg.txt);
    }
    pid = fork();
    if (pid == 0) {
        pid_t child_pid = fork();
        if (child_pid == 0) {
            mail_process(msgid);
        } else if (child_pid > 0) {
            otp_generator(msgid, getpid());
        }
    } else if (pid > 0) {
        wait(NULL);
        if (msgrcv(msgid, &msg, sizeof(msg.txt), 2, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
        char otp_from_otp[6];
        strcpy(otp_from_otp, msg.txt);
        printf("Log in received OTP from OTP generator: %s\n", otp_from_otp);
        if (msgrcv(msgid, &msg, sizeof(msg.txt), 4, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
        char otp_from_mail[6];
        strcpy(otp_from_mail, msg.txt);
        printf("Log in received OTP from mail: %s\n", otp_from_mail);
        if (strcmp(otp_from_otp, otp_from_mail) == 0) { //comparing otps
            printf("OTP Verified\n");
        } else {
            printf("OTP Incorrect\n");
        }
        msgctl(msgid, IPC_RMID, NULL);
    } else {
        perror("fork");
        exit(1);
    }

    return 0;
}

