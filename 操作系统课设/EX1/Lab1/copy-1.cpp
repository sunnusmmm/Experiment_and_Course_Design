#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h> 
#include <string.h> 

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    int from_fd, to_fd, bytes_read, bytes_write;
    char buffer[BUFFER_SIZE]; //一次读写BUFF_SIZE个字节
    char *ptr;
    //判断参数是否完整
    if (argc != 3)
    {
        printf("输入参数不正确！\n");
        printf("请输入两个参数，前一个参数为目标文件名，后一个参数为被复制的文件名 ！\n");
        return -1;
    }

    from_fd = open(argv[2], O_RDONLY);
    if (from_fd == -1)
    {
        printf("open %s error\n", argv[2]);
        return -1;
    }

    // 目标路径和文件  没有则创建
    to_fd = open(argv[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR); //设置用户权限
    if (to_fd == -1)
    {
        printf("create %s error\n", argv[1]);
        return -1;
    }

    while ((bytes_read = read(from_fd, buffer, sizeof(buffer))))
    {
        /* 一个致命的错误发生了 */
        if (bytes_read == -1)
        {
            printf("read error!\n");
            break;
        }
        else if (bytes_read > 0)
        {
            ptr = buffer;
            while ((bytes_write = write(to_fd, ptr, bytes_read)))
            {
                // /* 一个致命错误发生了 */
                // if ((bytes_write == -1) && (errno != EINTR)){
                //     printf("write stop error!");
                //     break;
                // }
                /* 写完了所有读的字节 */
                if (bytes_write == bytes_read)
                    break;
                /* 只写了一部分,继续写 */
                else if (bytes_write > 0)
                {
                    ptr += bytes_write;
                    bytes_read -= bytes_write;
                }
            }
            /* 写的时候发生的致命错误 */
            if (bytes_write == -1){
                printf("write error!\n");
                break;
            }
        }
    }
    close(from_fd);
    close(to_fd);
    return (1);
}
