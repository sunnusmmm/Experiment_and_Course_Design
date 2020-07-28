#include "process.h"

long int p_cpu_time_o[MAX_P];
long int cpu_all_o;
GtkListStore *process_store;
GtkWidget *ptree_view;
pid_t g_pid;

void CreateProcess(GtkWidget *notebook)
{

    GtkWidget *vbox;
    GtkWidget *scrolled_window;
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    // 创建盒装容器并添加
    vbox = gtk_vbox_new(FALSE, 5);
    gtk_container_border_width(GTK_CONTAINER(vbox), 5);

    /* 将该标签页加入到notebook中 */
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), vbox, gtk_label_new("进程信息"));

    scrolled_window = gtk_scrolled_window_new(NULL, NULL); //添加滚动窗口控件
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0);

    //添加list控件
    process_store = gtk_list_store_new(7, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING, G_TYPE_STRING);

    //添加tree view控件,显示进程信息树
    ptree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(process_store));
    g_object_unref(G_OBJECT(process_store));                       //减少引用次数
    gtk_container_add(GTK_CONTAINER(scrolled_window), ptree_view); //Tree in scrolled_window
    // 悬浮菜单
    gtk_tree_view_set_hover_selection(GTK_TREE_VIEW(ptree_view), FALSE);
    // 右键弹出菜单连接
    g_signal_connect(G_OBJECT(ptree_view), "button-release-event", G_CALLBACK(PopMenu), NULL);
    // 显示列
    renderer = gtk_cell_renderer_text_new(); //添加一个cell_renderer_text用于显示文字
    column = gtk_tree_view_column_new_with_attributes("PID", renderer, "text", 0, NULL); //新建一列
    gtk_tree_view_append_column(GTK_TREE_VIEW(ptree_view), column);               //将该列加到树中
    gtk_tree_view_column_set_min_width(column, 100);
	
	renderer = gtk_cell_renderer_text_new(); //添加一个cell_renderer_text用于显示文字
    column = gtk_tree_view_column_new_with_attributes("进程名", renderer, "text", 1, NULL); //新建一列
    gtk_tree_view_append_column(GTK_TREE_VIEW(ptree_view), column);               //将该列加到树中
    gtk_tree_view_column_set_min_width(column, 200);
	
    renderer = gtk_cell_renderer_text_new(); //添加一个cell_renderer_text用于显示文字
    column = gtk_tree_view_column_new_with_attributes("PPID", renderer, "text", 2, NULL); //新建一列
    gtk_tree_view_append_column(GTK_TREE_VIEW(ptree_view), column);               //将该列加到树中
    gtk_tree_view_column_set_min_width(column, 100);
	
	renderer = gtk_cell_renderer_text_new(); //添加一个cell_renderer_text用于显示文字
    column = gtk_tree_view_column_new_with_attributes("状态", renderer, "text", 3, NULL); //新建一列
    gtk_tree_view_append_column(GTK_TREE_VIEW(ptree_view), column);               //将该列加到树中
    gtk_tree_view_column_set_min_width(column, 150);
	
	renderer = gtk_cell_renderer_text_new(); //添加一个cell_renderer_text用于显示文字
    column = gtk_tree_view_column_new_with_attributes("CPU利用率", renderer, "text", 4, NULL); //新建一列
    gtk_tree_view_append_column(GTK_TREE_VIEW(ptree_view), column);               //将该列加到树中
    gtk_tree_view_column_set_min_width(column, 100);
	
	renderer = gtk_cell_renderer_text_new(); //添加一个cell_renderer_text用于显示文字
    column = gtk_tree_view_column_new_with_attributes("占用内存", renderer, "text", 5, NULL); //新建一列
    gtk_tree_view_append_column(GTK_TREE_VIEW(ptree_view), column);               //将该列加到树中
    gtk_tree_view_column_set_min_width(column, 100);
	
	renderer = gtk_cell_renderer_text_new(); //添加一个cell_renderer_text用于显示文字
    column = gtk_tree_view_column_new_with_attributes("优先级", renderer, "text", 6, NULL); //新建一列
    gtk_tree_view_append_column(GTK_TREE_VIEW(ptree_view), column);               //将该列加到树中
    gtk_tree_view_column_set_min_width(column, 100);
	
    GetProcessInfo(process_store);
    g_timeout_add(1500, UpdateProcess, NULL);
}

void GetProcessInfo(GtkListStore *store)
{
    DIR *dir;
    int fd;
    GtkTreeIter iter;
    struct dirent *entry;
    char dir_buf[256];//文件名
    char buffer[1024];//文件内容
	//需要的信息
    char process_status[30], memo_size[20], ratio[20], pid[10], ppid[10], process_name[50], status, priority[5];
	//空
    char noneed[20];

    long int utime_now, stime_now, cutime_now, cstime_now;
    long int p_cpu_time, cpu_all;
    long int page;
    float p_ratio;
    int num = 0; //用于遍历

    //用opendir打开一个与给定目录名相对应的目录流
    dir = opendir("/proc");

    cpu_all = stat_info.user + stat_info.nice + stat_info.system +
              stat_info.idle + stat_info.iowait + stat_info.irq +
              stat_info.softirq;

    while ((entry = readdir(dir)) != NULL)
    {
        // 筛选名字为数字的文件夹
        if ((entry->d_name[0] >= '0') && (entry->d_name[0] <= '9'))
        {
            // 生成文件名
            sprintf(dir_buf, "/proc/%s/stat", entry->d_name);
            fd = open(dir_buf, O_RDONLY); //只读打开
            read(fd, buffer, sizeof(buffer));
            close(fd);

            // 14-17cpu 19有先 24内存
			//utime 该任务在用户态运行的时间，单位为jiffies
			//stime 该任务在核心态运行的时间，单位为jiffies
			//cutime 累计的该任务的所有的waited-for进程曾经在用户态运行的时间，单位为jiffies
			//cstime 累计的该任务的所有的waited-for进程曾经在核心态运行的时间，单位为jiffies
            sscanf(buffer, "%s (%s %c %s %s %s %s %s %s %s %s %s %s %ld %ld %ld %ld %s %s %s %s %s %s %ld",
                   pid, process_name, &status, ppid, noneed, noneed, noneed, noneed, noneed, noneed,
                   noneed, noneed, noneed, &utime_now, &stime_now, &cutime_now, &cstime_now, noneed,
                   priority, noneed, noneed, noneed, noneed, &page);

            process_name[strlen(process_name) - 1] = '\0';

            // 状态转换
            if (status == 'S')
                strcpy(process_status, "Sleeping");
            else if (status == 'R')
                strcpy(process_status, "Runnign");
            else if (status == 'T')
                strcpy(process_status, "Stopped");
            else if (status == 'D')
                strcpy(process_status, "Disk_sleep");
            else if (status == 'Z')
                strcpy(process_status, "Zombie");
            else if (status == 'I')
                strcpy(process_status, "I");

            // 计算CPU使用率
            p_cpu_time = utime_now + stime_now + cutime_now + cstime_now;
            p_ratio = (float)(p_cpu_time - p_cpu_time_o[num]) /
                      (cpu_all - cpu_all_o);
            sprintf(ratio, "%.2f %%", 100.0 * p_ratio);

            // 使用getpagesize获得系统内存页
            sprintf(memo_size, "%.2fM", (float)page * getpagesize() / 1024.0 / 1024.0);

            gtk_list_store_append(store, &iter); //增加到列表
            gtk_list_store_set(store, &iter, 0, pid, 1, process_name, 2, ppid, 3, process_status, 4, ratio, 5, memo_size, 6, priority, -1);

            p_cpu_time_o[num] = p_cpu_time;
            num = (num + 1) % MAX_P;
        }
    }
    cpu_all_o = cpu_all;
    closedir(dir);
}

gboolean UpdateProcess(gpointer data)
{
    gtk_list_store_clear(process_store); //清空
    GetProcessInfo(process_store);
    return TRUE;
}

gboolean PopMenu(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
    GtkWidget *menu;
    GtkWidget *kill, *refresh;
    GtkTreeSelection *selection;
    GtkTreeModel *model;
    GtkTreeIter iter;
    char *pid;
    // 单击 3为右键
    if (event->type == GDK_BUTTON_RELEASE && event->button == 3)
    {
        // 先获得该进程pid
        selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(ptree_view));
        if (gtk_tree_selection_get_selected(selection, &model, &iter))
        {
            gtk_tree_model_get(model, &iter, 0, &pid, -1); //在数的相应列中获得该进程的PID
            g_pid = atoi(pid);//字符串转换成长整数
            menu = gtk_menu_new();//创建菜单
            refresh = gtk_menu_item_new_with_label("刷新进程");
            g_signal_connect(G_OBJECT(refresh), "activate", G_CALLBACK(UpdateProcess), widget);
            gtk_menu_shell_append(GTK_MENU_SHELL(menu), refresh);
            kill = gtk_menu_item_new_with_label("结束进程");
            g_signal_connect(G_OBJECT(kill), "activate", G_CALLBACK(KillProcess), widget);
            gtk_menu_shell_append(GTK_MENU_SHELL(menu), kill);
            gtk_widget_show_all(GTK_WIDGET(menu));
            gtk_menu_popup(GTK_MENU(menu), NULL, NULL, NULL, NULL, event->button, event->time);
            return TRUE;
        }
    }
    return FALSE;
}

gboolean KillProcess(gpointer data)
{
    int result;
    GtkWidget *dialog; //声明一个对话框

    dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_QUESTION, GTK_BUTTONS_YES_NO, "确定结束该进程吗？");
    gtk_window_set_title(GTK_WINDOW(dialog), "Kill");
    result = gtk_dialog_run(GTK_DIALOG(dialog));

    if (result == GTK_RESPONSE_YES)
    {
		kill(g_pid, SIGTERM);
    }
    gtk_widget_destroy(dialog); //删除对话框
    return TRUE;
}