#include <stdio.h>
#include <stdlib.h>

void print_elements(char **elems, int count) {
    for (int i = 0; i < count; i++) {
        printf("%s\n", elems[i]);
    }
}
int count_odd_digits(const char *str) {
    int count = 0;
    while (*str) {
        if (isdigit(*str)) {
            int digit = *str;
            if (digit % 2 != 0)
                count++;
        }
        str++;
    }
    return count;
}

int compare( *a, *b) {
    const char *str1 = *a;
    const char *str2 = *b;

    int count1 = count_odd_digits(str1);
    int count2 = count_odd_digits(str2);

    return count1 - count2;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        perror("Usage : ./place <strings>");
        exit(1);
    }
    qsort(argv, argc - 1, sizeof(char *), compare);
    print_elements(&argv[1], argc - 1);

    return 0;
}
