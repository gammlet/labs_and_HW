#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n = 5;
    for (int i = 1; i <= n; i++) {
        printf("rand:%d\n", rand()%6);
    }
    return 0;
}