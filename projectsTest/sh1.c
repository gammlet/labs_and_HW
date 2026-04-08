
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define FIFO_NAME "/tmp/my_fifo"

int main (int argc, char *argv[]) {

   // create namedpipe
    mkfifo(FIFO_NAME, 0666);
    int fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) {
        perror("open"                                                                                                                                 );
        return 1;
    }
    if (dup2(fd, STDOUT_FILENO)<0) {
        perror("dup2");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if ((atoi(argv[i]))%2 == 0) {
            printf("%d\n", atoi(argv[i]));
        }

    }
    close(fd);
    return 0;
}