#include "memory.h"

MEM_INFO mem_info;

GtkWidget *label1;
GtkWidget *label2;
GtkWidget *label3;
GtkWidget *label4;
GtkWidget *label5;
GtkWidget *label6;
GtkWidget *label7;
GtkWidget *label8;
GtkWidget *label9;
GtkWidget *label10;

void CreateMemory(GtkWidget* notebook)
{
    GtkWidget *table;
    GtkWidget *vbox1;
    GtkWidget *vbox2;
    GtkWidget *vbox3;
    GtkWidget *vbox4;
	
    // 需要表格布局 创建10行10列的表格
    table = gtk_table_new(10, 10, TRUE);
    /* 将该标签页加入到notebook中 */
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), table, gtk_label_new("CPU/MEM"));

    // 创建frame来装各种控件
    GtkWidget *MEMO_frame1 = gtk_frame_new("内存详细情况");
    GtkWidget *MEMO_frame2 = gtk_frame_new("交换分区详细情况");
	GtkWidget *MEMO_frame3 = gtk_frame_new("CPU使用情况");
    GtkWidget *MEMO_frame4 = gtk_frame_new("CPU基本信息");

    gtk_table_attach_defaults(GTK_TABLE(table), MEMO_frame1, 0, 6, 5, 10);
    gtk_table_attach_defaults(GTK_TABLE(table), MEMO_frame2, 6, 10, 5, 10);
    gtk_table_attach_defaults(GTK_TABLE(table), MEMO_frame3, 0, 3, 0, 5);
    gtk_table_attach_defaults(GTK_TABLE(table), MEMO_frame4, 3, 10, 0, 5);

    // 创建装文本的vbox
    vbox1 = gtk_vbox_new(TRUE, 2);
    gtk_container_add(GTK_CONTAINER(MEMO_frame1), vbox1);

    vbox2 = gtk_vbox_new(TRUE, 2);
    gtk_container_add(GTK_CONTAINER(MEMO_frame2), vbox2);
	
	vbox3 = gtk_vbox_new(TRUE, 2);
    gtk_container_add(GTK_CONTAINER(MEMO_frame3), vbox3);

    vbox4 = gtk_vbox_new(TRUE, 2);
    gtk_container_add(GTK_CONTAINER(MEMO_frame4), vbox4);

    ShowMemInfo(vbox1);
    ShowSwapInfo(vbox2);
	ShowRatio(vbox3);
	ShowCPUInfo(vbox4);

    // 内存使用率
    g_timeout_add(1000, UpdateMemInfo, NULL);
	g_timeout_add(500, UpdateRatio, NULL);
}

void ShowMemInfo(GtkWidget *vbox)
{
    GtkWidget *table;
    table = gtk_table_new(6, 1, TRUE);
    gtk_container_add(GTK_CONTAINER(vbox), table);

    GtkWidget *vbox1 = gtk_hbox_new(TRUE, 1);
    GtkWidget *vbox2 = gtk_hbox_new(TRUE, 1);
    GtkWidget *vbox3 = gtk_hbox_new(TRUE, 1);
    GtkWidget *vbox4 = gtk_hbox_new(TRUE, 1);
    GtkWidget *vbox5 = gtk_hbox_new(TRUE, 1);
	GtkWidget *vbox6 = gtk_hbox_new(TRUE, 1);

    gtk_table_attach_defaults(GTK_TABLE(table), vbox1, 0, 1, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(table), vbox2, 0, 1, 1, 2);
    gtk_table_attach_defaults(GTK_TABLE(table), vbox3, 0, 1, 2, 3);
    gtk_table_attach_defaults(GTK_TABLE(table), vbox4, 0, 1, 3, 4);
    gtk_table_attach_defaults(GTK_TABLE(table), vbox5, 0, 1, 4, 5);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox6, 0, 1, 5, 6);

    // 每个表格的布局
    GtkWidget *label;

    label = gtk_label_new("内存使用率");
    gtk_misc_set_alignment(GTK_MISC(label), 0, 1);
    gtk_container_add(GTK_CONTAINER(vbox1), label);
	
    label1 = gtk_label_new("");
    gtk_misc_set_alignment(GTK_MISC(label1), 0, 1);
    gtk_container_add(GTK_CONTAINER(vbox1), label1);

    label = gtk_label_new("(已使用) 总内存");
    gtk_misc_set_alignment(GTK_MISC(label), 0, 1);
    gtk_container_add(GTK_CONTAINER(vbox2), label);

    label2 = gtk_label_new("");
    gtk_misc_set_alignment(GTK_MISC(label2), 0, 1);
    gtk_container_add(GTK_CONTAINER(vbox2), label2);

    label = gtk_label_new("空闲内存");
    gtk_misc_set_alignment(GTK_MISC(label), 0, 1);
    gtk_container_add(GTK_CONTAINER(vbox3), label);
	
    label3 = gtk_label_new("");
    gtk_misc_set_alignment(GTK_MISC(label3), 0, 1);
    gtk_container_add(GTK_CONTAINER(vbox3), label3);

    label = gtk_label_new("已缓冲 / 已缓存");
    gtk_misc_set_alignment(GTK_MISC(label), 0, 1);
    gtk_container_add(GTK_CONTAINER(vbox4), label);
	
    label4 = gtk_label_new("");
    gtk_misc_set_alignment(GTK_MISC(label4), 0, 1);
    gtk_container_add(GTK_CONTAINER(vbox4), label4);

    label = gtk_label_new("活跃内存 / 不活跃内存");
    gtk_misc_set_alignment(GTK_MISC(label), 0, 1);
    gtk_container_add(GTK_CONTAINER(vbox5), label);

    label5 = gtk_label_new("");
    gtk_misc_set_alignment(GTK_MISC(label5), 0, 1);
    gtk_container_add(GTK_CONTAINER(vbox5), label5);
	
	label = gtk_label_new("可用内存");
    gtk_misc_set_alignment(GTK_MISC(label), 0, 1);
    gtk_container_add(GTK_CONTAINER(vbox6), label);
	
	label6 = gtk_label_new("");
    gtk_misc_set_alignment(GTK_MISC(label6), 0, 1);
    gtk_container_add(GTK_CONTAINER(vbox6), label6);
}

void ShowSwapInfo(GtkWidget *vbox)
{
    GtkWidget *table;

    table = gtk_table_new(4, 1, TRUE);
    gtk_container_add(GTK_CONTAINER(vbox), table);

    GtkWidget *vbox1 = gtk_hbox_new(TRUE, 0);
    GtkWidget *vbox2 = gtk_hbox_new(TRUE, 0);
    GtkWidget *vbox3 = gtk_hbox_new(TRUE, 0);
    GtkWidget *vbox4 = gtk_hbox_new(TRUE, 0);

    gtk_table_attach_defaults(GTK_TABLE(table), vbox1, 0, 1, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(table), vbox2, 0, 1, 1, 2);
    gtk_table_attach_defaults(GTK_TABLE(table), vbox3, 0, 1, 2, 3);
    gtk_table_attach_defaults(GTK_TABLE(table), vbox4, 0, 1, 3, 4);

    // 每个表格的布局
    GtkWidget *label;

    label = gtk_label_new("交换分区使用率");
    gtk_misc_set_alignment(GTK_MISC(label), 0, 1);
    gtk_container_add(GTK_CONTAINER(vbox1), label);
	
	label7 = gtk_label_new("");
    gtk_misc_set_alignment(GTK_MISC(label7), 0, 1);
    gtk_container_add(GTK_CONTAINER(vbox1), label7);

    label = gtk_label_new("(已使用) 总交换分区");
    gtk_misc_set_alignment(GTK_MISC(label), 0, 1);
    gtk_container_add(GTK_CONTAINER(vbox2), label);

    label8 = gtk_label_new("");
    gtk_misc_set_alignment(GTK_MISC(label8), 0, 1);
    gtk_container_add(GTK_CONTAINER(vbox2), label8);

    label = gtk_label_new("可用交换分区");
    gtk_misc_set_alignment(GTK_MISC(label), 0, 1);
    gtk_container_add(GTK_CONTAINER(vbox3), label);

    label9 = gtk_label_new("");
    gtk_misc_set_alignment(GTK_MISC(label9), 0, 1);
    gtk_container_add(GTK_CONTAINER(vbox3), label9);

    label = gtk_label_new("等待写回 / 正在写回");
    gtk_misc_set_alignment(GTK_MISC(label), 0, 1);
    gtk_container_add(GTK_CONTAINER(vbox4), label);
	
	label10 = gtk_label_new("");
    gtk_misc_set_alignment(GTK_MISC(label10), 0, 1);
    gtk_container_add(GTK_CONTAINER(vbox4), label10);

}

void GetMemInfo(){
	int fd;
    char buf[3000];
    char *p = NULL;
    char cache[30];

    if ((fd = open("/proc/meminfo", O_RDONLY)) == -1)
    {
        perror("fail to meminfo");
        return ;
    }
    read(fd, buf, sizeof(buf));
    close(fd);
    // 查找子串
    p = strstr(buf, "MemTotal");
    sscanf(p, "%s %ld",cache, &mem_info.MemTotal);
	p = strstr(buf, "MemFree");
    sscanf(p, "%s %ld",cache, &mem_info.MemFree);
	p = strstr(buf, "MemAvailable");
    sscanf(p, "%s %ld",cache, &mem_info.MemAvailable);
	p = strstr(buf, "Buffers");
    sscanf(p, "%s %ld",cache, &mem_info.Buffers);
	p = strstr(buf, "Cached");
    sscanf(p, "%s %ld",cache, &mem_info.Cached);
	p = strstr(buf, "Active");
    sscanf(p, "%s %ld",cache, &mem_info.Active);
	p = strstr(buf, "Inactive");
    sscanf(p, "%s %ld",cache, &mem_info.Inactive);
	p = strstr(buf, "SwapTotal");
    sscanf(p, "%s %ld",cache, &mem_info.SwapTotal);
	p = strstr(buf, "SwapFree");
    sscanf(p, "%s %ld",cache, &mem_info.SwapFree);
	p = strstr(buf, "Dirty");
    sscanf(p, "%s %ld",cache, &mem_info.Dirty);
	p = strstr(buf, "Writeback");
    sscanf(p, "%s %ld",cache, &mem_info.Writeback);
	
	mem_info.memoredio = (float)(mem_info.MemTotal - mem_info.MemFree) / mem_info.MemTotal *100;
    mem_info.swapredio = (float)(mem_info.SwapTotal - mem_info.SwapFree) / mem_info.SwapTotal *100;
}

gint UpdateMemInfo(gpointer data)
{
    char string[128];
    // 更新信息
    //内存
	GetMemInfo();

    sprintf(string, "%.2f %%", mem_info.memoredio);
    gtk_label_set_text(GTK_LABEL(label1), string);

    sprintf(string, "(%.2fG) %.2fG", (mem_info.MemTotal - mem_info.MemFree) / 1024.0 /1024.0, mem_info.MemTotal / 1024.0 /1024.0);
    gtk_label_set_text(GTK_LABEL(label2), string);

    sprintf(string, "%.2fM", mem_info.MemFree / 1024.0);
    gtk_label_set_text(GTK_LABEL(label3), string);

    sprintf(string, "%.2fM / %.2fM ", mem_info.Buffers / 1024.0, mem_info.Cached /1024.0);
    gtk_label_set_text(GTK_LABEL(label4), string);

    sprintf(string, "%.2fM / %.2fM ", mem_info.Active / 1024.0, mem_info.Inactive /1024.0);
    gtk_label_set_text(GTK_LABEL(label5), string);
	
	sprintf(string, "%.2fG", mem_info.MemAvailable / 1024.0 /1024.0);
    gtk_label_set_text(GTK_LABEL(label6), string);
	
	sprintf(string, "%.2f %%", mem_info.swapredio);
    gtk_label_set_text(GTK_LABEL(label7), string);

    sprintf(string, "(%.2fM) %.2fG", (mem_info.SwapTotal - mem_info.SwapFree) / 1024.0 ,
                     mem_info.SwapTotal / 1024.0 / 1024.0);
    gtk_label_set_text(GTK_LABEL(label8), string);

    sprintf(string, "%.2fM", mem_info.SwapFree /1024.0);
    gtk_label_set_text(GTK_LABEL(label9), string);

    sprintf(string, "%.2fM / %.2fM",mem_info.Dirty / 1024.0, mem_info.Writeback /1024.0);
    gtk_label_set_text(GTK_LABEL(label10), string);

    return 1;
}