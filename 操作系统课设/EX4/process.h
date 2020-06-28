#ifndef __PROCESS_h__
#define __PROCESS_h__

#include "MainWindow.h"
#include "cpu.h"

#define P_COLUMN 7
#define MAX_P 300

void CreateProcess(GtkWidget* notebook);
void GetProcessInfo(GtkListStore *store);
gboolean PopMenu(GtkWidget *widget, GdkEventButton *event, gpointer data); 
gboolean KillProcess(gpointer data);
gboolean UpdateProcess (gpointer data);

#endif // __PROCESS_h__