#include <stdio.h>
#include <string.h>
#include <stdbool.h>
int main() {
    char str[200];  
    char *suru, *ses;  //suru sesh nisi

    printf("Please enter the string: ");
    scanf("%s", str); 

    suru = str;  //1st char indicate kortesi
    ses = str + strlen(str) - 1;  // last char indicate kortesi

    int palindrome = true;  //potaka nilam

    while (suru < ses) {
        if (*suru != *ses) { 
            palindrome = false;  //jodi na mele false 
            break;
        }
        suru++;  // suru agai
        ses--;    // ses pichai
    }

    if (palindrome) {
        printf("Palindrome\n");
    } else {
        printf("Not Palindrome\n");
    }

    return 0;
}

