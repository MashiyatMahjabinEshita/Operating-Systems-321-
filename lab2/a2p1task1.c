#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>    //kholar jonno 
#include <unistd.h>   //write and off 
#include <string.h>   

#define max_length 100  //str er length bole dilam

int main(int argc, char *argv[]) {
    int file_des; //file descriptor
    char input[max_length];
    if (argc != 2) {    // checking if the file name is here by user /cli arg
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    file_des = open(argv[1], O_CREAT | O_WRONLY | O_APPEND, 0644);     // file open kortesi, na thakle create
    if (file_des == -1) {
        perror("Getting Error while opening or creating file");
        exit(EXIT_FAILURE);
    }

    printf("File opened done!! Enter strings to write in file \n");
    printf("Type '-1' to stop.\n");
    
    while (1) {     // Loop to continuously accept user input and write to the file
        printf("Enter string: ");
        fgets(input, max_length, stdin);

        input[strcspn(input, "\n")] = '\0';       // newline char remove kortesi jeita chole jete pare sesh e str er 

        if (strcmp(input, "-1") == 0) {     // exit condition check kortesi
            break;
        }

        if (write(file_des, input, strlen(input)) == -1) {       // string likhtesi file e
            perror("Error writing to the file");
            close(file_des);
            exit(EXIT_FAILURE);
        }

        if (write(file_des, "\n", 1) == -1) {      // newline char likbho after each str to look good
            perror("Error writing newline to the file");
            close(file_des);
            exit(EXIT_FAILURE);
        }
    }
    close(file_des);

    printf("Have written data to the file successfully\n");
    return 0;
}

