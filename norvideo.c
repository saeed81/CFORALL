#include<stdio.h>
#include<stdlib.h>
#include<X11/Xlib.h>
#include<math.h>
#include<unistd.h>
#include <pthread.h>
#include <netcdf.h>
#include "colormaps_jet.h" 
#include "colormaps_bright.h" 

#define ArrayCount(a) (sizeof(a) / sizeof(a[0]))
#define NX (619)
#define NY (523)
#define NT  (31)

typedef unsigned int  uint32;
typedef unsigned char uint8;

float  SSH[NX*NY]    = {0.0};
uint8  image32[NX*NY*4] = {0};

enum CLMAP {JET, BRIGHT, RED_BLUE,};

struct Colort{
  float red, green, blue, alpha;
  int ncol;
};

struct xdata {
  Display *dsp;
  int screen_num;
  Window win;
  GC gc;                                  
};



uint32 lenstring(char *str){
  if (str == NULL) return 0U;
  uint32 len = 0U;
  while (*str != '\0'){
    len++;
    str++;
  }
  return len;
}

float minval(float *a, int n ){
  float mv = a[0];
  for (int i=1; i < n;++i){
    if (a[i] <= mv) mv = a[i];
  }
  return mv;
}

float maxval(float *a, int n){
  float mv = a[0];
  for (int i=1; i < n;++i){
    if (a[i] >= mv) mv = a[i];
  }
  return mv;
}

void colortoRGBA(uint32 color, uint8 *red, uint8 *green, uint8 *blue, uint8 *alpha){

  *red = 0x0;
  *green = 0x0;
  *blue = 0x0;
  *alpha = 0x0;

  *alpha = (color >> 24) & (0xff);
  *red   = (color >> 16) & (0xff);
  *green = (color >> 8) & (0xff);
  *blue  = (color) & (0xff);
  return;
}

struct Colort *getcolorfromcolormap(enum CLMAP CLM, int *ncol){
  uint32 nt = 0;
  if (CLM == JET)    nt = ArrayCount(cmap_jet);
  if (CLM == BRIGHT) nt = ArrayCount(cmap_bright);
  
  struct Colort *scolor = NULL;
  scolor = (struct Colort *)malloc(sizeof(struct Colort)*nt);
  if (scolor == NULL){
    *ncol = 0;
    return NULL;
  }
  int ncount = 0;
  if (CLM == JET){
    for (size_t i= 0; i < (nt-2); i += 3){
      scolor[ncount].red   = (float)(cmap_jet[i]) / 255.0;
      scolor[ncount].green = (float)(cmap_jet[i+1]) / 255.0;
      scolor[ncount].blue  = (float)(cmap_jet[i+2]) / 255.0;
      scolor[ncount].alpha  = 0.0;
      ncount++;
    }
  }
  if (CLM == BRIGHT){
    for (size_t i= 0; i < (nt-2); i += 3){
      scolor[ncount].red   = (float)(cmap_bright[i]) / 255.0;
      scolor[ncount].green = (float)(cmap_bright[i+1]) / 255.0;
      scolor[ncount].blue  = (float)(cmap_bright[i+2]) / 255.0;
      scolor[ncount].alpha  = 0.0;
      ncount++;
    }
  }
  *ncol = ncount;
  return scolor;
}

void getrgbpoint(float *value, struct Colort *scolor, int nc, uint8 *red, uint8 *green, uint8 *blue){
  if (scolor == NULL) return;
  if (nc == 0 ) return;
  float zred = 0.0, zgreen = 0.0, zblue = 0.0; 
  int idx1;                 
  int idx2;                
  float fractBetween = 0;  
  if(*value <= 0.0){  idx1 = idx2 = 0;}    
  else if(*value >= 1.0){idx1 = idx2 = nc-1; }   
  else{
    *value = *value * (nc);        
    idx1  = floor(*value);          
    idx2  = idx1+1;                
    fractBetween = *value - (float)(idx1); 
    if (idx1 >= (nc-1) ){ idx1 = (nc-1); idx2 = (nc-1);} 
    if (idx2 > (nc-1) ) idx2 = (nc-1);
  }
  zred   = (scolor[idx2].red   - scolor[idx1].red  )*fractBetween + scolor[idx1].red;
  zgreen = (scolor[idx2].green - scolor[idx1].green)*fractBetween + scolor[idx1].green;
  zblue  = (scolor[idx2].blue  - scolor[idx1].blue )*fractBetween + scolor[idx1].blue;
  *red   = (uint8 )(zred * 255.0);
  *green = (uint8 )(zgreen * 255.0);
  *blue  = (uint8 )(zblue * 255.0);
}

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

void fillcolor(uint32 **pcolor, int *ncol){
  uint8 red = 0x0, green = 0x0, blue = 0x0, alpha = 0x0;
  uint32 nt = 0;
  *pcolor = (uint32 *)malloc(nt * sizeof(uint32));
  if (*pcolor == NULL) return;
  int ncount = 0;
  for (size_t i= 0; i < (nt-2); i += 3){
    *pcolor[ncount] = 0;
    red   = cmap_jet[i];
    green = cmap_jet[i+1];
    blue  = cmap_jet[i+2];
    *pcolor[ncount] = (((uint32)red << 16) | ((uint32)green << 8) | ((uint32)blue) | (uint32)alpha<<24);
    ncount++;
  }
  *ncol = ncount;
}

XImage *CreateTrueColorImage(Display *display, Visual *visual, int width, int height)
{
  int i, j;
  char *p=image32;
  
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
  char *filename  =  "sst_ssh.nc";
  char *varname   =  "SSH_inst";
  size_t iassh[3] = {0,0,0};
  size_t start[3] = {0,0,0};
  size_t count[3] = {0,0,0};
  nc_open(filename,NC_NOWRITE,&ncid);
  nc_inq_varid(ncid, varname, &issh);
  
  Display *dsp;
  Window win;
  int screen_num;
  GC gc;                                /* handle of newly created GC.  */
  dsp = XOpenDisplay((char *)0);
  screen_num = DefaultScreen(dsp);
  Visual *visual=DefaultVisual(dsp, 0);
  win    = XCreateSimpleWindow (dsp, DefaultRootWindow (dsp),0, 0, NX,NY,0,0x0,0x0);
  XSelectInput(dsp, win, ExposureMask | StructureNotifyMask | KeyPressMask);        // We want to get MapNotify events  
  XMapWindow(dsp, win);
  // "Map" the window (that is, make it appear on the screen)                                                                                                                     
  for(;;){XEvent e; XNextEvent(dsp,&e); if(e.type == MapNotify) break;} //Wait for the MapNotify event  
  XFlush(dsp);
  gc = XCreateGC(dsp, win, 0, NULL);
  float minv = 0.0f, maxv = 0.0f;
  uint8 ured = 0x0, ugreen = 0x0, ublue = 0x0, ualpha = 0x0;
  uint32 pcolor = 0x0;
  float value =0.0f;

  int ncolor = 0;
  struct Colort *scolor = getcolorfromcolormap(BRIGHT,&ncolor);
  
  if (scolor == NULL) return 1;
  minv = -0.2;
  maxv = 0.7;
  XImage *ximage = NULL;
  uint32 *pimage = NULL;

  char *title = "NEMO_NORDIC_NS02";
  XSetForeground(dsp, gc, 0x0); // red
  XDrawString(dsp, win, gc, 150, 150, title, lenstring(title));
  XFlush(dsp);

  
  for(;;){
    for (int k=0; k < NT;++k){
      //XClearWindow(dsp,win);
      pimage = (uint32 *)image32; 
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
      for (int j=0; j < NY; ++j){
	for (int i=0; i < NX; ++i){
	  value = (SSH[(NY -j -1)*NX+i] - minv) / (maxv - minv);
	  getrgbpoint(&value,scolor, ncolor, &ured, &ugreen, &ublue);
	  pcolor = 0x0;
	  pcolor = (((uint32)ured << 16) | ((uint32)ugreen << 8) | ((uint32)ublue) |  ((uint32)ualpha << 24));  
	  if (SSH[(NY -j -1)*NX+i] == 0.0) pcolor=0xffffffff;
	  *pimage++ = pcolor;
	}
      }
      ximage = XCreateImage(dsp, visual, 24, ZPixmap, 0, image32, NX, NY, 32, 0);
      XPutImage(dsp, win, gc, ximage, 0, 0, 0, 0, NX, NY);
      XFlush(dsp);
      XSetForeground(dsp, gc, 0x000000ff); // red
      XDrawString(dsp, win, gc, 150, 150, title, lenstring(title));
      XFlush(dsp);
      usleep(1000*10);
    }
  }
  nc_close(ncid);
  XFlush(dsp);

  return 0;
}
