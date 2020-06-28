#include "cpu.h"

// 申明为全局变量
CPU_INFO cpu_info;
STAT_INFO stat_info;
GdkPixmap *cgraph = NULL; //Pixmap绘图
gint cpu_graph[LENGTH];   //保存绘图数据
GtkWidget *cpu_draw_area;

// 刷新标签
GtkWidget *label_cpu_1;
GtkWidget *label_cpu_2;
GtkWidget *label_cpu_3;
GtkWidget *label_cpu_4;

void CreateCPU(GtkWidget *notebook)
{
    GtkWidget *vbox1;
    GtkWidget *vbox2;
    GtkWidget *vbox3;
    GtkWidget *table;
    int i;

    // 需要表格布局 创建10行10列的表格
    table = gtk_table_new(10, 10, TRUE);

    /* 将该表格加入到notebook中 */
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), table, gtk_label_new("CPU"));

    // 创建frame来装各种控件
    GtkWidget *CPU_frame1 = gtk_frame_new("CPU使用情况");
    GtkWidget *CPU_frame2 = gtk_frame_new("CPU使用历史曲线");
    GtkWidget *CPU_frame3 = gtk_frame_new("CPU基本信息");

	gtk_table_attach_defaults(GTK_TABLE(table), CPU_frame1, 0, 2, 5.5, 10);
    gtk_table_attach_defaults(GTK_TABLE(table), CPU_frame2, 0, 10, 0, 5.5);
    gtk_table_attach_defaults(GTK_TABLE(table), CPU_frame3, 2, 10, 5.5, 10);

    // 创建装文本的vbox
    vbox1 = gtk_vbox_new(TRUE, 5);
    gtk_container_border_width(GTK_CONTAINER(vbox1), 5);
    gtk_container_add(GTK_CONTAINER(CPU_frame1), vbox1);

    // 留出边框
    vbox2 = gtk_vbox_new(TRUE, 0);
    gtk_container_border_width(GTK_CONTAINER(vbox2), 20);
    gtk_container_add(GTK_CONTAINER(CPU_frame2), vbox2);

    vbox3 = gtk_vbox_new(TRUE, 5);
    gtk_container_border_width(GTK_CONTAINER(vbox3), 5);
    gtk_container_add(GTK_CONTAINER(CPU_frame3), vbox3);

    ShowCPUInfo(vbox3);
    ShowRatio(vbox1);

    // 创建绘图区
    cpu_draw_area = gtk_drawing_area_new();
    // 设置可以画图
    gtk_widget_set_app_paintable(cpu_draw_area, TRUE);
    gtk_drawing_area_size(GTK_DRAWING_AREA(cpu_draw_area), 400, 300);
    // 画布添加到cpu曲线框架中
    gtk_container_add(GTK_CONTAINER(vbox2), cpu_draw_area);
    gtk_widget_show(cpu_draw_area);

    // 绘图区信号连接
    // 在绘图区会触发expose_event 和 configure_event信号
    g_signal_connect(cpu_draw_area, "expose_event",
                     G_CALLBACK(cpu_expose_event), NULL);
    g_signal_connect(cpu_draw_area, "configure_event",
                     G_CALLBACK(cpu_configure_event), NULL);

    // cpu_graph 初始化
    for (i = 0; i < LENGTH; i++)
        cpu_graph[i] = LENGTH;

    // CPU使用率刷新
    g_timeout_add(500, UpdateRatio, NULL);
}

void GetOneInfo(char *path, char *name, char *info)
{
    int fd;
    char buf[3000];
    char *p = NULL;
    char *t = info;

    if ((fd = open(path, O_RDONLY)) == -1)
    {
        perror("fail to path");
        return;
    }

    read(fd, buf, sizeof(buf));
    close(fd);
    // 查找子串
    p = strstr(buf, name);

    /* 跳过标题 */
    for (; *p != ':'; p++)
        ;
    // 跳过空字符
    p += 2;
    /* 读取数值 */
    while (*p != '\n')
    {
        *(t++) = *(p++);
    }
    *t = '\0';
}

// 查找子字符串出现次数  获得处理器线程数
// str1 为被查找的串
void GetCPUInfo(void)
{
    // model_name
    GetOneInfo("/proc/cpuinfo", "model name", cpu_info.model_name);

    // cache_size
    GetOneInfo("/proc/cpuinfo", "cache size", cpu_info.cache_size);

    // cpu_MHz
    GetOneInfo("/proc/cpuinfo", "cpu MHz", cpu_info.cpu_MHz);

    // cores
    GetOneInfo("/proc/cpuinfo", "cpu cores", cpu_info.cores);

    // address_sizes
    GetOneInfo("/proc/cpuinfo", "address sizes", cpu_info.address_sizes);
	
	// address_sizes
    GetOneInfo("/proc/cpuinfo", "clflush size", cpu_info.clflush_size);

    // processor
	char buf[10240];
    FILE *fp;
    fp = fopen("/proc/cpuinfo", "r");
    fread(buf, 1, sizeof(buf), fp);
    fclose(fp);

    // 查找多少个子串
	char *str1 = buf;
	char *str2 = "processor";
	unsigned int c = 0;
    while ((str1 = strstr(str1, str2)) != NULL)
    {
        c++;
        str1++;
    }
    sprintf(cpu_info.processor, "%hd", c);
}

void ShowCPUInfo(GtkWidget *vbox)
{
	GtkWidget *label1;
	GtkWidget *label2;
	GtkWidget *label3;
	GtkWidget *label4;
	GtkWidget *label5;
	GtkWidget *label6;
	GtkWidget *label7;

    char text[50];

    label1 = gtk_label_new("");
    sprintf(text, "\t\t型号\t\t\t： %s", cpu_info.model_name);
    gtk_misc_set_alignment(GTK_MISC(label1), 0, 0.5);
    gtk_label_set_text(GTK_LABEL(label1), text);
    gtk_container_add(GTK_CONTAINER(vbox), label1);

    label2 = gtk_label_new("");
    sprintf(text, "\t\t核心\t\t\t：%s", cpu_info.cores);
    gtk_misc_set_alignment(GTK_MISC(label2), 0, 0.5);
    gtk_label_set_text(GTK_LABEL(label2), text);
    gtk_container_add(GTK_CONTAINER(vbox), label2);

    label3 = gtk_label_new("");
    sprintf(text, "\t\t逻辑处理器\t：%s", cpu_info.processor);
    gtk_misc_set_alignment(GTK_MISC(label3), 0, 0.5);
    gtk_label_set_text(GTK_LABEL(label3), text);
    gtk_container_add(GTK_CONTAINER(vbox), label3);

    label4 = gtk_label_new("");
    sprintf(text, "\t\t主频\t\t\t：%s MHz", cpu_info.cpu_MHz);
    gtk_misc_set_alignment(GTK_MISC(label4), 0, 0.5);
    gtk_label_set_text(GTK_LABEL(label4), text);
    gtk_container_add(GTK_CONTAINER(vbox), label4);

    label5 = gtk_label_new("");
    sprintf(text, "\t\t缓存\t\t\t：%s", cpu_info.cache_size);
    gtk_misc_set_alignment(GTK_MISC(label5), 0, 0.5);
    gtk_label_set_text(GTK_LABEL(label5), text);
    gtk_container_add(GTK_CONTAINER(vbox), label5);

    label6 = gtk_label_new("");
    sprintf(text, "\t\t寻址位数\t\t：%s", cpu_info.address_sizes);
    gtk_misc_set_alignment(GTK_MISC(label6), 0, 0.5);
    gtk_label_set_text(GTK_LABEL(label6), text);
    gtk_container_add(GTK_CONTAINER(vbox), label6);
	
	label7 = gtk_label_new("");
    sprintf(text, "\t\tCPU位数\t\t：%s", cpu_info.clflush_size);
    gtk_misc_set_alignment(GTK_MISC(label7), 0, 0.5);
    gtk_label_set_text(GTK_LABEL(label7), text);
    gtk_container_add(GTK_CONTAINER(vbox), label7);
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
    gtk_misc_set_alignment(GTK_MISC(label), 0, 0.2);
    gtk_container_add(GTK_CONTAINER(vbox1), label);

    label = gtk_label_new("历史进程数:");
    gtk_misc_set_alignment(GTK_MISC(label), 0, 0.2);
    gtk_container_add(GTK_CONTAINER(vbox2), label);

    label = gtk_label_new("正在运行进程:");
    gtk_misc_set_alignment(GTK_MISC(label), 0, 0.2);
    gtk_container_add(GTK_CONTAINER(vbox3), label);

    label = gtk_label_new("阻塞进程:");
    gtk_misc_set_alignment(GTK_MISC(label), 0, 0.2);
    gtk_container_add(GTK_CONTAINER(vbox4), label);

    label_cpu_1 = gtk_label_new("");
    gtk_misc_set_alignment(GTK_MISC(label_cpu_1), 0, 0.25);
    gtk_container_add(GTK_CONTAINER(vbox1), label_cpu_1);

    label_cpu_2 = gtk_label_new("");
    gtk_misc_set_alignment(GTK_MISC(label_cpu_2), 0, 0.25);
    gtk_container_add(GTK_CONTAINER(vbox2), label_cpu_2);

    label_cpu_3 = gtk_label_new("");
    gtk_misc_set_alignment(GTK_MISC(label_cpu_3), 0, 0.25);
    gtk_container_add(GTK_CONTAINER(vbox3), label_cpu_3);

    label_cpu_4 = gtk_label_new("");
    gtk_misc_set_alignment(GTK_MISC(label_cpu_4), 0, 0.25);
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

    // 绘图
    DrawCPUGraph();
    return 1;
}

// 绘图信号回调函数
gboolean cpu_configure_event(GtkWidget *widget, GdkEventConfigure *event, gpointer data)
{
    if (cgraph)
    {
        g_object_unref(cgraph);
    }

    //创建 Pixmap 后端位图
    cgraph = gdk_pixmap_new(widget->window,
                            widget->allocation.width, widget->allocation.height, -1);

    //重新绘制 Pixmap
    gdk_draw_rectangle(cgraph, widget->style->white_gc, TRUE, 0, 0,
                       widget->allocation.width, widget->allocation.height);
    return TRUE;
}

gboolean cpu_expose_event(GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
    gdk_draw_drawable(widget->window,
                      widget->style->fg_gc[GTK_WIDGET_STATE(widget)],
                      cgraph,
                      event->area.x, event->area.y,
                      event->area.x, event->area.y,
                      event->area.width, event->area.height);
    return TRUE;
}

// CPU 绘图曲线
void DrawCPUGraph(void)
{
    int width, height, ratio;
    float step_w, step_h;
    int i;

    // 如果pixmap没有创建成功，则不绘图
    if (cgraph == NULL)
        return;

    // 设置风格
    GdkGC *gc = gdk_gc_new(GDK_DRAWABLE(cgraph));
    

    // 清除位图，并初始化为灰色
    gdk_draw_rectangle(GDK_DRAWABLE(cgraph), window->style->dark_gc[4], TRUE, 0, 0,
                       cpu_draw_area->allocation.width,
                       cpu_draw_area->allocation.height);

    // 获得绘图区大小
    width = cpu_draw_area->allocation.width;
    height = cpu_draw_area->allocation.height;

    // 获得当前CPU利用率
    ratio = (int)stat_info.cpu_ratio;
    // 移动数据 向前移动
    cpu_graph[LENGTH - 1] = LENGTH - (float)ratio / 100 * LENGTH - 1;
    for (i = 0; i < LENGTH - 1; i++)
    {
        cpu_graph[i] = cpu_graph[i + 1];
    }

    // 计算步长
    step_w = (float)width / LENGTH;
    step_h = (float)height / LENGTH;
    // 设置颜色
    GdkColor color;
    gdk_color_parse("#ffcc80", &color);
    // 设置前景色的函数……
    gdk_gc_set_rgb_fg_color(gc, &color);


    // 连线
    for (i = LENGTH - 1; i >= 1; i--)
    {
        gdk_draw_line(cgraph, gc, i * step_w, cpu_graph[i] * step_h,
                      (i - 1) * step_w, cpu_graph[i - 1] * step_h);
    }

    gtk_widget_queue_draw(cpu_draw_area); //触发信号,刷新图片的整个区域
}