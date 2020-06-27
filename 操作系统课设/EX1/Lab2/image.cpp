#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <gtk/gtk.h>

static int i = 1;

gint ChageImage(gpointer imageA);

int main(int argc, char *argv[])
{
	const GdkPixbuf *src_pixbuf;
    GdkPixbuf *dest_pixbuf;

    //初始化GTK
    GtkWidget *window;
    GtkWidget *vbox;  
    GtkWidget *text_label;
	GtkWidget *imageA;

    // 初始化整个GTK
    gtk_init(&argc, &argv);
    // 生成窗口
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    // 窗口属性
    gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "图片展示");
    gtk_container_set_border_width(GTK_CONTAINER(window), 20); //边界宽度
    // gtk_window_set_default_size(GTK_WINDOW(window), 500, 400);

    g_signal_connect_swapped(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit), NULL);
    
    // 创建盒装容器并添加
    vbox = gtk_vbox_new(FALSE, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_container_border_width(GTK_CONTAINER(vbox), 150);
    gtk_widget_show(vbox);

    // 标签
    text_label = gtk_label_new("图片交换");
    gtk_widget_show(text_label);
	//gtk_box_pack_start(GTK_BOX(vbox), text_label, FALSE, FALSE, 10);
	
	src_pixbuf = gdk_pixbuf_new_from_file("A.jpg", NULL); 
    dest_pixbuf = gdk_pixbuf_scale_simple(src_pixbuf, 450, 260, GDK_INTERP_HYPER);
    imageA = gtk_image_new_from_pixbuf(dest_pixbuf); 
	
	gtk_box_pack_start(GTK_BOX(vbox), imageA, FALSE, FALSE,10);
	
	//gtk_widget_show(text_label);
	gtk_widget_show(imageA);
    // 显示窗口
    gtk_widget_show(window);
    // 延时1000ms 循环调用函数
    g_timeout_add(1000, ChageImage, (gpointer)imageA);

    gtk_main();
}

gint ChageImage(gpointer imageA)
{
	const GdkPixbuf *src_pixbuf;
    GdkPixbuf *dest_pixbuf;
	if(i % 2 == 1){
		src_pixbuf = gdk_pixbuf_new_from_file("B.png", NULL); 
		dest_pixbuf = gdk_pixbuf_scale_simple(src_pixbuf, 450, 260, GDK_INTERP_HYPER);
		gtk_image_set_from_pixbuf( GTK_IMAGE(imageA), dest_pixbuf );
		i++;
	}else{
		src_pixbuf = gdk_pixbuf_new_from_file("A.jpg", NULL); 
		dest_pixbuf = gdk_pixbuf_scale_simple(src_pixbuf, 450, 260, GDK_INTERP_HYPER);
		gtk_image_set_from_pixbuf( GTK_IMAGE(imageA), dest_pixbuf );
		i++;
	}		
}