
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define FIFO_NAME "/tmp/my_fifo"

int main () {
    // create namedpipe
    mkfifo(FIFO_NAME, 0666);
    int fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }
    if (dup2(fd, STDIN_FILENO) == -1) {
        perror("dup2");
    }

    int var;
    do {
        if (scanf("%d", &var) == EOF) {
         exit(0);
        }
        printf("%d\n", var);
    }while(1);

    close(fd);
    return 0;
}