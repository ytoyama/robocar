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
get_gs_pixel(Display *disp, unsigned char k) {
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
main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "usage: %s <filename>\n", argv[0]);
    exit(1);
  }

  Display *disp = XOpenDisplay(NULL);
  Window win = XCreateSimpleWindow(disp, RootWindow(disp, 0), 200, 50, 400,
      300, 2, XWhitePixel(disp, 0), XWhitePixel(disp, 0));
  XMapWindow(disp, win);

  GC gc = XCreateGC(disp, win, 0, 0);
  
  FILE *fp = fopen(argv[1], "rb");
  if (fp) {
    for (int y = 0; y < 240; y++) {
      for (int x = 0; x < 640; x++) {
        XSetForeground(disp, gc, get_gs_pixel(disp, fgetc(fp)));
        XDrawPoint(disp, win, gc, x, y);
      }
    }
    fclose(fp);
  } else {
    fprintf(stderr, "ERROR: failed to open a file, '%s'\n", argv[1]);
    exit(1);
  }

  XFlush(disp);

  getchar();

  return 0;
}
