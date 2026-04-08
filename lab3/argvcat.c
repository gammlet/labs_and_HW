#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* print out an error message and exit */
void my_error(char *s)
{
    perror(s);
    exit(1);
}

/* Concatnate two strings.
 * Dynamically allocate space for the result.
 * Return the address of the result.
 */
char *my_strcat(char *s1, char *s2)
{
    char* arr;
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int total_len = len1 + len2 + 1; // +1 for null
    // TODO
    arr = (char*) malloc(total_len);  //just total len without sizeof(chart) because we are allocating for char not int
    if(arr == NULL){
        my_error("malloc failed");
    }

    arr[0] = '\0'; // initialize the first character to null to make it an empty string

    strcat(arr, s1);
    strcat(arr, s2);

    return arr;
}

int main(int argc, char *argv[])
{
    char    *s;
    char* old;

    s = my_strcat("", argv[0]);

    for (int i = 1; i < argc; i ++) {
        old = s;
        s = my_strcat(s, argv[i]);
        free(old);
    }

    printf("%s\n", s);
    free(s);
    return 0;
}
