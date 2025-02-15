#include <stdio.h>
#include <stdlib.h>

int tulona(const void *a, const void *b) {
    return (*(int*)b - *(int*)a); // large to small
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Put numbers in the terminal\n");
        return 1;
    }

    int n = argc - 1;
    int *arr = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i + 1]);
    }
    qsort(arr, n, sizeof(int), tulona);    //array sort kortesi large to small 
    printf("Sorted array in descending order: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    //now(arr);
    return 0;
}

