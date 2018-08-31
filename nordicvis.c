#include<stdio.h>
#include<stdlib.h>
#include<X11/Xlib.h>
#include<math.h>
#include<unistd.h>
#include <pthread.h>
#include <netcdf.h>
#include "colormaps_blue_red.h"
#include "colormaps_bright.h"

#define ArrayCount(a) (sizeof(a) / sizeof(a[0]))

typedef unsigned int  uint32;
typedef unsigned char uint8;

#define NX (1238)
#define NY (1046)
#define NT  (726)
float          SSH[NX*NY]    = {0.0};
unsigned long CSSH[NX*NY]    = {0};

float minvall(float *a, long int n ){
  float mv = a[0];
  for (long int i=1; i < n;++i){
    if (a[i] <= mv) mv = a[i];
  }
  return mv;
}

float maxvall(float *a, long int n){
  float mv = a[0];
  for (long int i=1; i < n;++i){
    if (a[i] >= mv) mv = a[i];
  }
  return mv;
}

void fillcolor(void){
  uint8 red = 0x0, green = 0x0, blue = 0x0, alpha = 0x0;
  uint32 *color = NULL;
  uint32 nt = ArrayCount(cmap_bright);
  color = (uint32 *)malloc(nt * sizeof(uint32));
  int ncount = 0;
  for (size_t i= 0; i < (nt-2); i += 3){
    color[ncount] = 0;
    red   = cmap_bright[i];
    green = cmap_bright[i+1];
    blue  = cmap_bright[i+2];
    color[ncount] = (((uint32)red << 16) | ((uint32)green << 8) | ((uint32)blue) | (uint32)alpha<<24);
    ncount++;
  }
  for (int j=0; j < NY;++j){
    for (int i=0; i < NX;++i){
      CSSH[j*NX + i] = color[(j*NX + i) %ncount];
    }
  }
}


XImage *CreateTrueColorImage(Display *display, Visual *visual, unsigned char *image, int width, int height)
{
  int i, j;
  unsigned char *image32=(unsigned char *)malloc(width*height*4);
  unsigned char *p=image32;
  #if 0
  for(i=0; i<width; i++)
    {
      for(j=0; j<height; j++)
        {
	  if((i<256)&&(j<256))
            {
	      *p++=rand()%256; // blue
	      *p++=rand()%256; // green
	      *p++=rand()%256; // red
            }
	  else
            {
	      *p++=i%256; // blue
	      *p++=j%256; // green
	      if(i<256)
		*p++=i%256; // red
	      else if(j<256)
		*p++=j%256; // red
	      else
		*p++=(256-j)%256; // red
            }
	  p++;
        }
    }
  #endif
  
  for(i=0; i<width; i++){
      for(j=0; j<height; j++){
	*p++=(unsigned char)(i) ; // blue
	*p++=(unsigned char)(i*j); // green
	*p++=(unsigned char)(j); // red
	p++;
      }
  }
  
  return XCreateImage(display, visual, 24, ZPixmap, 0, image32, width, height, 32, 0);
}

void processEvent(Display *display, Window window, XImage *ximage, int width, int height)
{
  static char *tir="This is red";
  static char *tig="This is green";
  static char *tib="This is blue";
  XEvent ev;
  XNextEvent(display, &ev);
  switch(ev.type)
    {
    case Expose:
      XPutImage(display, window, DefaultGC(display, 0), ximage, 0, 0, 0, 0, width, height);
      XSetForeground(display, DefaultGC(display, 0), 0x00ff0000); // red
      XDrawString(display, window, DefaultGC(display, 0), 32,     32,     tir, strlen(tir));
      XDrawString(display, window, DefaultGC(display, 0), 32+256, 32,     tir, strlen(tir));
      XDrawString(display, window, DefaultGC(display, 0), 32+256, 32+256, tir, strlen(tir));
      XDrawString(display, window, DefaultGC(display, 0), 32,     32+256, tir, strlen(tir));
      XSetForeground(display, DefaultGC(display, 0), 0x0000ff00); // green
      XDrawString(display, window, DefaultGC(display, 0), 32,     52,     tig, strlen(tig));
      XDrawString(display, window, DefaultGC(display, 0), 32+256, 52,     tig, strlen(tig));
      XDrawString(display, window, DefaultGC(display, 0), 32+256, 52+256, tig, strlen(tig));
      XDrawString(display, window, DefaultGC(display, 0), 32,     52+256, tig, strlen(tig));
      XSetForeground(display, DefaultGC(display, 0), 0x000000ff); // blue
      XDrawString(display, window, DefaultGC(display, 0), 32,     72,     tib, strlen(tib));
      XDrawString(display, window, DefaultGC(display, 0), 32+256, 72,     tib, strlen(tib));
      XDrawString(display, window, DefaultGC(display, 0), 32+256, 72+256, tib, strlen(tib));
      XDrawString(display, window, DefaultGC(display, 0), 32,     72+256, tib, strlen(tib));
      //XFlush(display);
      break;
    case ButtonPress:
      exit(0);
    }
}

struct xdata {
  Display *dsp;
  int screen_num;
  Window win;
  GC gc;                                  
};

void reverse(char *s, char *t){
  
  char *tmp = s;
  int len = 0;
  while (*tmp !='\0' ){
    tmp++;
    len++;
  }
  tmp--;
  while (len >0 ){
    *t = *tmp;
    tmp--;
    len--;
    t++;
  }
}

void intostr(int a, char *st){
  
  int index = 0;
  int r = -1 ;
  int q = 0;
  char cl[64] = {'\0'};
  do {
    r = a % 10;
    q = (a - r) / 10;
    *(cl+index) = (char)(r+'0');
    a = q;
    index++;
  }while(a >0);
  
  *(cl+index) = '\0';

  reverse(cl,st);
  
}

void *myThreadFun(void *vargp){
  
  struct xdata *xd = (struct xdata *)vargp; 
  float angle = 0, x1 = 0, y1 = 0;
  float mpi = 4.0*atan(1.0);
  for(;;){
    printf("thread 1 and angle is %f\n",angle);
    angle += 1.0;
    XClearWindow(xd->dsp, xd->win);
    char sangle[64] = {'\0'};
    intostr((int)angle, sangle);
    int length = 0;
    char *tmp = (char *)sangle; 
    while(*tmp != '\0' ){
      length++;
      tmp++;
    }
    x1= 50.0 * cos(-angle* (mpi / 180.0));
    y1= 50.0 * sin(-angle* (mpi / 180.0));
    XDrawLine(xd->dsp, xd->win, xd->gc, 150, 150, 150+2*(int)x1 , 150+2*(int)y1);
    XDrawString(xd->dsp, xd->win, xd->gc, 150+2*(int)x1 + 8 ,  150+2*(int)y1 + 8, sangle, length);
    if (angle > 360.0) angle = 0.0;
    XFlush(xd->dsp); // Tell the graphics server to show us the results now. 
    usleep(100000);  // Wait for 100000 micro seconds                    
  }
    XFlush(xd->dsp);
    return NULL;
}

int main(void){
 
  int ncid  = 0;
  int  issh = 0;
  char *filename  =  "abborre_ssh.nc";
  char *varname   =  "SSH_inst";
  size_t iassh[3] = {0,0,0};
  size_t start[3] = {0,0,0};
  size_t count[3] = {0,0,0};
  nc_open(filename,NC_NOWRITE,&ncid);
  nc_inq_varid(ncid, varname, &issh);
  int no_fill;
  float fill_valuep;
  nc_inq_var_fill(ncid, issh, &no_fill, &fill_valuep);
  printf("%d %e\n",no_fill, fill_valuep);
  Display *dsp;
  Window win;
  int screen_num;
  GC gc;                                /* handle of newly created GC.  */
  unsigned long valuemask = 0;          /* which values in 'values' to  */
  XGCValues values;
  Pixmap pixmap;
  dsp = XOpenDisplay((char *)0);
  screen_num = DefaultScreen(dsp);
  win    = XCreateSimpleWindow (dsp, DefaultRootWindow (dsp),0, 0, NX,NY,2,0x0,0x00ffff00);
  XSelectInput(dsp, win, ExposureMask | StructureNotifyMask | KeyPressMask);        // We want to get MapNotify events  
  XMapWindow(dsp, win);
  // "Map" the window (that is, make it appear on the screen)                                                                                                                     
  for(;;){XEvent e; XNextEvent(dsp,&e); if(e.type == MapNotify) break;} //Wait for the MapNotify event  
  XFlush(dsp);
  XColor color;
  int depth = DefaultDepth(dsp,screen_num); 
  pixmap = XCreatePixmap(dsp,win,NX,NY,depth);  
  color.pixel = 0x000000ff;
  gc = XCreateGC(dsp, win, 0, NULL);
  XSetForeground(dsp, gc, 0xffffffff);
  unsigned int line_width = 3;          /* line width for the GC.       */
  int line_style = LineSolid;           /* style for lines drawing and  */
  int cap_style = CapButt;              /* style of the line's edje and */
  int join_style = JoinBevel;           /*  joined lines.               */
  XSetLineAttributes(dsp, gc,line_width, line_style, cap_style, join_style);
  int ncount = 0;
  //pixmap = XCreatePixmapFromBitmapData(dsp,win, alien_bits,NX, NY,0xffffffff,0,depth);
  //XCopyArea ( dsp, pixmap, win,gc, 0, 0, NX, NY,0, 0);
  fillcolor();
  float minv = 0.0f, maxv = 0.0f;
  unsigned long pcolor = 0;
  float dis = 0.0f;
  
  for (int k=0; k < NT;++k){
    //XClearWindow(dsp,win);
    start[0] = k;
    start[1] = 0;
    start[2] = 0;
    count[0] = 1;
    count[1] = NY;
    count[2] = NX;
    nc_get_vara(ncid, issh,  start,count, SSH);
    for (int j=0; j < NY; ++j){
      for (int i=0; i < NX; ++i){
	if (SSH[j*NX+i] == 1.e+20f) SSH[j*NX+i] = 0.0;
      }
    }
    minv = minvall(SSH,NX*NY);
    maxv = maxvall(SSH,NX*NY);
    printf("maxval is %f\n",maxv);
    for (int j=0; j < NY;++j){
      for (int i=0; i < NX;++i){
	dis = (SSH[(NY -j -1)*NX+i] - minv) / (maxv - minv);
	pcolor = (unsigned long)((1.0 -dis) * CSSH[0] + dis *CSSH[NX*NY-1]);
	if (SSH[(NY -j -1)*NX+i] == 0.0) pcolor=0x0;
	XSetForeground(dsp, gc, pcolor);
	XDrawPoint(dsp,win,gc,i,j);
	XFlush(dsp);
      }
    }
  }
  nc_close(ncid);
  XFlush(dsp);
  for(;;);
  return 0;
}
  
