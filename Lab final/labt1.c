//Task1 for binary num in nondecresing order
#include <stdio.h>
#include <string.h>

void sortBinaryString(char *str) { \\writing the func
    int count0 = 0, count1 = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '0') {
            count0++;
        } else if (str[i] == '1') {
            count1++;
        }
    }
    for (int i = 0; i < count0; i++) {
        str[i] = '0';
    }
    for (int i = count0; i < count0 + count1; i++) { 
        str[i] = '1';
    }
    str[count0 + count1] = '\0';
}

int main() {
    char binaryString[100];
    printf("Enter binary string: ");
    scanf("%s", binaryString);
    sortBinaryString(binaryString);
    printf("Sorted: %s\n", binaryString);
    return 0;
}
