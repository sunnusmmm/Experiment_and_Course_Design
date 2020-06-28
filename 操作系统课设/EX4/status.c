#include "status.h"

void hello(GtkWidget *widget, gpointer *data)
{
	GtkWidget *dialog;
    dialog = gtk_message_dialog_new(NULL,
                GTK_DIALOG_DESTROY_WITH_PARENT,
                GTK_MESSAGE_INFO,
                GTK_BUTTONS_OK,
                "\n确定要关闭计算机吗？\n");
    gtk_window_set_title(GTK_WINDOW(dialog), "Information");
    int k = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    if(k == -5)
		system("shutdown -P now");
}

void ShowStatus(GtkWidget *vbox)
{
    GtkWidget *label;
	GtkWidget *button;
	
	button = gtk_button_new_with_label("Shutdown");
	g_signal_connect(GTK_OBJECT(button), "clicked",
        GTK_SIGNAL_FUNC(hello), "button message");

    label = gtk_label_new("状态栏");
	//放置在vbox的下方
    gtk_box_pack_end(GTK_BOX(vbox), label, FALSE, TRUE, 1);
	gtk_box_pack_end(GTK_BOX(vbox), button, FALSE, TRUE, 1);
    //循环调用函数
    g_timeout_add(1000, GetTime, (gpointer)label);
}

// 定时器回调
gint GetTime(gpointer label)
{   
//当前时间
    time_t t;
	struct tm * lt;
    char string[150], curtime[25], starttime[25];
    time(&t); //获得系统时间
	lt = localtime (&t);//转为时间结构。
    sprintf (curtime, "%d/%d/%d %d:%d:%d",lt->tm_year+1900, lt->tm_mon, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);//输出结果
//运行时间
    long int num;
	int fd;
    char buf[30];
    if ((fd = open("/proc/uptime", O_RDONLY)) == -1)
    {
        perror("fail to uptime");
        return 0;
    }
    read(fd, buf, sizeof(buf));
    close(fd);
    sscanf(buf, "%ld",(long int*) &num);
    int hours = num / 3600;
    int mins = num % 3600 / 60;
    int sec = num % 60;
//开始时间=当前时间-运行时间
	t = t -  num;
	lt = localtime (&t);//转为时间结构。
    sprintf (starttime, "%d/%d/%d %d:%d:%d",lt->tm_year+1900, lt->tm_mon, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);//输出结果
	
//输出状态栏所有信息
    sprintf(string, "当前时间为:%s\t启动时间:%s\t运行时间:%dh %dm %ds\tCPU利用率:%.2f %%\t内存使用:%.2fG / %.2fG",
            curtime, starttime, hours, mins, sec,stat_info.cpu_ratio, (memo_info.MemTotal - memo_info.MemFree) / 1024.0 /1024.0 ,
         memo_info.MemTotal / 1024.0 /1024.0);
    gtk_label_set_text(label, string);

    return TRUE;
}
