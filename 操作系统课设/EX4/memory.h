#ifndef __MEMORY_h__
#define __MEMORY_h__

#include "MainWindow.h"
#include "cpu.h"

typedef struct memInfo
{
    long int MemTotal;
    long int MemFree;
	long int MemAvailable;
    long int Buffers; //缓冲
    long int Cached;  //缓存
    long int Active;
    long int Inactive;

    long int SwapTotal;
    long int SwapFree;
    long int Dirty;     //等待写回的数据大小
    long int Writeback;  //正在写回的数据大小

    float memoredio;
    float swapredio;
}MEM_INFO, *p_memInfo;

extern MEM_INFO mem_info;

void CreateMemory(GtkWidget* notebook);
void GetMemInfo();
void ShowMemInfo(GtkWidget *vbox);
void ShowSwapInfo(GtkWidget *vbox);
gint UpdateMemInfo(gpointer data);


#endif // __MEMORY_h__