#include<stdio.h>
#include<stdlib.h>
#include<X11/Xlib.h>
#include<math.h>
#include<unistd.h>
#include <pthread.h>

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

  struct tm tbegin = {0,0,0,1,1,118};
  struct tm *info  = NULL;
  tbegin.tm_isdst = -1;
  time_t t1 = mktime(&tbegin);
  time_t tt = t1;
  time_t incr = 3600;
  int nx = 10, ny = 10;
  Display *dsp, *dsp1;
  Window win, win1;
  int screen_num, screen_num1;
  GC gc, gc1;                                /* handle of newly created GC.  */
  unsigned long valuemask = 0;          /* which values in 'values' to  */
  XGCValues values;           
  dsp = XOpenDisplay((char *)0);
  dsp1 = XOpenDisplay((char *)0);
  screen_num = DefaultScreen(dsp);
  screen_num1 = DefaultScreen(dsp1);
  win    = XCreateSimpleWindow (dsp, DefaultRootWindow (dsp),100, 100, 800,800, 2, 0x0,0x00ffff00);
  win1    = XCreateSimpleWindow (dsp1, DefaultRootWindow (dsp1),100, 100, 300,300, 2, 0x0,0x00ff00ff);
  XSelectInput(dsp, win, ExposureMask | StructureNotifyMask | KeyPressMask);        // We want to get MapNotify events  
  XMapWindow(dsp, win);
  XMapWindow(dsp1, win1);
  // "Map" the window (that is, make it appear on the screen)                                                                                                                     
  for(;;){XEvent e; XNextEvent(dsp,&e); if(e.type == MapNotify) break;} //Wait for the MapNotify event  
  XFlush(dsp);
  XFlush(dsp1);
  XColor color;
  color.pixel = 0x000000ff;
  gc = XCreateGC(dsp, win, 0, NULL);
  gc1 = XCreateGC(dsp1, win1, 0, NULL);
  XSetForeground(dsp, gc, 0x000000ff);
  XSetForeground(dsp1, gc1, 0x000000ff);
  
  unsigned int line_width = 3;          /* line width for the GC.       */
  int line_style = LineSolid;           /* style for lines drawing and  */
  int cap_style = CapButt;              /* style of the line's edje and */
  int join_style = JoinBevel;           /*  joined lines.               */
  XSetLineAttributes(dsp1, gc1,line_width, line_style, cap_style, join_style);
  XSetLineAttributes(dsp, gc,line_width, line_style, cap_style, join_style);
  struct xdata xdthread = {dsp1,screen_num1,win1,gc1};
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
  // A normal C function that is executed as a thread 
  // when its name is specified in pthread_create()
  pthread_t thread_id;
  printf("Before Thread\n");
  pthread_create(&thread_id, NULL, myThreadFun, (void *)&xdthread);
  printf("After Thread\n");
  for(;;){
    printf("thread 0 and angle is %f\n",angle);
    angle += 1.0;
    XClearWindow(dsp, win);
    char sangle[64] = {'\0'};
    intostr((int)angle, sangle);
    int length = 0;
    char *tmp = (char *)sangle; 
    while(*tmp != '\0' ){
      length++;
      tmp++;
    }
    info = localtime(&tt);
    int hour = info->tm_hour, min = info->tm_min, sec = info->tm_sec;
    x1= 100.0 * cos(angle* (mpi / 180.0));
    y1= 100.0 * sin(angle* (mpi / 180.0));
    XDrawLine(dsp, win,  gc, i1 +ip, j1 + ip, i1 + 2*(int)x1 + ip, j1 + 2*(int)y1 + ip);
    XDrawString(dsp, win, gc, i1+ 2*(int)x1 + 8 , j1 + 2*(int)y1 + 8, sangle, length);
    char stime[64] = {'\0'};
    intostr(sec, stime);
    length = 0;
    tmp = (char *)stime; 
    while(*tmp != '\0' ){
      length++;
      tmp++;
    }
    XDrawString(dsp, win, gc, i1+ 2*(int)x1 + 25 , j1 + 2*(int)y1 + 25, stime, length);
    char stime1[64] = {'\0'};
    intostr(min, stime1);
    length = 0;
    tmp = (char *)stime1; 
    while(*tmp != '\0' ){
      length++;
      tmp++;
    }
    XDrawString(dsp, win, gc, i1+ 2*(int)x1 + 45 , j1 + 2*(int)y1 + 45, stime1, length);
    char stime2[64] = {'\0'};
    intostr(hour, stime2);
    length = 0;
    tmp = (char *)stime2; 
    while(*tmp != '\0' ){
      length++;
      tmp++;
    }
    XDrawString(dsp, win, gc, i1+ 2*(int)x1 + 65 , j1 + 2*(int)y1 + 65, stime2, length);
    //XDrawLine(dsp, win, gc, i1+ip, j1+ip, i4+ip, j4 +ip);
    //XDrawLine(dsp, win, gc, i2+ip, j2+ip, i3+ip, j3+ip);
    //XDrawLine(dsp, win, gc, i3+ip, j3+ip, i4+ip, j4+ip);
    ip += 0;
    tt += 1;
    if (angle > 360.0) angle = 0.0;
    //if (ip > 400) ip = -100;
    XFlush(dsp); // Tell the graphics server to show us the results now. 
    usleep(100000);  // Wait for 100000 micro seconds                    
  }
  XFlush(dsp);
  for(;;);
  pthread_join(thread_id, NULL);
  printf("After Thread\n");
  

  return 0;
}
  





