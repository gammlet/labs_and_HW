#include <stdio.h>
#include <stdlib.h>

int main(void) {

    int* arr = malloc(3*sizeof(int));
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    for (int i = 0; i<=5; i++) {
        if (i>=3) {
            printf("Insufficient memory\n");
            return 0;
        }
        printf("%d\n", arr[i]);

    }
    free(arr);
    //int* p = arr+1;
    //printf("&p = %p\n", &p);
    //printf("*p = %d\n", *p);
    //printf("&arr = %p\n", arr);
    //printf("*arr = %d\n", *arr);
    //printf("&p = %d\n", &p);
    //printf("&arr = %d\n", &arr);

}
