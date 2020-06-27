#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <sys/time.h>

int main(int argc, char const *argv[])
{

	long int callreturn;
    struct timeval start, end;
    // 计时开始
    gettimeofday(&start, NULL);

    printf("调用sys_mycopy\n");
    callreturn = syscall(334,"test.jpg" , "to.jpg");
    if (callreturn == -1)
        printf("文件打开失败，请使用dmesg查看具体信息！ \n");
    if (callreturn == -2)
        printf("文件写入失败，请使用dmesg查看具体信息！ \n");
    else
    {
        // 计时结束
        gettimeofday(&end, NULL);
        suseconds_t msec = end.tv_usec - start.tv_usec;
        time_t sec = end.tv_sec - start.tv_sec;
        printf("使用时间 : %lu.%6lus\n", sec, msec);
    }

    return 0;
}
