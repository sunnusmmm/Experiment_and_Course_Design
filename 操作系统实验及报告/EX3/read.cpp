#include <fcntl.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "lab3.h"

int main() {

    int shmid = shmget(KEY1, 4096, IPC_CREAT | 0666);//获取该共享内存区的标识符、可通过不同的Size调整共享内存的大小，但是只能调小，不能调大
    int flag = shmget(KEY2, 2*sizeof(int), IPC_CREAT | 0666); //该共享标志内存的标识符
    int semid = semget(KEY3, 2, IPC_CREAT | 0666);

    char (*addr)[SIZE] = (char(*)[SIZE])shmat(shmid, NULL, 0);//获取进程虚拟地址，flag权限设置为0可读可写
    int *num = (int *)shmat(flag, NULL, 0);
    *num = -1;
    int fileread = open("/mnt/hgfs/ubuntn/Operate_System/EX3/Test/read.png", O_RDONLY);
    if (fileread == -1) {
        return -1;
    }
    int i = 0;
    while (1) {
        P(semid, 1);
        // printf("read->%d\n",i);
        int size = read(fileread, addr[i], SIZE);
        if(size < SIZE) {
            num[0] = i;
            num[1] = size;
        }
        V(semid, 0);
        i = (i + 1) % QUANTITY;//求模 循环
        if (size < SIZE) {
            break;
        }
    }
    close(fileread);
    if (shmdt(addr) == -1) {//进程结束，断开共享地址的连接 进程脱离共享内存区后，数据结构 shmid_ds 中的 shm_nattch 就会减 1 。但是共享段内存依然存在，只有 shm_attch 为 0 后，即没有任何进程再使用该共享内存区，共享内存区才在内核中被删除。一般来说，当一个进程终止时，它所附加的共享内存区都会自动脱离。
        exit(-1);
    }
    printf("read进程退出\n");
    return 0;
}