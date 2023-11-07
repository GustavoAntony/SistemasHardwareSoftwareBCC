#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    pid_t filho;

    filho = fork();
    if (filho == 0) {
        printf("Meu pid: %d\n", getpid());
        while (1){
        }
        return 0;
    }
    int ws;
    // int x= wait(&ws);
    printf("%d\n",wait(&ws));

    printf("EXITED %d \n"
    "SIGNALED %d \n"
    "TERMSIG %d \n"
    "Error: %s \n",
    WIFEXITED(ws),
    WIFSIGNALED(ws),
    WTERMSIG(ws),
    strsignal(WTERMSIG(ws))
    );



    return 0;
}