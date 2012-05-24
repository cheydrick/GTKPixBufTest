#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include "GTKPixBufTest.h"

void put_pixel(GdkPixbuf *pixbuf, int x, int y, guchar red, guchar green, guchar blue, guchar alpha);

int main (int argc, char *argv[])
{
  struct widgets w;
  guint32 randnumx, randnumy, randnumr, randnumg, randnumb;
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

  /* random number structure for later */
  grand = g_rand_new_with_seed(12345);
  
  for(index = 0; index < 5096; index++)
    {
      randnumx = g_rand_int_range(grand, 0, 640);
      randnumy = g_rand_int_range(grand, 0, 480);
      randnumr = g_rand_int_range(grand, 0, 255);
      randnumg = g_rand_int_range(grand, 0, 255);
      randnumb = g_rand_int_range(grand, 0, 255);
      put_pixel(w.pixbuf, (int)randnumx, (int)randnumy, (guchar)randnumr, (guchar)randnumg, (guchar)randnumb, 255);
    }

  /* create GtkImage from this pixbuf */
  w.image = gtk_image_new_from_pixbuf(w.pixbuf);
  
  //image = gtk_image_new_from_file("test.png");
  /* since image is now a pointer to a gtk container, we'll put it in our main window */
  gtk_container_add(GTK_CONTAINER(w.window), w.image);
  gtk_widget_show_all(w.window);
  g_signal_connect_swapped(G_OBJECT(w.window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_main();

  return 0;
}
