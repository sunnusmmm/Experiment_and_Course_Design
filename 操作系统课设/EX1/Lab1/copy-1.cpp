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
    char buffer[BUFFER_SIZE]; //һ�ζ�дBUFF_SIZE���ֽ�
    char *ptr;
    //�жϲ����Ƿ�����
    if (argc != 3)
    {
        printf("�����������ȷ��\n");
        printf("����������������ǰһ������ΪĿ���ļ�������һ������Ϊ�����Ƶ��ļ��� ��\n");
        return -1;
    }

    from_fd = open(argv[2], O_RDONLY);
    if (from_fd == -1)
    {
        printf("open %s error\n", argv[2]);
        return -1;
    }

    // Ŀ��·�����ļ�  û���򴴽�
    to_fd = open(argv[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR); //�����û�Ȩ��
    if (to_fd == -1)
    {
        printf("create %s error\n", argv[1]);
        return -1;
    }

    while ((bytes_read = read(from_fd, buffer, sizeof(buffer))))
    {
        /* һ�������Ĵ������� */
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
                // /* һ�������������� */
                // if ((bytes_write == -1) && (errno != EINTR)){
                //     printf("write stop error!");
                //     break;
                // }
                /* д�������ж����ֽ� */
                if (bytes_write == bytes_read)
                    break;
                /* ֻд��һ����,����д */
                else if (bytes_write > 0)
                {
                    ptr += bytes_write;
                    bytes_read -= bytes_write;
                }
            }
            /* д��ʱ�������������� */
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
