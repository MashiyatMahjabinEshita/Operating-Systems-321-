#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char password[40];
    int lower = 0, upper = 0, digit = 0, special = 0; // Conter 

    printf("Please enter the password: ");
    scanf("%s", password);


    for (int i = 0; i < strlen(password); i++) {  //now iterating
        if (islower(password[i])) {
            lower++;
        } else if (isupper(password[i])) {
            upper++;
        } else if (isdigit(password[i])) {
            digit++;
        } else if (strchr("_$#@", password[i])) {
            special++;
        }
    }

   //jodi sob thik thake
    if (lower > 0 && upper > 0 && digit > 0 && special > 0) {
        printf("OK\n");
    } else {
        // Display missing components
        if (lower == 0) {
            printf("Lowercase missing\n");
        }
        if (upper == 0) {
            printf("Uppercase character missing\n");
        }
        if (digit == 0) {
            printf("Digit missing\n");
        }
        if (special == 0) {
            printf("Special character missing\n");
        }
    }

    return 0;
}

