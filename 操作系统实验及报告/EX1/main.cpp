#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<signal.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int piped[2];
static int pid1, pid2;
#define SIZE 1024

void handlerMain(int sig_no);
void handler1(int sig_no);
void handler2(int sig_no);

int main(int argc, char *argv[]) {
    signal(SIGINT, handlerMain);

    pipe(piped);

    int num = 10;
    pid1 = fork();
    if (pid1 == 0) {
        signal(SIGINT, SIG_IGN);
        signal(SIGUSR1, handler1);

        char buffer[SIZE];
        unsigned counterSend = 1;
        while(1) {
            num += 10;
            printf("×Ó£º%d", num);
            sprintf(buffer, "I send you %u times", counterSend);
            write(piped[1], buffer, sizeof(buffer));
            counterSend++;
            sleep(1);
        }
    }

    pid2 = fork();
    if (pid2 == 0) {
        signal(SIGINT, SIG_IGN);
        signal(SIGUSR2, handler2);

        char buffer[SIZE];
        ssize_t size;
        while (1) {
            memset(buffer, 0, SIZE);
            size = read(piped[0], buffer, SIZE);
            buffer[size] = 0;
            printf("%s\n", buffer);
        }
    }
    num += 20;
    printf("¸¸£º%d", num);
    // close(piped[0]);
    // close(piped[1]);

    int status;
    waitpid(pid1, &status, 0);
    waitpid(pid2, &status, 0);

    close(piped[0]);
    close(piped[1]);

    printf("\nParent Process is Killed!\n");
    return 0;
}

void handlerMain(int sig_no) {
    kill(pid1, SIGUSR1);
    kill(pid2, SIGUSR2);
}

void handler1(int sig_no) {
    close(piped[0]);
    close(piped[1]);
    printf("\nProcess 1 is Killed by Parent!\n");
    exit(0);
}

void handler2(int sig_no) {
    close(piped[0]);
    close(piped[1]);
    printf("\nProcess 2 is Killed by Parent!\n");
    exit(0);
}