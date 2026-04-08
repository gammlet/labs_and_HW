#include <stdio.h>

int main() {

    int a[]={1};
    int *p = a;
    int r = (unsigned long)p ==(unsigned long) &p;
    printf("%d\n", r);
    return 0;
}