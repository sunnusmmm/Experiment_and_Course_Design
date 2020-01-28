#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun {
    int val;                  /* value for SETVAL */
    struct semid_ds *buf;     /* buffer for IPC_STAT, IPC_SET */
    unsigned short *array;    /* array for GETALL, SETALL */
    struct seminfo *__buf;    /* buffer for IPC_INFO */
};

int semid = 0;
int a = 0;

void P(int semid, int index)
{
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = -1;
    sem.sem_flg = 0;       //操作标记：0或IPC_NOWAIT等
    semop(semid, &sem, 1); //1:表示执行命令的个数
    return;
}

void V(int semid, int index)
{
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = 1;
    sem.sem_flg = 0;
    semop(semid, &sem, 1);
    return;
}

void *process1(void *args)
{
    for (int i = 0; i < 100; i++)
    {
        P(semid, 0);
        printf("i = %d\n",a);
        V(semid, 1);
    }
}

void *process2(void *args)
{
    for (int i = 1; i <= 100; i++)
    {
        P(semid, 1);
        a += i;
        V(semid, 0);
    }
}

int main()
{
    pthread_t sub1, sub2;
    //创建信号灯；
    semid = semget(IPC_PRIVATE, 2, IPC_CREAT | 0666);
    // 信号灯赋初值;
    union semun arg;
    arg.val = 0;
    semctl(semid, 0, SETVAL, arg);
    arg.val = 1;
    semctl(semid, 1, SETVAL, arg);
    // 创建两个线程subp1、subp2;
    pthread_create(&sub1, nullptr, process1, nullptr);
    pthread_create(&sub2, nullptr, process2, nullptr);
    // 等待两个线程运行结束；
    pthread_join(sub1, nullptr);
    pthread_join(sub2, nullptr);
    // 删除信号灯；
    semctl(semid, 0, IPC_RMID, 0);
}
