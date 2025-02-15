#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t a, b, c;
    int process_count = 1;  //parent diye suru
    
    
    a = fork();
    if (a == 0) {
        
        process_count++; //1st child process e 
        if (getpid() % 2 != 0) {  //pid check
            fork();  // another child
            process_count++;  
        }
    } else {
        process_count++;
        
        // Second fork (b)
        b = fork();
        if (b == 0) {
            // 2nd child process e 
            process_count++;
            if (getpid() % 2 != 0) {  // pid is odd
                fork();  // another child
                process_count++;  
            }
        } else {
            process_count++;
            
            c = fork();     // third fork (c)
            if (c == 0) {
                //3rd child process e 
                process_count++;
                if (getpid() % 2 != 0) {  // pID is odd
                    fork();  // Create another child
                    process_count++; 
                }
            }
        }
    }

    while (wait(NULL) > 0); //sob child terminate 

    if (a > 0 && b > 0 && c > 0) {
        printf("Total processes created (considering parent): %d\n", process_count);
    }

    return 0;
}

