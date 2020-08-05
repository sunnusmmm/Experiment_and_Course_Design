#ifndef __SUMMARY_h__
#define __SUMMARY_h__

#include "MainWindow.h"
#include "cpu.h"

typedef struct info
{
    char hostname[50];
    char version[50];
    char kernel[50];
    char cpu[50];
} INFO, *p_info;

void CreateSummary(GtkWidget* notebook);
void GetInfo(p_info info);
void ShowInfo(GtkWidget *vbox, INFO info);
void showLabel(GtkWidget *vbox, GtkWidget *label, char text[]);


#endif

