#include<stdio.h>
#include<stdlib.h>
#include<X11/Xlib.h>
#include<math.h>
#include<unistd.h>

#include<stdio.h>
#include<stdlib.h>

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

int main(void){
  
  int nx = 10, ny = 10;
  
  Display *dsp;
  Window win, win1;
  int screen_num;
  GC gc, gc1;                                /* handle of newly created GC.  */
  unsigned long valuemask = 0;          /* which values in 'values' to  */
  XGCValues values;           
  dsp = XOpenDisplay((char *)0);
  screen_num = DefaultScreen(dsp);
  win    = XCreateSimpleWindow (dsp, DefaultRootWindow (dsp),100, 100, 800,800, 2, 0x0,0x00ffff00);
  win1    = XCreateSimpleWindow (dsp, DefaultRootWindow (dsp),100, 100, 300,300, 2, 0x0,0x00ff00ff);
  XSelectInput(dsp, win, ExposureMask | StructureNotifyMask | KeyPressMask);        // We want to get MapNotify events  
  XMapWindow(dsp, win);
  XMapWindow(dsp, win1);
  // "Map" the window (that is, make it appear on the screen)                                                                                                                     
  for(;;){XEvent e; XNextEvent(dsp,&e); if(e.type == MapNotify) break;} //Wait for the MapNotify event  
  XFlush(dsp);
  XColor color;
  color.pixel = 0x000000ff;
  gc = XCreateGC(dsp, win, 0, NULL);
  gc1 = XCreateGC(dsp, win1, 0, NULL);
  XSetForeground(dsp, gc, 0x000000ff);
  XSetForeground(dsp, gc1, 0x000000ff);
  int xorig = -100, yorig = -100; 
  int i1 = xorig + 444, j1 =  yorig + 486;
  int i2 = xorig + 460, j2 = yorig + 516;
  int i3 = xorig + 497, j3 = yorig + 520;
  int i4 = xorig + 499, j4 = yorig + 471;
  //for (int ip=0; ip < 200; ip += 20){
  float angle = 0;
  float x1 = 0.0, y1 = 0.0;
  float mpi = 4.0*atan(1.0);
  int ip = 0;

  for(;;){
    angle += 1.0;
    XClearWindow(dsp, win);
    XClearWindow(dsp, win1);
    char sangle[64] = {'\0'};
    intostr((int)angle, sangle);
    int length = 0;
    char *tmp = (char *)sangle; 
    while(*tmp != '\0' ){
      length++;
      tmp++;
    }
    x1= 100.0 * cos(angle* (mpi / 180.0));
    y1= 100.0 * sin(angle* (mpi / 180.0));
    XDrawLine(dsp, win,  gc, i1 +ip, j1 + ip, i1 + 2*(int)x1 + ip, j1 + 2*(int)y1 + ip);
    XDrawString(dsp, win, gc, i1+ 2*(int)x1 + 5 , j1 + 2*(int)y1 + 5, sangle, length);
    x1= 50.0 * sin(angle* (mpi / 180.0));
    y1= 50.0 * cos(angle* (mpi / 180.0));
    XDrawLine(dsp, win1, gc1, 150, 150, 150+2*(int)x1 , 150+2*(int)y1);
    XDrawString(dsp, win1, gc1, 150+2*(int)x1 + 5 ,  150+2*(int)y1 + 5, sangle, length);
    //XDrawLine(dsp, win, gc, i1+ip, j1+ip, i4+ip, j4 +ip);
    //XDrawLine(dsp, win, gc, i2+ip, j2+ip, i3+ip, j3+ip);
    //XDrawLine(dsp, win, gc, i3+ip, j3+ip, i4+ip, j4+ip);
    ip += 0;
    if (angle > 360.0) angle = 0.0;
    //if (ip > 400) ip = -100;
    XFlush(dsp); // Tell the graphics server to show us the results now. 
    usleep(100000);  // Wait for 100000 micro seconds                    
  }
  XFlush(dsp);
  for(;;);
  return 0;
}
  





