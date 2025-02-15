#include <stdio.h>

struct item {
    int quantity;
    float price;
};

int main() {
    struct item paratha, vegetables, water;  // Corrected variable names and structure
    int num_of_people;
    float total_tk, ekar_taka;

    printf("Quantity Of Paratha: ");   //paratha
    scanf("%d", &paratha.quantity);
    printf("Unit Price Of Paratha: ");
    scanf("%f", &paratha.price);

    printf("Quantity Of Vegetables: ");//vegs
    scanf("%d", &vegetables.quantity);
    printf("Unit Price Of Vegetables: ");
    scanf("%f", &vegetables.price);

    printf("Quantity Of Mineral Water: "); //water
    scanf("%d", &water.quantity);
    printf("Unit Price Of Mineral Water: ");
    scanf("%f", &water.price);

    printf("Number of People: ");  //no. of people
    scanf("%d", &num_of_people);

    total_tk = (paratha.quantity * paratha.price) +  //total taka
               (vegetables.quantity * vegetables.price) +
               (water.quantity * water.price);

    ekar_taka = total_tk / num_of_people;      // Cekar taka
    printf("Individual people will pay: %.2f tk\n", ekar_taka);
 

    return 0;
}

