#include "cpu.h"

// 申明为全局变量
CPU_INFO cpu_info;
STAT_INFO stat_info;

// 刷新标签
GtkWidget *label_cpu_1;
GtkWidget *label_cpu_2;
GtkWidget *label_cpu_3;
GtkWidget *label_cpu_4;

void GetCPUInfo(void){
	int fd;
    char buf[3000];
    char *p = NULL;
	char *cpuInfo = cpu_info.model_name;
	if ((fd = open("/proc/cpuinfo", O_RDONLY)) == -1)
    {
        perror("fail to path");
        return;
    }
    read(fd, buf, sizeof(buf));
    close(fd);
	p = strstr(buf, "model name");
	for (; *p != ':'; p++);
	p += 2;
	while (*p != '\n')
    {
        *(cpuInfo++) = *(p++);
    }
	*cpuInfo = '\0';
	
	cpuInfo = cpu_info.cache_size;
	p = strstr(buf, "cache size");
	for (; *p != ':'; p++);
	p += 2;
	while (*p != '\n')
    {
        *(cpuInfo++) = *(p++);
    }
	*cpuInfo = '\0';
	
	cpuInfo = cpu_info.cpu_MHz;
	p = strstr(buf, "cpu MHz");
	for (; *p != ':'; p++);
	p += 2;
	while (*p != '\n')
    {
        *(cpuInfo++) = *(p++);
    }
	*cpuInfo = '\0';
	
	cpuInfo = cpu_info.cores;
	p = strstr(buf, "cpu cores");
	for (; *p != ':'; p++);
	p += 2;
	while (*p != '\n')
    {
        *(cpuInfo++) = *(p++);
    }
	*cpuInfo = '\0';
	
	cpuInfo = cpu_info.address_sizes;
	p = strstr(buf, "address sizes");
	for (; *p != ':'; p++);
	p += 2;
	while (*p != '\n')
    {
        *(cpuInfo++) = *(p++);
    }
	*cpuInfo = '\0';
	
	cpuInfo = cpu_info.clflush_size;
	p = strstr(buf, "clflush size");
	for (; *p != ':'; p++);
	p += 2;
	while (*p != '\n')
    {
        *(cpuInfo++) = *(p++);
    }
	*cpuInfo = '\0';
}


void GetStat(p_statinfo stat_info)
{
    int fd;
    char buf[51200];
    char *strs;
    char cp[128];
    size_t count;

    if ((fd = open("/proc/stat", O_RDONLY)) == -1)
    {
        perror("fail to stat");
        return;
    }
    count = read(fd, buf, sizeof(buf));
    close(fd);
    buf[count] = '\0';

    sscanf(buf, "cpu %ld%ld%ld%ld%ld%ld%ld", &stat_info->user, &stat_info->nice, &stat_info->system, &stat_info->idle, &stat_info->iowait, &stat_info->irq, &stat_info->softirq);

    // 查找 processes
    strs = strstr(buf, "processes");
    strcpy(cp, strs);
    sscanf(cp, "processes %ld", &stat_info->processes);

    // 查找 procs_running
    strs = strstr(buf, "procs_running");
    strcpy(cp, strs);
    // printf(" str:%s ", cp);
    sscanf(cp, "procs_running %ld", &stat_info->procs_running);

    // 查找 procs_blocked
    strs = strstr(buf, "procs_blocked");
    strcpy(cp, strs);
    sscanf(cp, "procs_blocked %ld", &stat_info->procs_blocked);
}

void ShowCPUInfo(GtkWidget *vbox)
{
	GtkWidget *label_cpu_1;
	GtkWidget *label_cpu_2;
	GtkWidget *label_cpu_3;
	GtkWidget *label_cpu_4;
	GtkWidget *label5;
	GtkWidget *label6;

    char text[50];

    label_cpu_1 = gtk_label_new("");
    sprintf(text, "\t\t型号\t\t\t： %s", cpu_info.model_name);
    gtk_misc_set_alignment(GTK_MISC(label_cpu_1), 0, 1);
    gtk_label_set_text(GTK_LABEL(label_cpu_1), text);
    gtk_container_add(GTK_CONTAINER(vbox), label_cpu_1);

    label_cpu_2 = gtk_label_new("");
    sprintf(text, "\t\t核心\t\t\t：%s", cpu_info.cores);
    gtk_misc_set_alignment(GTK_MISC(label_cpu_2), 0, 1);
    gtk_label_set_text(GTK_LABEL(label_cpu_2), text);
    gtk_container_add(GTK_CONTAINER(vbox), label_cpu_2);

    label_cpu_3 = gtk_label_new("");
    sprintf(text, "\t\t主频\t\t\t：%s MHz", cpu_info.cpu_MHz);
    gtk_misc_set_alignment(GTK_MISC(label_cpu_3), 0, 1);
    gtk_label_set_text(GTK_LABEL(label_cpu_3), text);
    gtk_container_add(GTK_CONTAINER(vbox), label_cpu_3);

    label_cpu_4 = gtk_label_new("");
    sprintf(text, "\t\t缓存\t\t\t：%s", cpu_info.cache_size);
    gtk_misc_set_alignment(GTK_MISC(label_cpu_4), 0, 1);
    gtk_label_set_text(GTK_LABEL(label_cpu_4), text);
    gtk_container_add(GTK_CONTAINER(vbox), label_cpu_4);

    label5 = gtk_label_new("");
    sprintf(text, "\t\t寻址位数\t\t：%s", cpu_info.address_sizes);
    gtk_misc_set_alignment(GTK_MISC(label5), 0, 1);
    gtk_label_set_text(GTK_LABEL(label5), text);
    gtk_container_add(GTK_CONTAINER(vbox), label5);
	
	label6 = gtk_label_new("");
    sprintf(text, "\t\tCPU位数\t\t：%s", cpu_info.clflush_size);
    gtk_misc_set_alignment(GTK_MISC(label6), 0, 1);
    gtk_label_set_text(GTK_LABEL(label6), text);
    gtk_container_add(GTK_CONTAINER(vbox), label6);
}

void ShowRatio(GtkWidget *vbox)
{
    GtkWidget *table;
    // 需要表格布局 创建4行1列的表格
    table = gtk_table_new(4, 1, TRUE);
    gtk_container_add(GTK_CONTAINER(vbox), table);

    GtkWidget *vbox1 = gtk_hbox_new(TRUE, 2);
    GtkWidget *vbox2 = gtk_hbox_new(TRUE, 2);
    GtkWidget *vbox3 = gtk_hbox_new(TRUE, 2);
    GtkWidget *vbox4 = gtk_hbox_new(TRUE, 2);

    gtk_table_attach_defaults(GTK_TABLE(table), vbox1, 0, 1, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(table), vbox2, 0, 1, 1, 2);
    gtk_table_attach_defaults(GTK_TABLE(table), vbox3, 0, 1, 2, 3);
    gtk_table_attach_defaults(GTK_TABLE(table), vbox4, 0, 1, 3, 4);

    // 每个表格的布局
    GtkWidget *label;

    label = gtk_label_new("CPU使用率:");
    gtk_misc_set_alignment(GTK_MISC(label), 0, 1);
    gtk_container_add(GTK_CONTAINER(vbox1), label);

    label = gtk_label_new("历史进程数:");
    gtk_misc_set_alignment(GTK_MISC(label), 0, 1);
    gtk_container_add(GTK_CONTAINER(vbox2), label);

    label = gtk_label_new("正在运行进程:");
    gtk_misc_set_alignment(GTK_MISC(label), 0, 1);
    gtk_container_add(GTK_CONTAINER(vbox3), label);

    label = gtk_label_new("阻塞进程:");
    gtk_misc_set_alignment(GTK_MISC(label), 0, 1);
    gtk_container_add(GTK_CONTAINER(vbox4), label);

    label_cpu_1 = gtk_label_new("");
    gtk_misc_set_alignment(GTK_MISC(label_cpu_1), 0, 1);
    gtk_container_add(GTK_CONTAINER(vbox1), label_cpu_1);

    label_cpu_2 = gtk_label_new("");
    gtk_misc_set_alignment(GTK_MISC(label_cpu_2), 0, 1);
    gtk_container_add(GTK_CONTAINER(vbox2), label_cpu_2);

    label_cpu_3 = gtk_label_new("");
    gtk_misc_set_alignment(GTK_MISC(label_cpu_3), 0, 1);
    gtk_container_add(GTK_CONTAINER(vbox3), label_cpu_3);

    label_cpu_4 = gtk_label_new("");
    gtk_misc_set_alignment(GTK_MISC(label_cpu_4), 0, 1);
    gtk_container_add(GTK_CONTAINER(vbox4), label_cpu_4);
}

gint UpdateRatio(gpointer data)
{
    char string[128];
    // 更新信息
    GetStat(&stat_info);
    
	//获取cpu利用率状态信息
	long int all;
    long int idle;
    static long int all_o = 0;
    static long int idle_o = 0;

    all = stat_info.user + stat_info.nice + stat_info.system +
          stat_info.idle + stat_info.iowait + stat_info.irq +
          stat_info.softirq;

    idle = stat_info.idle;

    stat_info.cpu_ratio = (float)((all - all_o) - (idle - idle_o)) / (all - all_o) * 100.0;

    all_o = all;
    idle_o = idle;

    static int i;
    // 放慢左边状态栏刷新速度

    if (i == 5)
    {
        sprintf(string, "%.2f %%", stat_info.cpu_ratio);
        gtk_label_set_text(GTK_LABEL(label_cpu_1), string);

        sprintf(string, "%ld", stat_info.processes);
        gtk_label_set_text(GTK_LABEL(label_cpu_2), string);

        sprintf(string, "%ld", stat_info.procs_running);
        gtk_label_set_text(GTK_LABEL(label_cpu_3), string);

        sprintf(string, "%ld", stat_info.procs_blocked);
        gtk_label_set_text(GTK_LABEL(label_cpu_4), string);

        i = 0;
    }
    i++;
    return 1;
}