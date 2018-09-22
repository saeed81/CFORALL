#include<stdio.h>
#include<stdlib.h>
#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<unistd.h>

Display                 *dpy;
Window                  root;
Visual                  *vi;
XSetWindowAttributes    swa;
Window                  win;
Pixmap                  pixmap;
int                     pixmap_width = 128, pixmap_height = 128;
int                     width = 600, height = 600; 
GC                      gc;
GC                      pix_gc;
XImage                  *xim;
int depth                 ;
void Redraw_background(void) {

  XPutImage(dpy, win,gc, xim, 0, 0, 0, 0,600, 600);
    return;
}

void Redraw(int nc) {
  XSetForeground(dpy, gc, 0x00c0c0c0);
  XFillRectangle(dpy, win, gc, nc, 0, 100, 100);
  return;
}



int lenstr(char *string){
  if (string == NULL) return 0;
  int len = 0;
  char *tmp = string;
  while(*tmp != '\0'){
    len++;
    tmp++;
  }
  return len;
}

int main(int argc, char *argv[]) {
  XEvent         xev;

  dpy = XOpenDisplay(NULL);

  if(dpy == NULL) {
    printf("\n\tcannot open display\n\n");
    return 1;
  }

  root = DefaultRootWindow(dpy);
  vi = DefaultVisual(dpy, 0);
  
  swa.event_mask = ExposureMask | KeyPressMask;
  swa.colormap   = XCreateColormap(dpy, root,vi, AllocNone);
  
  

  win = XCreateWindow(dpy, root, 0, 0, 600, 600, 0, CopyFromParent, InputOutput, vi, CWEventMask  | CWColormap, &swa);
  XMapWindow(dpy, win);
  XStoreName(dpy, win, "PIXMAP TO TEXTURE");

  /* CREATE A PIXMAP AND DRAW SOMETHING */
  depth = DefaultDepth(dpy, 0);
  pixmap_width = width;
  pixmap_height = height;
  pixmap = XCreatePixmap(dpy, root, pixmap_width, pixmap_height, depth);
  gc = DefaultGC(dpy, 0);
  pix_gc = XCreateGC (dpy, pixmap,0,NULL);
  
  XSetForeground(dpy, pix_gc, 0x00c0c0);
  XFillRectangle(dpy, pixmap, pix_gc, 0, 0, pixmap_width, pixmap_height);

  XSetForeground(dpy, pix_gc, 0x000000);
  XFillArc(dpy, pixmap, pix_gc, 15, 25, 50, 50, 0, 360*64);

  XSetForeground(dpy, pix_gc, 0x0000ff);
  XDrawString(dpy, pixmap, pix_gc, 10, 15, "PIXMAP TO TEXTURE", lenstr("PIXMAP TO TEXTURE"));

  XSetForeground(dpy, pix_gc, 0xff0000);
  XFillRectangle(dpy, pixmap, pix_gc, 75, 75, 45, 35);

  XFlush(dpy);
  xim = XGetImage(dpy, pixmap, 0, 0, pixmap_width, pixmap_height, AllPlanes, ZPixmap);
  XSetWindowBackgroundPixmap (dpy, win, pixmap);
  XFreePixmap(dpy,pixmap);
  XClearWindow (dpy, win);
  if(xim == NULL) {
    printf("\n\tximage could not be created.\n\n");
  }

  printf("here \n");
  int nc = 0;
  #if 0
  while(1) {
    XNextEvent(dpy, &xev);
    if(xev.type == Expose && xev.xexpose.count == 0) {
      //Redraw_background();
      XFlush(dpy);
      break;
    }
  }
  #endif
  while(1) {
    XNextEvent(dpy, &xev);
    printf("here \n");
    if(xev.type == KeyPress) {
      XClearWindow (dpy, win);
      nc += 10;
      printf("here \n");
      Redraw(nc);
      if (nc > 300) nc = 0;
    }
      //XDestroyImage(xim);
      //XFreeGC(dpy,gc);
      //XFreeGC(dpy,pix_gc);
      //XDestroyWindow(dpy, win);
      //XCloseDisplay(dpy);
    
    
  } 

  return 0;
}  
