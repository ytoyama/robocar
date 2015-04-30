#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

unsigned short
uchar2ushort(unsigned char c) {
  return (unsigned short)c * 0xFF;
}

unsigned long
get_gs_pixel(Display *disp, char k) {
  XColor color = {
    .red = uchar2ushort(k),
    .green = uchar2ushort(k),
    .blue = uchar2ushort(k),
  };

  if (XAllocColor(disp, DefaultColormap(disp, 0), &color) == False) {
    printf("XAllocColor() failed in get_gs_color()\n");
    exit(1);
  }

  return color.pixel;
}

int
main() {
  Display *disp;
  Window win;
  GC gc;
  //XSetWindowAttributes att;
  XPoint points[] = {
    200, 100,
    200, 200,
    250, 150,
    300, 100,
    300, 200
  };
  unsigned long black, white;

  disp = XOpenDisplay(NULL);

  black = XBlackPixel(disp, 0);
  white = XWhitePixel(disp, 0);

  win = XCreateSimpleWindow(disp, RootWindow(disp, 0), 200, 50, 400, 300, 2,
      white, white);

  //att.override_redirect = 1;

  //XChangeWindowAttributes(dips, win, CWOverrideRedirect, &att);
  XMapWindow(disp, win);
  XFlush(disp);

  gc = XCreateGC(disp, win, 0, 0);
  
  for (int y = 0; y < 100; y++)
    for (int x = 0; x < 100; x++) {
      XSetForeground(disp, gc, get_gs_pixel(disp, x + y));
      XDrawPoint(disp, win, gc, x, y);
    }

  XFlush(disp);

  getchar();

  return 0;
}
