asmlinkage long sys_hello_world(void);
asmlinkage long sys_mycopy(const char *target, const char *source);

asmlinkage long sys_hello_world(void)
{
	printk("mycall: hello world !\n");
	return 333;
}

asmlinkage long sys_mycopy(const char *target, const char *source)
{
    int from_fd, to_fd, bytes_read, bytes_write;
    char buffer[960]; //一次读写BUFF_SIZE个字节
    char *ptr;

	mm_segment_t fs;
	fs = get_fs();  //get access restriction value
	set_fs(KERNEL_DS);  //set kernel restriction value

    from_fd = sys_open(source, O_RDONLY, S_IRUSR);
    if (from_fd < 0)
    {
        printk("open %s error\n", source);
		set_fs(fs);   //recovery
        return -1;
    }

    // 目标路径和文件  没有则创建
    to_fd = sys_open(target, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR); //设置用户权限
    if (to_fd < 0)
    {
        printk("create %s error\n", target);
		set_fs(fs);   //recovery
        return -2;
    }

    while ((bytes_read = sys_read(from_fd, buffer, sizeof(buffer))))
    {
        /* 一个致命的错误发生了 */
        if (bytes_read < 0)
        {
            printk("read error!\n");
            break;
        }
        else if (bytes_read > 0)
        {
            ptr = buffer;
            while ((bytes_write = sys_write(to_fd, ptr, bytes_read)))
            {
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
            if (bytes_write < 0){
                printk("write error!\n");
                break;
            }
        }
    }
    sys_close(from_fd);
    sys_close(to_fd);
	set_fs(fs);   //recovery

    return 334;
}
