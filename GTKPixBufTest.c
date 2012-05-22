#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>

void put_pixel(GdkPixbuf *pixbuf, int x, int y, guchar red, guchar green, guchar blue, guchar alpha);

int main (int argc, char *argv[])
{
  GtkWidget *window, *image;
  GdkPixbuf *pixbuf;
  guint32 randnumx, randnumy, randnumc;
  GRand *grand;
  int index;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  
  /* initialize pixbuf to nothing */
  pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, 0, 8, 640, 480);
  if (pixbuf == NULL) g_print("Something Happened\n");
  /* some debug stuff */
  g_print("Bits per sample: %i\n", gdk_pixbuf_get_bits_per_sample(pixbuf));
  g_print("Colorspace: %i\n", gdk_pixbuf_get_colorspace(pixbuf));
  g_print("Rowstride: %i\n", gdk_pixbuf_get_rowstride(pixbuf));

  /* random number structure for later */
  grand = g_rand_new_with_seed(1234);
  
  for(index = 0; index < 5096; index++)
    {
      randnumx = g_rand_int_range(grand, 0, 640);
      randnumy = g_rand_int_range(grand, 0, 480);
      randnumc = g_rand_int_range(grand, 0, 255);

      put_pixel(pixbuf, (int)randnumx, (int)randnumy, (guchar)randnumc, (guchar)randnumc, (guchar)randnumc, (guchar)randnumc);
    }

  /* create GtkImage from this pixbuf */
  image = gtk_image_new_from_pixbuf(pixbuf);
  
  //image = gtk_image_new_from_file("test.png");
  /* since image is now a pointer to a gtk container, we'll put it in our main window */
  gtk_container_add(GTK_CONTAINER(window), image);
  gtk_widget_show_all(window);
  g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_main();

  return 0;
}

void put_pixel(GdkPixbuf *pixbuf, int x, int y, guchar red, guchar green, guchar blue, guchar alpha)
{
  guchar *pixels, *p;
  int rowstride, numchannels;

  numchannels = gdk_pixbuf_get_n_channels(pixbuf);
  rowstride = gdk_pixbuf_get_rowstride(pixbuf);
  pixels = gdk_pixbuf_get_pixels(pixbuf);

  p = pixels + y * rowstride + x * numchannels;

  p[0] = red;
  p[1] = green;
  p[2] = blue;
  p[3] = alpha;
}
  
