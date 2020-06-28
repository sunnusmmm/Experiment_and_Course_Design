#ifndef __OUTLINE_h__
#define __OUTLINE_h__

#include "MainWindow.h"
#include "cpu.h"
#include "memory.h"

typedef struct info
{
    char hostname[50];
    char version[50];
    char kernel[50];
    char cpu[50];
    char memory[50];
} INFO, *p_info;

void CreateOutline(GtkWidget* notebook);
void GetInfo(p_info info);
void ShowInfo(GtkWidget *vbox, INFO info);



#endif // __OUTLINE_h__

