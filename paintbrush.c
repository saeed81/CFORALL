#include<stdio.h>
#include<stdlib.h>
#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<stdarg.h>

#define Arraycount(a) (sizeof(a) / sizeof(a[0]))
#define StringArraycount(a) (Arraycount(a) -1)
unsigned int stringlen(char *str){
  if (str == NULL) return 0;
  unsigned int len = 0;
  while(*str != '\0'){
    len++;
    str++;
  }
  return len;
}
void writetostring(char *buffer, int N, char *str,...){
  if (str == NULL) return;
  va_list vv;
  va_start(vv,str);
  char *tmp = buffer;
  int counter = 0;
  while(*str!='\0'){
    if (counter < N){
      *tmp = *str;
      tmp++;
    }
    counter++;
    str++;
  }
  while((str=va_arg(vv,char *)) != NULL){
    while(*str!='\0'){
      if (counter < N ){
        *tmp = *str;
        tmp++;
      }
      counter++;
      str++;
    }
  }
  va_end(vv);
  return;
}

int lenstr(char *str){
  int result = 0;
  if (str == NULL) return result;
  char *tmp = str;
  while(*tmp != '\0'){
    result++;
    tmp++;
  }
  return result;
}



void reverse(char *s, char *t, int sign, int npadzero){
  
  char *tmp = s;
  int len = 0;
  while (*tmp !='\0' ){
    tmp++;
    len++;
  }
  tmp--;

  if (sign < 0){
    *t = '-';
    t++;
  }

  while(npadzero--){
    *t = '0';
    t++;
  }
  
  while (len >0 ){
    *t = *tmp;
    tmp--;
    len--;
    t++;
  }
  *t = '\0';
}

void intostr(int a, char *st){
  int sign = 1;
  if (a < 0){
    sign = -1;
    a = (-a);
  }
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

  reverse(cl,st,sign,0);
  
}

void drawslider(Display *dsp, Window *win, GC *gc, int jm){
  XClearWindow(dsp,*win);
  XSetForeground(dsp,*gc,0x00ff0000);
  XDrawLine(dsp,*win,*gc,100,200,400,200);
  XSetForeground(dsp,*gc,0x000000ff);
  XDrawRectangle(dsp,*win,*gc,100+jm,190,20,20);
  XDrawRectangle(dsp,*win,*gc,100,50,75,75);
  XFlush(dsp);
}

void moveslider(Display *dsp, Window *win, GC *gc, int jm, int move){
  XClearWindow(dsp,*win);
  XSetForeground(dsp,*gc,0x00ff0000);
  XDrawLine(dsp,*win,*gc,100,200,400,200);
  XSetForeground(dsp,*gc,0x000000ff);
  XDrawRectangle(dsp,*win,*gc,100 + jm + move,190,20,20);
  XDrawRectangle(dsp,*win,*gc,100,50,75,75);
  XFlush(dsp);
}

int main(void){

  Display *dsp = XOpenDisplay((char *)NULL);
  int screen_num = DefaultScreen(dsp);
  int nx = 512;
  int ny = 512;
  Window win    = XCreateSimpleWindow (dsp, DefaultRootWindow (dsp),0, 0, nx,ny,0,0xffffffff,0xffffffff);
  XSelectInput(dsp, win, ExposureMask | StructureNotifyMask | KeyPressMask | ButtonPressMask | PointerMotionMask | EnterWindowMask | LeaveWindowMask);
  GC gc;
  gc=XCreateGC(dsp,win,0,NULL);
  XMapWindow(dsp, win);
  // "Map" the window (that is, make it appear on the screen)                                                                                                                                                      
  for(;;){XEvent e; XNextEvent(dsp,&e); if(e.type == MapNotify) break;} //Wait for the MapNotify event                                                                                                             
  XFlush(dsp);
  XFontStruct *fontinfo = XLoadQueryFont(dsp,"6x10"); 
  XSetFont(dsp,gc,fontinfo->fid); 
  XSetForeground(dsp,gc,0x00ff0000);
  
  XDrawLine(dsp,win,gc,100,200,400,200);

  XSetForeground(dsp,gc,0x000000ff);
  XDrawRectangle(dsp,win,gc,100,190,20,20);
  XDrawRectangle(dsp,win,gc,100,50,75,75);
  

  XFlush(dsp);

  XEvent ev;
  XEvent ev1;
  int jm = 0;

  while(1){
    XNextEvent(dsp,&ev);
    if (ev.type == ButtonPress){
      //XClearWindow(dsp,win);
      char cx[128] = {'\0'};
      char cy[128] = {'\0'};
      int x = ev.xbutton.x;
      int y = ev.xbutton.y;
      jm = x - 100;
      intostr(x, cx);
      intostr(y, cy);
      char cxo[128] = {'\0'};
      char cyo[128] = {'\0'};
      writetostring(cxo, 128, "x ",cx," ",NULL);
      writetostring(cyo, 128, "y ",cy," ",NULL);
      //XDrawString(dsp,win,gc,x,y,cxo,lenstr(cxo));
      //XDrawString(dsp,win,gc,x,y+20,cyo,lenstr(cyo));
      printf("button press \n");
    }
    if (ev.type == MotionNotify){
      //XClearWindow(dsp,win);
      char cx[128] = {'\0'};
      char cy[128] = {'\0'};
      int x = ev.xmotion.x;
      int y = ev.xmotion.y;
      jm = x - 100;
      intostr(x, cx);
      intostr(y, cy);
      char cxo[128] = {'\0'};
      char cyo[128] = {'\0'};
      writetostring(cxo, 128, "x ",cx," ",NULL);
      writetostring(cyo, 128, "y ",cy," ",NULL);
      //XDrawString(dsp,win,gc,x,y,cxo,lenstr(cxo));
      //XDrawString(dsp,win,gc,x,y+20,cyo,lenstr(cyo));
      printf("motion notify \n");
      /* if the 1st mouse button was held during this event, draw a pixel */
      /* at the mouse pointer location.                                   */
      if (ev.xmotion.state & Button1Mask) {
	/* draw a pixel at the mouse position. */
	/* if the 1st mouse button was held during this event, draw a pixel */
	/* at the mouse pointer location.                                   */
	XSetForeground(dsp,gc,0x00ff0000);
	XDrawPoint(dsp, win, gc, x+1, y);
	XDrawPoint(dsp, win, gc, x, y+1);
	XDrawPoint(dsp, win, gc, x, y);
	XDrawPoint(dsp, win, gc, x+1, y+1);
      }
    }
    
    if (ev.type == EnterNotify){
      printf("Mouse enter\n");
    }
    if (ev.type == LeaveNotify){
	printf("Mouse leave\n");
    }
    if (ev.type == KeyPress){
      break;
    }
  }

 

  XFree(gc);
  XClearWindow(dsp,win);
  XCloseDisplay(dsp);
  
  return 0;
}

