#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Need numbers in the terminal\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        int num = atoi(argv[i]);
        if (num % 2 != 0) {
            printf("%d is Odd\n", num);
        } else {
            printf("%d is Even\n", num);
        }
    }
    return 0;
}

