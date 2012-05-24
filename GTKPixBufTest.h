void put_pixel(GdkPixbuf *pixbuf, int x, int y, guchar red, guchar green, guchar blue, guchar alpha)
{
  guchar *pixels, *p;
  int rowstride, numchannels;
  g_print("In putpixel, GdkPixbuf pointer is: %p\n", pixbuf);
  numchannels = gdk_pixbuf_get_n_channels(pixbuf);
  g_print("numchannels is: %i\n", numchannels);
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

struct RGBAPixel
{
  guint32 x, y, r, g, b, a;
};

void put_random_rgba_pixel(GdkPixbuf *pixbuf)
{
  GRand *grand;
  int index;
  guint32 x, y, r, g, b;
  grand = g_rand_new();
  x = g_rand_int_range(grand, 0, 640);
  y = g_rand_int_range(grand, 0, 480);
  r = g_rand_int_range(grand, 0, 255);
  g = g_rand_int_range(grand, 0, 255);
  b = g_rand_int_range(grand, 0, 255);
  //g_print("x: %i, y:%i, r:%i, g:%i, b:%i\n", (int)x, (int)y, (guchar)r, (guchar)g, (guchar)b);
  g_print("In put random rgba pixel, pixbuf is: %p\n", pixbuf);
  put_pixel(pixbuf, (int)x, (int)y, (guchar)r, (guchar)g, (guchar)b, 255);
  
  return;
}

gboolean time_handler(gpointer data)
{
  //struct widgets *w = (struct widgets *)data;
  struct widgets *d = (struct widgets *)data;
  g_print("In handler, widgets pointer is: %p\n", d);
  GdkPixbuf *p = d->pixbuf;
  GtkWidget *w = d->window;
  GtkWidget *i = d->image;
  g_print("In handler, GdkPixbuf pointer is: %p\n", p);
  //GdkPixbuf *d = (GdkPixbuf *)((struct widgets *)data->pixbuf);
  //struct widgets *w = (struct widgets *)data;
  //d = w->pixbuf;
  put_random_rgba_pixel(p);
  i = gtk_image_new_from_pixbuf(p);
  gtk_container_add(GTK_CONTAINER(w), i);
  return TRUE;
}
