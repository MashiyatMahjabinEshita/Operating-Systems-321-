#include <stdio.h>
#include <string.h>

int main() {
    char mail[50];  

    printf("Please give me the email: ");
    scanf("%s", mail);  // taking inputs

    char *domain = strchr(mail, '@');  // @ ache na nai

    if (domain != NULL) {
        if (strcmp(domain, "@sheba.xyz") == 0) {
            printf("Email address is okay\n");
        } else {
            printf("Email address is outdated\n");
        }
    } else {
        printf("Invalid email address\n");
    }

    return 0;
}

