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

struct widgets
{
  GtkWidget *window, *image;
  GdkPixbuf *pixbuf;
};

void put_random_rgba_pixel(GdkPixbuf *pixbuf)
{
  GRand *grand;
  
  guint32 x, y, r, g, b;
  
  grand = g_rand_new();
  x = g_rand_int_range(grand, 0, 640);
  y = g_rand_int_range(grand, 0, 480);
  r = g_rand_int_range(grand, 0, 255);
  g = g_rand_int_range(grand, 0, 255);
  b = g_rand_int_range(grand, 0, 255);
  
  put_pixel(pixbuf, (int)x, (int)y, (guchar)r, (guchar)g, (guchar)b, 255);
  
  return;
}

gboolean time_handler(gpointer data)
{
  
  struct widgets *d = (struct widgets *)data;
  
  GdkPixbuf *p = d->pixbuf;
  GtkWidget *w = d->window;
  GtkWidget *i = d->image;
  
  put_random_rgba_pixel(p);
  gtk_image_set_from_pixbuf(i,p);
  
  return TRUE;
}
