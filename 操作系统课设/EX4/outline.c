#include "outline.h"

void CreateOutline(GtkWidget *notebook)
{

    GtkWidget *hbox;
    GtkWidget *vbox;
    INFO info;
    GdkPixbuf *src;

    // 清空结构图脏数据
    memset(&info, '\0', sizeof(info));

    // 创建水平盒装容器并添加
    hbox = gtk_vbox_new(TRUE, 5);
    gtk_container_border_width(GTK_CONTAINER(hbox), 5);

    /* 将该标签页加入到notebook中 */
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), hbox, gtk_label_new("系统概要"));


    //修改图片大小
	src = gdk_pixbuf_new_from_file("./image/ubuntu.jpg", NULL);
    GdkPixbuf *dst = gdk_pixbuf_scale_simple(src, 200, 200, GDK_INTERP_BILINEAR);
    GtkWidget *image = gtk_image_new_from_pixbuf(dst);
    //将image_two添加到hbox中
    gtk_container_add(GTK_CONTAINER(hbox), image);
    //pixbuf使用完需要释放其中资源
    g_object_unref(src);
    g_object_unref(dst);

    // 创建垂直盒装容器并添加
    vbox = gtk_vbox_new(TRUE, 5);
    gtk_container_border_width(GTK_CONTAINER(vbox), 20);
    gtk_container_add(GTK_CONTAINER(hbox), vbox);

	// 获得系统信息
    GetInfo(&info);
    // 显示信息
    ShowInfo(vbox, info);
}

void GetInfo(p_info info)
{
    int fd;
    int bytes;
    char buf[50];

    // 读取主机名
    //打开存储系统平均负载的proc文件
    if ((fd = open("/proc/sys/kernel/hostname", O_RDONLY)) == -1)
    {
        perror("fail to hostname");
        strcpy("none", info->hostname);
    }
    else
    {
        bytes = read(fd, buf, sizeof(buf));
        buf[bytes] = '\0';
        strcpy(info->hostname, buf);
    }
    close(fd);

    // 获得系统及版本号
    if ((fd = open("/etc/issue", O_RDONLY)) == -1)
    {
        perror("fail to ver");
        strcpy("none", info->version);
    }
    else
    {
        bytes = read(fd, buf, sizeof(buf));
        buf[bytes - 7] = '\0';
        strcpy(info->version, buf);
    }
    close(fd);

    if ((fd = open("/proc/version", O_RDONLY)) == -1)
    {
        perror("fail to kernel");
        strcpy("none", info->kernel);
    }
    else
    {
        bytes = read(fd, buf, 50);
        buf[22] = '\0';
        strcpy(info->kernel, buf);
    }
    close(fd);

    // 从cpu获得cpu信息
    strcpy(info->cpu, cpu_info.model_name);

    // 从memory获得内存信息
    GetMemoInfo();
    sprintf(info->memory, "%.2fG", memo_info.MemTotal /1024.0 /1024.0);

}

void ShowInfo(GtkWidget *vbox, INFO info)
{
	
	GtkWidget *label1;
	GtkWidget *label2;
	GtkWidget *label3;
	GtkWidget *label4;
	GtkWidget *label5;
	
    char text[50];

    label1 = gtk_label_new("");
    sprintf(text, "计算机名\t\t：%s", info.hostname);
    gtk_misc_set_alignment(GTK_MISC(label1), 0, 0.5);
    gtk_label_set_text(GTK_LABEL(label1), text);
    gtk_container_add(GTK_CONTAINER(vbox), label1);

    label2 = gtk_label_new("");
    sprintf(text, "系统版本号\t：%s", info.version);
    gtk_misc_set_alignment(GTK_MISC(label2), 0, 0.5);
    gtk_label_set_text(GTK_LABEL(label2), text);
    gtk_container_add(GTK_CONTAINER(vbox), label2);

    label3 = gtk_label_new("");
    sprintf(text, "内核版本号\t：%s", info.kernel);
    gtk_misc_set_alignment(GTK_MISC(label3), 0, 0.5);
    gtk_label_set_text(GTK_LABEL(label3), text);
    gtk_container_add(GTK_CONTAINER(vbox), label3);

    label4 = gtk_label_new("");
    sprintf(text, "CPU\t\t\t：%s", info.cpu);
    gtk_misc_set_alignment(GTK_MISC(label4), 0, 0.5);
    gtk_label_set_text(GTK_LABEL(label4), text);
    gtk_container_add(GTK_CONTAINER(vbox), label4);

    label5 = gtk_label_new("");
    sprintf(text, "安装内存\t\t：%s", info.memory);
    gtk_misc_set_alignment(GTK_MISC(label5), 0, 0.5);
    gtk_label_set_text(GTK_LABEL(label5), text);
    gtk_container_add(GTK_CONTAINER(vbox), label5);
}


