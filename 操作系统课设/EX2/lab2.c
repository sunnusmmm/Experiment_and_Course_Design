asmlinkage long sys_testcall(void) {
    printk("This is my call.\n");
    return 0;
}

asmlinkage long sys_mycall(const char *source, const char *target)
{
    int from_fd, to_fd, bytes_read, bytes_write;
    char buffer[1024];//缓冲区大小
    char *ptr;

	mm_segment_t old_fs;//保存环境
	old_fs = get_fs();
	set_fs(KERNEL_DS);//内核环境

    from_fd = sys_open(source, O_RDONLY, S_IRUSR);
    if (from_fd < 0)
    {
        printk("Open error\n");
        set_fs(old_fs);//恢复环境
        return -1;
    }


    to_fd = sys_open(target, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR); //设置用户权限
    if (to_fd < 0)
    {
        printk("Open/Create error\n");
        set_fs(old_fs);//恢复环境
        return -2;
    }

    //文件的正常拷贝
    while ((bytes_read = sys_read(from_fd, buffer, sizeof(buffer))))
    {
        /* 一个致命的错误发生了 */
        if (bytes_read < 0)
        {
            printk("Read error!\n");
            break;
        }
        else if (bytes_read > 0)
        {
            ptr = buffer;
            while ((bytes_write = sys_write(to_fd, ptr, bytes_read)))
            {
                /* 写的时候发生的致命错误 */
                if (bytes_write < 0){
                    printk("Write error!\n");
                    break;
                }
                else if (bytes_write == bytes_read)
                    break;
                /* 只写了一部分,继续写 */
                else if (bytes_write > 0)
                {
                    ptr += bytes_write;
                    bytes_read -= bytes_write;
                }
            }
            /* 写的时候发生的致命错误 */
            if (bytes_write < 0){
                printk("write error!\n");
                break;
            }
        }
    }
    sys_close(from_fd);
    sys_close(to_fd);
	set_fs(old_fs);//恢复环境

    return 0;
}
