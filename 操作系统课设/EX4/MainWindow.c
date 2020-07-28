#include "MainWindow.h"
#include "cpu.h"
#include "memory.h"
#include "summary.h"
#include "status.h"
#include "process.h"

GtkWidget *window;

int main(int argc, char **argv)
{

	//创建主窗口
	GtkWidget *main_vbox;

	gtk_init(&argc, &argv);
	// 主窗口设置
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "系统监视器");
	// 窗口大小
	gtk_window_set_default_size(GTK_WINDOW(window), 1000, 800);
	// 窗口初始位置
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	// 关闭信号链接
	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	// 创建一个垂直窗口
	main_vbox = gtk_vbox_new(FALSE, 2);
	// 周围的间距
	gtk_container_set_border_width(GTK_CONTAINER(main_vbox), 2);
	// 添加进入主窗口
	gtk_container_add(GTK_CONTAINER(window), main_vbox);

	/* 建立多标签页notebook */
	GtkWidget *notebook = gtk_notebook_new();
	gtk_notebook_set_tab_pos((GtkNotebook *)notebook, GTK_POS_LEFT); //位置放置在左边
	gtk_notebook_set_show_border((GtkNotebook *)notebook, FALSE);
	gtk_box_pack_start(GTK_BOX(main_vbox), notebook, TRUE, TRUE, 0);

	// 获取CPU基本信息
	GetCPUInfo();

	// 添加子页面
	CreateSummary(notebook);
	CreateMemory(notebook);
	CreateProcess(notebook);
	ShowStatus(main_vbox);
	gtk_widget_show_all(window);

	gtk_main();
	return 0;
}