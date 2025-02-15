#include <stdio.h>


int perfect(int num) { 
    int sum = 0;


    for (int i = 1; i <= num / 2; i++) {  //num bad diye perfect or not
        if (num % i == 0) {  // i is a divisor of num
            sum += i;
        }
    }

    return sum == num; //sum num e perfect
}

int main() {
    int suru, sesh;

    // Input the range
    printf("Enter the starting range: "); 
    scanf("%d", &suru);
    printf("Enter the ending range: ");
    scanf("%d", &sesh);

    // Print the range and the perfect numbers
    //printf("Perfect numbers between %d and %d are:\n", suru, sesh);
    printf("%d , %d \n", suru, sesh);


    // Loop through the range and print perfect numbers
    for (int i = suru; i <= sesh; i++) {
        if (perfect(i)) {
            printf("%d\n", i);
        }
    }

    return 0;
}

