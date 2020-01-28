#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include "lab3.h"

pid_t  pid1, pid2;

int main(){
    
    printf("主程序开始\n");
    int shmid = shmget(KEY1, 4096, IPC_CREAT | 0666); //共享内存
    int flag = shmget(KEY2, 2*sizeof(int), IPC_CREAT | 0666); //共享标志内存
    int semid = semget(KEY3, 2, IPC_CREAT | 0666);//信号灯

    union semun arg;
    arg.val = 0;
    semctl(semid, 0, SETVAL, arg);
    arg.val = QUANTITY;
    semctl(semid, 1, SETVAL, arg);

    pid1 = fork();
    if (pid1 == 0) {
        printf("调用./bin/read可执行程序\n");
        execv("./bin/read", NULL);	
	}else{
        pid2 = fork();
        if (pid2 == 0){
            printf("调用./bin/write可执行程序\n");
            execv("./bin/write", NULL);
	    }
    }

    int status;
    waitpid(pid1, &status, 0);
    waitpid(pid2, &status, 0);

    semctl(semid, 0, IPC_RMID, 0);//IPC_RMID删除
    semctl(semid, 1, IPC_RMID, 0);
    shmctl(shmid, IPC_RMID, 0);

    printf("程序结束!\n");
    return 0;
}