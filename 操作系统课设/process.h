#ifndef __PROCESS_h__
#define __PROCESS_h__

#include "MainWindow.h"
#include "cpu.h"

#define P_COLUMN 7
#define MAX_P 300

enum
{
    PID_COLUMN,    //进程PID列
    NAME_COLUMN,  //进程名列
	PPID_COLUMN,    //进程PID列
    STATUS_COLUMN, //进程状态列
    CPU_COLUMN,  //CPU信息列
    MEMORY_COLUMN,//内存信息列
    PRIORITY_COLUMN,//内存信息列
    NP_COLUMNS
};

void CreateProcess(GtkWidget* notebook);
void GetProcessInfo(GtkListStore *store);
gboolean PopMenu(GtkWidget *widget, GdkEventButton *event, gpointer data); 
gboolean KillProcess(gpointer data);
gboolean UpdateProcess (gpointer data);
void ShowInfoDialog(char *info, int k);

#endif // __PROCESS_h__