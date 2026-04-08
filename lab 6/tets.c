#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    char word[]= "hello\n";
    char buffer[100];

    // create pipe
    int pd[2];
    pipe(pd);
    //

    pid_t pid;
    pid = fork();
    if (pid <0) {
        perror("error");
    } else if (pid == 0) {
        close(pd[0]);
        write(pd[1], word, sizeof(word));
        close(pd[1]);
    }else {
        close(pd[1]);
        read(pd[0], buffer, sizeof(buffer));
        printf("%s", buffer);

        wait(NULL);
        printf("I am the parent\n");
    }
    return 0;
}