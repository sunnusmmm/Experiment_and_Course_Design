#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>
#include "lab3.h"

int main() {

    int shmid = shmget(KEY1, 4096, IPC_CREAT | 0666);
    int flag = shmget(KEY2, 2*sizeof(int), IPC_CREAT | 0666); //共享标志内存
    int semid = semget(KEY3, 2, IPC_CREAT | 0666);

    char(*addr)[SIZE] = (char(*)[SIZE])shmat(shmid, NULL, 0);
    int *num = (int *)shmat(flag, NULL, 0);

    int filewrite = open("/mnt/hgfs/ubuntn/Operate_System/EX3/Test/write.png", O_WRONLY | O_CREAT | O_TRUNC);//写文件、该文件不存在则创建、该文件若存在则长度截为0
    int i = 0;
    int w = SIZE;
    while (1) {
        P(semid, 0);
        if(num[0] == i && num[0] != -1) w = num[1]; //最后一次需要写入的大小
        int size = write(filewrite, addr[i], w);
        V(semid, 1);
        if(num[0] == i && num[0] != -1) break;
        i = (i + 1) % QUANTITY;
    }
    close(filewrite);

    if (shmdt(addr) == -1) {//进程结束，断开共享地址的连接
        exit(-1);
    }

    printf("write进程退出\n");
    return 0;
}