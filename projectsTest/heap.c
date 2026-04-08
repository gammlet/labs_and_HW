#include <stdio.h>
#include <stdlib.h>


int* mkArray(int n) {
    int* arr = (int *)malloc(n * sizeof(int));
    return arr;
}
int main(void) {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int* myArray = mkArray(n);
    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &myArray[i]);
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", myArray[i]);
    }
    return 0;
}