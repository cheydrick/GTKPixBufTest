#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include "GTKPixBufTest.h"

int main (int argc, char *argv[])
{
  struct widgets w;

  gtk_init(&argc, &argv);

  w.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  
  w.pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, 0, 8, 640, 480);

  w.image = gtk_image_new_from_pixbuf(w.pixbuf);
  
  gtk_container_add(GTK_CONTAINER(w.window), GTK_WIDGET(w.image));

  gtk_widget_show_all(w.window);

  g_signal_connect_swapped(G_OBJECT(w.window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  g_timeout_add(10, (GSourceFunc) time_handler, (gpointer) &w);

  gtk_main();

  return 0;
}
