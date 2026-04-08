
#include <stdio.h>

int main() {
    int p = 1;
    int* pp = &p;

    printf("&pp = %d\n", *pp);
    return 0;
}