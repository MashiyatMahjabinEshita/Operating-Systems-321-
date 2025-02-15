#include <stdio.h>

int main() {
    int var1, var2;

   
    printf("Please enter number1: ");
    scanf("%d", &var1);
    printf("Please enter number2: ");
    scanf("%d", &var2);
    
//Checking my conditions for comparing here :)

    if (var1 > var2) {
    
        printf("After Subtracting: %d\n", var1-var2); //1 big then sub
    } else if (var1 < var2) {
    
        printf("After adding: %d\n", var1+ var2);//1 small then add
        
    } else {

        printf("After multiplicating: %d\n", var1*var2); //equal gun
    }

    return 0;
}

