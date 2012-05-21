#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[])
{
  GtkWidget *window, *image;
  GdkPixbuf *pixbuf;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  
  /* initialize pixbuf to nothing */
  pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, 0, 8, 640, 480);
  if (pixbuf == NULL) printf("Something Happened\n");

  /* create GtkImage from this pixbuf */
  // image = gtk_image_new_from_pixbuf(pixbuf);
  image = gtk_image_new_from_file("test.png");
  /* since image is now a pointer to a gtk container, we'll put it in our main window */
  gtk_container_add(GTK_CONTAINER(window), image);

  gtk_widget_show_all(window);
  g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_main();

  return 0;
}
