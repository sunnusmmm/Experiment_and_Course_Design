/***********************************************************************
 * @file MainWindow.h
     MAINWINDOW
 * @brief   header file
***********************************************************************/
#ifndef __MAINWINDOW_h__
#define __MAINWINDOW_h__

#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <dirent.h>
#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <cairo.h>
#include <time.h>

extern GtkWidget *window;
extern gboolean g_update;

#endif // __MAINWINDOW_h__

