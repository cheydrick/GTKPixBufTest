#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include "GTKPixBufTest.h"

int main (int argc, char *argv[])
{
  struct widgets w;
  struct RGBAPixel p;
  GRand *grand;
  int index;

  gtk_init(&argc, &argv);

  w.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  
  /* initialize pixbuf to nothing */
  w.pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, 0, 8, 640, 480);
  if (w.pixbuf == NULL) g_print("Something Happened\n");
  /* some debug stuff */
  g_print("Bits per sample: %i\n", gdk_pixbuf_get_bits_per_sample(w.pixbuf));
  g_print("Colorspace: %i\n", gdk_pixbuf_get_colorspace(w.pixbuf));
  g_print("Rowstride: %i\n", gdk_pixbuf_get_rowstride(w.pixbuf));

  //sanity check to make sure we're drawing
  //random pixels prior to timer doing it for us
  //time_handler((gpointer) &w);
  

  w.image = gtk_image_new_from_pixbuf(w.pixbuf);
  
  //image = gtk_image_new_from_file("test.png");
  /* since image is now a pointer to a gtk container, we'll put it in our main window */
  gtk_container_add(GTK_CONTAINER(w.window), w.image);
  gtk_widget_show_all(w.window);
  g_signal_connect_swapped(G_OBJECT(w.window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  g_print("Widget main is: %p\n", &w);
  g_print("Pixbuf main is: %p\n", w.pixbuf);
  g_timeout_add(1000, (GSourceFunc) time_handler, (gpointer) &w);

  gtk_main();

  return 0;
}
