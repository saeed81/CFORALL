#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<unistd.h>


int  main(void){

  Display *dsp;
  Window window;
  int screen_num;
  XEvent event;
  char *winame  = "moving";
  unsigned long valuemask;
  int x = 0, y = 0;
  dsp = XOpenDisplay("");
  if (dsp == NULL) fprintf(stderr,"unable to connect to server\n");
  screen_num = DefaultScreen(dsp);
  int width = 500;
  int height= 500;
  XColor color;
  color.red   = 0xFF;
  color.green = 0;
  color.blue  = 0;
  color.flags = DoGreen | DoRed | DoBlue;
  XColor black_col,white_col,red_col,green_col,blue_col,yellow_col,magenta_col,cyan_col;
  Colormap colormap;
  char black_bits[]   = "#000000";
  char white_bits[]   = "#FFFFFF";    // Mix red, green and blue to get white
  char red_bits[]     = "#FF0000";
  char green_bits[]   = "#00FF00";
  char blue_bits[]    = "#0000FF";
  char yellow_bits[]  = "#FFFF00";   // Mix red and green to get yellow
  char magenta_bits[] = "#FF00FF";  // A sort of purple color
  char cyan_bits[]    = "#00FFFF";     // A blue-green color
  // Define the colors we want to use
  colormap = DefaultColormap(dsp, screen_num);
  XParseColor(dsp, colormap, black_bits, &black_col); XAllocColor(dsp, colormap, &black_col);
  XParseColor(dsp, colormap, white_bits, &white_col); XAllocColor(dsp, colormap, &white_col);
  XParseColor(dsp, colormap, red_bits, &red_col); XAllocColor(dsp, colormap, &red_col);
  XParseColor(dsp, colormap, green_bits, &green_col);XAllocColor(dsp, colormap, &green_col);
  XParseColor(dsp, colormap, blue_bits, &blue_col);XAllocColor(dsp, colormap, &blue_col);
  XParseColor(dsp, colormap, yellow_bits, &yellow_col);XAllocColor(dsp, colormap, &yellow_col);
  XParseColor(dsp, colormap, magenta_bits, &magenta_col);XAllocColor(dsp, colormap, &magenta_col);
  XParseColor(dsp, colormap, cyan_bits, &cyan_col);XAllocColor(dsp, colormap, &cyan_col);
  XAllocColor(dsp, colormap,&color);
  window = XCreateSimpleWindow(dsp,RootWindow(dsp,screen_num),0,0,width,height,2,WhitePixel(dsp,screen_num),WhitePixel(dsp,screen_num));
  XSelectInput(dsp, window, ExposureMask | StructureNotifyMask | KeyPressMask);        // We want to get MapNotify events
  XMapWindow(dsp, window);         // "Map" the window (that is, make it appear on the screen)
  for(;;){XEvent e; XNextEvent(dsp,&e); if(e.type == MapNotify) break;} //Wait for the MapNotify event
  // which means that the window has appeared on the screen.
  //XMapWindow(dsp,win);
  //XFlush(dsp);
  //XSync(dsp, False); 
  GC gc;
  gc = XCreateGC(dsp, window, 0, NULL);
  unsigned int line_width = 2;          /* line width for the GC.       */
  int line_style = LineSolid;           /* style for lines drawing and  */
  int cap_style = CapButt;              /* style of the line's edje and */
  int join_style = JoinBevel;           /*  joined lines.               */
  XSetForeground(dsp, gc, green_col.pixel);
  //XSetForeground(dsp, gc, color.pixel);
  //XDrawLine(dsp, window, gc, 10, 70, 180, 30);      // Draw theline

  //XSetForeground(dsp, gc, green_col.pixel);  // Tell the GC we draw using the GREEN color

  //XDrawLine(dsp, win, gc, 10, 80, 180, 40);      // Draw the line

  //XSetForeground(dsp, gc, blue_col.pixel);  // Tell the GC we draw using the BLUE color

  //XDrawLine(dsp, win, gc, 10, 90, 180, 50);      // Draw the line
  //XSetForeground(dpy, gc, whiteColor);  // Tell the GC we draw using the WHITE color (Method 1)

  //XSetForeground(dsp, gc, white_col.pixel);  // Tell the GC we draw using the WHITE color (Method 2)
  //XDrawLine(dsp, win, gc, 10, 60, 180, 20);      // Draw the line
  /* define the style of lines that will be drawn using this GC. */
  XSetLineAttributes(dsp, gc,line_width, line_style, cap_style, join_style);
  XFillRectangle(dsp, window, gc, 20, 250, 50,50);
  KeySym keysym;
  char BUFFER[80] = {'\0'};
  int ncount = 0;
  int xr = 0;
  int xu = 0;
  int radius = 50;
  for (;;) {
    XEvent e;
    XNextEvent (dsp, & e);
    if (e.type == KeyPress) {
      XClearWindow(dsp, window);
      //XMapRaised(dsp, window);
      //XSetForeground(dsp, gc, red_col.pixel);
      //XSetBackground(dsp, gc, red_col.pixel);
      printf("we are pressing keyboard\n");
      ncount = XLookupString (&e.xkey,BUFFER,sizeof(BUFFER)-1, &keysym, NULL);
      BUFFER[ncount] = 0;  /* add terminal '\0' */
      //printf("%s %s  %d\n",XKeysymToString(keysym),BUFFER,(int)keysym);
      if (keysym == XK_Right){
	printf("inside of if %s %d\n",XKeysymToString(keysym),(int)keysym);
	xr += 20;
	//radius += 0; 
	//XSetForeground(dsp, gc, green_col.pixel);
	XFillRectangle(dsp, window, gc, 20+xr, 250+xu, radius, radius);
	//usleep(1);
      }
      if (keysym == XK_Left){
	printf("inside of if %s %d\n",XKeysymToString(keysym),(int)keysym);
	xr -= 20;
	//radius += 0; 
	//XSetForeground(dsp, gc, green_col.pixel);
	XFillRectangle(dsp, window, gc, 20+xr, 250+xu, radius, radius);
	//usleep(1);
      }
      if (keysym == XK_Up){
	printf("inside of if %s %d\n",XKeysymToString(keysym),(int)keysym);
	xu -= 20;
	//radius += 0; 
	//XSetForeground(dsp, gc, green_col.pixel);
	XFillRectangle(dsp, window, gc, 20+xr, 250+xu, radius, radius);
	//usleep(1);
      }
      if (keysym == XK_Down){
	printf("inside of if %s %d\n",XKeysymToString(keysym),(int)keysym);
	xu += 20;  
	//radius += 0; 
	//XSetForeground(dsp, gc, green_col.pixel);
	XFillRectangle(dsp, window, gc, 20+xr, 250+xu, radius, radius);
	//usleep(1);
      }
    }
  }


  //case KeyPress :
  //case KeyRelease :
  //ev->type = ev->xev.type;
  //ev->win  = ev->xev.xkey.window;
  //ev->mx   = ev->xev.xkey.x;
  // ev->my   = ev->xev.xkey.y;

  //ev->key_count = XLookupString (&ev->xev.xkey, ev->key_string,
  //				  sizeof(ev->key_string)-1, &ev->key_sym, NULL);
  //ev->key_string[ev->key_count] = 0;  /* add terminal '\0' */
  //sprintf (ev->key_name, "XK_%s", XKeysymToString(ev->key_sym));
  //break;

   



  
  XFlush(dsp);

  for(;;);
  
  XCloseDisplay(dsp);

  return 0;
}
