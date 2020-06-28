#ifndef __CPU_h__
#define __CPU_h__
#include "MainWindow.h"

#define LENGTH 200 //绘图长度

typedef struct cpuInfo
{
    char model_name[30];
    char cache_size[20];
    char cpu_MHz[20];
    char cores[10];
    char processor[20];  //逻辑处理器数
    char address_sizes[30];  //寻址位数
	char clflush_size[5];
} CPU_INFO, *p_cpuinfo;

typedef struct statinfo
{
    long int user;  // 用户模式
    long int nice;  // 低优先级用户模式
    long int system;  // 内核模式
    long int idle;  // 空闲的处理器时间
    long int iowait;  // io等待
    long int irq;  // 硬中断时间
    long int softirq;  // 软中断时间
    long int processes;  //运行进程
    long int procs_running;  //正在运行
    long int procs_blocked;  //阻塞

    float cpu_ratio;
}STAT_INFO, *p_statinfo;

extern CPU_INFO cpu_info;
extern STAT_INFO stat_info;
extern gint cpu_graph[LENGTH];

void CreateCPU(GtkWidget* notebook);
void GetOneInfo(char *path, char *name, char* info);
void ShowCPUInfo(GtkWidget *vbox);
void GetCPUInfo(void);
void ShowRatio(GtkWidget *data);
gint UpdateRatio(gpointer data);
void GetStat(p_statinfo istat);

gboolean cpu_configure_event (GtkWidget *widget, GdkEventConfigure *event, gpointer data);
gboolean cpu_expose_event (GtkWidget *widget, GdkEventExpose *event, gpointer data);
void DrawCPUGraph(void);

#endif // __CPU_h__