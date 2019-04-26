#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>
#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<X11/keysym.h>

struct Vis{
  Display *dsp;
  Window win;
  Visual *visual;
  int screen_num;
  XGCValues gr_values;
  XFontStruct *fontinfo;
  GC gc;
  int w;
  int h;
  int depth;
};

struct rect{
  int x1, y1, w, h;
};

struct point{
  int x, y;
};


static int isinbox(int x, int y, struct rect *rect){
  int result = ( x >= rect->x1 && x < (rect->x1 + rect->w) && y >= rect->y1 && y < (rect->y1 + rect->h))? 1 : 0; 
  return result;
}

static struct Vis init_x(int w, int h){
  
  struct Vis result = {0};
  result.w = w;
  result.h = h;
  result.dsp        = XOpenDisplay((char *)0);
  result.screen_num = DefaultScreen(result.dsp);
  result.visual=DefaultVisual(result.dsp, 0);
  result.win    = XCreateSimpleWindow (result.dsp, DefaultRootWindow (result.dsp),0, 0, w,h,0,0xffffffff,0xffffffff);
  XSelectInput(result.dsp, result.win, ExposureMask | StructureNotifyMask | KeyPressMask | ButtonPressMask | PointerMotionMask | FocusChangeMask);        // We want to get MapNotify events  
  result.fontinfo       = XLoadQueryFont(result.dsp,"10x20");
  result.gr_values.font =   result.fontinfo->fid;
  result.gr_values.function =   GXcopy;
  result.gr_values.plane_mask = AllPlanes;
  result.gr_values.foreground = BlackPixel(result.dsp,result.screen_num);
  result.gr_values.background = WhitePixel(result.dsp,result.screen_num);
  result.gc=XCreateGC(result.dsp,result.win,GCFont | GCFunction | GCPlaneMask | GCForeground | GCBackground,&result.gr_values);
  result.depth  = DefaultDepth(result.dsp,result.screen_num);
  return result;
}  

static void map_window(struct Vis *Vis){
  
  XMapWindow(Vis->dsp, Vis->win);
  for(;;){XEvent e; XNextEvent(Vis->dsp,&e); if(e.type == MapNotify) break;} //Wait for the MapNotify event  
  XFlush(Vis->dsp);
}

static void drawonscreen_expose(struct Vis *vis, struct rect *rect){
 
  Pixmap pixmap = XCreatePixmap(vis->dsp, vis->win, vis->w, vis->h, vis->depth);
  XSetForeground(vis->dsp, vis->gc, 0xffffffff);
  XFillRectangle(vis->dsp, pixmap, vis->gc, 0, 0, vis->w, vis->h);
  XSetForeground(vis->dsp, vis->gc, 0x00ff00ff);
  XDrawRectangle(vis->dsp,pixmap,vis->gc,rect->x1,rect->y1,rect->w,rect->h);
  XCopyArea (vis->dsp, pixmap, vis->win, vis->gc,0, 0,vis->w, vis->h,0, 0);
  XFreePixmap(vis->dsp,pixmap);
}


static void drawonscreen_configure(struct Vis *vis){
  
  
  Pixmap pixmap = XCreatePixmap(vis->dsp, vis->win, vis->w, vis->h, vis->depth);
  XSetForeground(vis->dsp, vis->gc, 0xffffffff);
  XFillRectangle(vis->dsp, pixmap, vis->gc, 0, 0, vis->w, vis->h);
  XSetForeground(vis->dsp, vis->gc, 0x00ff00ff);
  XDrawRectangle(vis->dsp,pixmap,vis->gc,vis->w / 20,vis->h / 20,(int)(0.25*vis->w),(int)(0.25*vis->h));
  XCopyArea (vis->dsp, pixmap, vis->win, vis->gc,0, 0,vis->w, vis->h,0, 0);
  XFreePixmap(vis->dsp,pixmap);
}


static void drawonscreen_motion(struct Vis *vis, XEvent *e){
  
  Pixmap pixmap = XCreatePixmap(vis->dsp, vis->win, vis->w, vis->h, vis->depth);
  XSetForeground(vis->dsp, vis->gc, 0xffffffff);
  XFillRectangle(vis->dsp, pixmap, vis->gc, 0, 0, vis->w, vis->h);
  XSetForeground(vis->dsp, vis->gc, 0x00ff00ff);
  XDrawRectangle(vis->dsp,pixmap,vis->gc,vis->w / 20,vis->h / 20,(int)(0.25*vis->w),(int)(0.25*vis->h));
  XCopyArea (vis->dsp, pixmap, vis->win, vis->gc,0, 0,vis->w, vis->h,0, 0);
  XFreePixmap(vis->dsp,pixmap);
}

static void drawonscreen_motion_button(struct Vis *vis, XEvent *e,struct rect *rect, struct point *pb, struct point *pn){
  
  //int xb = e->xbutton.x,yb = e->xbutton.y;
  int offsetx = pn->x - pb->x;
  int offsety = pn->y - pb->y;
  //printf("offsetx offsety %d %d \n",offsetx,offsety);
  Pixmap pixmap = XCreatePixmap(vis->dsp, vis->win, vis->w, vis->h, vis->depth);
  XSetForeground(vis->dsp, vis->gc, 0xffffffff);
  XFillRectangle(vis->dsp, pixmap, vis->gc, 0, 0, vis->w, vis->h);
  XSetForeground(vis->dsp, vis->gc, 0x00ff00ff);
  XDrawRectangle(vis->dsp,pixmap,vis->gc,rect->x1 + offsetx,rect->y1 + offsety,rect->w,rect->h);
  rect->x1 += offsetx;
  rect->y1 += offsety;
  XCopyArea (vis->dsp, pixmap, vis->win, vis->gc,0, 0,vis->w, vis->h,0, 0);
  XFreePixmap(vis->dsp,pixmap);
}


static void reset(struct point *pb){
  pb->x = -1;
  pb->y = -1;
}


static void handle_event(struct Vis *vis){
  
  int done = 1;
  XEvent e;
  struct rect rect = {100, 100, 800, 200}; 
  struct point pb  = {-1,-1}; 
  struct point pn  = {-1,-1}; 
  
  for(;done;){
    XNextEvent (vis->dsp,&e);
    if (e.type == Expose){
      drawonscreen_expose(vis,&rect);
      done = 0;
    }
  }
  
  done = 1;
  
  for(;done;){
  
    XNextEvent (vis->dsp,&e);
    
    if (e.type == FocusIn){
      printf("focus in \n");
    }
    
    if (e.type == Expose){
      printf("expose\n");
    }
    
    if (e.type == ConfigureNotify) {
      XConfigureEvent xce = e.xconfigure;
      vis->w = (int)xce.width;
      vis->h = (int)xce.height;
      drawonscreen_configure(vis);
    }
    if (e.type == ButtonPress ){
      int xf = e.xbutton.x;
      int yf = e.xbutton.y;
    }
    if (e.type == MotionNotify){
      pn.x = e.xmotion.x;
      pn.y = e.xmotion.y;
      if (e.xmotion.state & Button1Mask){
	if (pb.x == -1 || pb.y == -1 ){
	  pb = pn;
	}
	if (isinbox(pn.x,pn.y,&rect)){
	  drawonscreen_motion_button(vis,&e,&rect,&pb,&pn);
	  pb = pn;
	}
	else{
	  reset(&pb);
	}
      }
      else{
	reset(&pb);
      }
    }
    if (e.type == KeyPress){
      char buffer[80] = {'\0'};
      KeySym keysym;
      XLookupString(&e.xkey,buffer,sizeof(buffer) -1,&keysym,NULL);
      if (keysym == XK_KP_Add){
	vis->h = (int)(1.20 * vis->h);
	vis->w = (int)(1.20 * vis->w);
	XResizeWindow(vis->dsp,vis->win,vis->w,vis->h);
      }
      if (keysym == XK_KP_Subtract){
	vis->h = (int)(0.80 * vis->h);
	vis->w = (int)(0.80 * vis->w);
	XResizeWindow(vis->dsp,vis->win,vis->w,vis->h);
      }
      if ((buffer[0] == 'q') || ( buffer[0]== 'Q') ){
        done = 0;
      }
    }
  }
}


int main(int argc, char *argv[]){
  
  if (argc == 1){

    int width  = 1600;
    int height = 900;
        
    struct Vis visu       = init_x(width,height);
    map_window(&visu);
    handle_event(&visu);
  }
  return 0;
}




