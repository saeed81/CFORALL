#include<stdio.h>
#include<stdlib.h>
#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<X11/Xatom.h>
#include<unistd.h>
#include<math.h>
#include <string.h>

enum TYPE {ASCII_PPM,BINARY_PPM};

int save_ximage_pnm(XImage *img,char *pnmname,enum TYPE type) {
  int x,y;
  unsigned long pixel;
  if ( img  == NULL || pnmname == NULL || type<0) return 0;
  
  FILE *fout = fopen(pnmname,"w");

  printf("we are here \n");
  fprintf(fout,"P%d\n%d %d\n255\n",type,img->width, img->height);
  for (y=0; y<img->height; y++) {
    for (x=0; x<img->width; x++) {
      pixel=XGetPixel(img,x,y);
      if (type==ASCII_PPM) {
	fprintf(fout,"%ld %ld %ld\n",
		pixel>>16,(pixel&0x00ff00)>>8,pixel&0x0000ff);
      } else if (type==BINARY_PPM) {
	fprintf(fout,"%c%c%c",
		(char)(pixel>>16),
		(char)((pixel&0x00ff00)>>8),
		(char)(pixel&0x0000ff) );

      } else {
	fprintf(stderr,"PnM type %d not supported!",type);
	return(0);
      }
    }
  }

  fclose(fout);
  return(1);
}

void writeimagetobitmap_24(unsigned char *image, int width, int height, char *filename){
  if (image == NULL || filename == NULL) return;
  FILE *fout = NULL;
  fout = fopen(filename,"wb");
  if (fout == NULL) return;
  int filesize = 54 + 3 * width * height+ height * ((4- (width *3)%4)%4); // the last one is 4 byte padding

  unsigned char fileinfo[14] = {
    'B', 'M',//magic
    0,0,0,0, //size in bytes
    0,0,0,0,     //reserved
    40+14,0,0,0 // start of pixel array
  };

  fileinfo[0] = (unsigned char)('B');
  fileinfo[1] = (unsigned char)('M');
  fileinfo[2] = (unsigned char)(filesize);
  fileinfo[3] = (unsigned char)(filesize >> 8);
  fileinfo[4] = (unsigned char)(filesize >> 16);
  fileinfo[5] = (unsigned char)(filesize >> 24);
  fileinfo[10] = (unsigned char)(54);
  unsigned char bmpinfo[40] = {
    40,0,0,0,//header size
    0,0,0,0, //width
    0,0,0,0,//height
    1,0,     //color planes
    24,0,   // bits per pixel
    0,0,0,0,//compression
    0,0,0,0, // image size
    0,0,0,0, // horizontal resolution
    0,0,0,0, // vertical resolution
    0,0,0,0, // color in color tables
    0,0,0,0 // important color count
  };
  unsigned char bmppad[3] = {0,0,0}; 
  bmpinfo[0] = (unsigned char)(40);
  bmpinfo[4] = (unsigned char)(width);
  bmpinfo[5] = (unsigned char)(width>>8);
  bmpinfo[6] = (unsigned char)(width >> 16);
  bmpinfo[7] = (unsigned char)(width >> 24);
  bmpinfo[8] = (unsigned char)(height);
  bmpinfo[9] = (unsigned char)(height >> 8);
  bmpinfo[10] = (unsigned char)(height >>16);
  bmpinfo[11] = (unsigned char)(height >> 24);
  bmpinfo[12] = (unsigned char)(1);
  bmpinfo[14] = (unsigned char)(24);


  fwrite(fileinfo,1,14,fout);
  fwrite(bmpinfo,1,40,fout);

  for (int i=0; i < height;++i){
    fwrite(image+width*(height-i-1)*3,3,width,fout);
    fwrite(bmppad,1,(4-(width *3)%4)%4,fout);
  }

  fclose(fout);

  return;
}

void save_ximage_bitmap24(XImage *img,char *filename){

  unsigned char *image_out = (unsigned char *)malloc(img->height * img->width * 3);
  if (image_out == NULL) return;
  unsigned long pixel = 0x00000000;
  unsigned char *row = image_out;
  for (int i=0; i < img->height;i++){
    unsigned char *pt = (unsigned char *) row; 
    for (int j=0; j < img->width;j++){
      pixel=XGetPixel(img,j,i);
      //pixel = 0x00ff0000;
      //XPutPixel(img,j,i,pixel);
      *pt++ = (pixel & 0xff);
      *pt++ = ((pixel >> 8) & 0xff);
      *pt++ = ((pixel >> 16) & 0xff);
    }
    row += (img->width * 3);
  }
  writeimagetobitmap_24(image_out,img->width,img->height,filename);
  
  free(image_out);
}



void writeimagetobitmap(XImage *image, char *filename){
  if (image == NULL || filename == NULL) return;
  FILE *fout = NULL;
  fout = fopen(filename,"wb");
  if (fout == NULL) return;
  int filesize = 54 + 4 * image->width * image->height; //+ image->height * ((4- (image->width *3)%4)%4); // the last one is 4 byte padding

  unsigned char fileinfo[14] = {
    'B', 'M',//magic
    0,0,0,0, //size in bytes
    0,0,0,0,     //reserved
    40+14,0,0,0 // start of pixel array
  };

  fileinfo[0] = (unsigned char)('B');
  fileinfo[1] = (unsigned char)('M');
  fileinfo[2] = (unsigned char)(filesize);
  fileinfo[3] = (unsigned char)(filesize >> 8);
  fileinfo[4] = (unsigned char)(filesize >> 16);
  fileinfo[5] = (unsigned char)(filesize >> 24);
  fileinfo[10] = (unsigned char)(54);
  unsigned char bmpinfo[40] = {
    40,0,0,0,//header size
    0,0,0,0, //width
    0,0,0,0,//height
    1,0,     //color planes
    32,0,   // bits per pixel
    0,0,0,0,//compression
    0,0,0,0, // image size
    0,0,0,0, // horizontal resolution
    0,0,0,0, // vertical resolution
    0,0,0,0, // color in color tables
    0,0,0,0 // important color count
  };
  unsigned char bmppad[3] = {0,0,0}; 
  bmpinfo[0] = (unsigned char)(40);
  bmpinfo[4] = (unsigned char)(image->width);
  bmpinfo[5] = (unsigned char)(image->width>>8);
  bmpinfo[6] = (unsigned char)(image->width >> 16);
  bmpinfo[7] = (unsigned char)(image->width >> 24);
  bmpinfo[8] = (unsigned char)(image->height);
  bmpinfo[9] = (unsigned char)(image->height >> 8);
  bmpinfo[10] = (unsigned char)(image->height >>16);
  bmpinfo[11] = (unsigned char)(image->height >> 24);
  bmpinfo[12] = (unsigned char)(1);
  bmpinfo[14] = (unsigned char)(32);


  fwrite(fileinfo,1,14,fout);
  fwrite(bmpinfo,1,40,fout);

  for (int i=0; i < image->height;++i){
    fwrite(image->data+image->width*(image->height-i-1)*4,4,image->width,fout);
    //fwrite(image->data+image->width*(image->height-i-1)*3,3,image->width,fout);
  //  fwrite(bmppad,1,(4-(image->width *3)%4)%4,fout);
  }
  fclose(fout);

  return;
}
  
int main(void){

  Display *dsp = NULL;
  int screen_num;
  Window win;
  unsigned int display_width;
  unsigned int display_height;
  unsigned int width;
  unsigned int height;
  GC gc;  // we need this one for drawing
  dsp = XOpenDisplay((char *)0);
  if (dsp == NULL){
    fprintf(stderr,"Cannot open the display\n");
  }
  screen_num     = DefaultScreen(dsp);
  display_width  = DisplayWidth(dsp,screen_num);
  display_height = DisplayWidth(dsp,screen_num);
  width  = (display_width / 3);
  height = (display_height / 3);
  //printf("Window width %u; height %u\n",width, height);

  width = 512;
  height= 512;
  //win = XCreateSimpleWindow(dsp,RootWindow(dsp,screen_num),0,0,width,height,0,WhitePixel(dsp,screen_num),WhitePixel(dsp,screen_num));
  win = XCreateSimpleWindow(dsp,RootWindow(dsp,screen_num),0,0,width,height,0,BlackPixel(dsp,screen_num),0xffffffff);
  XSelectInput(dsp, win, ExposureMask | StructureNotifyMask);        // We want to get MapNotify events
  XMapWindow(dsp, win);         // "Map" the window (that is, make it appear on the screen) 
                                                                                                                    
  for(;;){XEvent e; XNextEvent(dsp,&e); if(e.type == MapNotify) break;} //Wait for the MapNotify event                                                                                 
  
  XFlush(dsp);
  
  unsigned long valuemask = 0;          /* which values in 'values' to  */
                                        /* check when creating the GC.  */
  XGCValues values;                     /* initial values for the GC.   */
  
  //gc = XCreateGC(dsp, win, valuemask, &values);
  gc = XCreateGC(dsp, win, 0, NULL);

        
  XEvent xev;
  while(1){
    XNextEvent(dsp,&xev);
    switch (xev.type){
    case Expose:{ 
      XSetForeground(dsp, gc, 0x00ff0000);
      XDrawLine(dsp,win,gc,100,100,150,100);
      XDrawLine(dsp,win,gc,100,100,100,150);
      XDrawLine(dsp,win,gc,100,150,150,150);
      XDrawLine(dsp,win,gc,150,150,150,100);
      XSetForeground(dsp, gc, 0x000000ff);
      XDrawString(dsp, win, gc, 105, 125, "Sinous", 6);
      XSetForeground(dsp, gc, 0x000000ff);
    }break;
    }
    usleep(1000*1000);
    break;
  }
  XWindowAttributes gwa;

  //XGetWindowAttributes(dsp, win, &gwa);
  //width = gwa.width;
  //height = gwa.height;
  //XGetImage(dsp,win,0,0,width,height,XAllPlanes,ZPixmap);
 //Pixmap bg = GetRootPixmap(dsp, win);
 //width = 512;
 //height = 512;
 XImage *img = NULL;
 //Pixmap bg = XCreatePixmap (dsp,win,width,height,DefaultDepth(dsp,screen_num));
 Pixmap bg = XCreatePixmap (dsp,win,width,height,DefaultDepth(dsp,screen_num));
 if (bg) {
   XGCValues gcv;
   gcv.subwindow_mode = IncludeInferiors;
   XChangeGC (dsp, gc, GCSubwindowMode, &gcv);
   XCopyArea (dsp, win, bg, gc,0, 0,width, height,0, 0);
   gcv.subwindow_mode = ClipByChildren;
   XChangeGC (dsp, gc, GCSubwindowMode, &gcv);
   img = XGetImage (dsp,bg,0, 0,width, height,AllPlanes, ZPixmap);
   //XFreePixmap (dsp, bg);
 }
 //XImage *img   = XGetImage(dsp, bg, 0, 0, width, height, ~0, ZPixmap);
 if (1){
 printf("information on Ximage \n");
 printf("width %d\n",img->width);
 printf("height %d\n",img->height);
 printf("bitmap unit %d\n",img->bitmap_unit);
 printf("bitmap bit oredr %d\n",img->bitmap_bit_order);
 printf("bitmap byte oredr %d\n",img->byte_order);
 printf("bitmap_pad  %d\n",img->bitmap_pad);             /* 8, 16, 32 either XY or ZPixmap */
 printf("depth %d\n",img->depth);                  /* depth of image */
 printf("bytes_per_line %d\n",img->bytes_per_line);         /* accelarator to next line */
 printf("bytes_per_pixel %d\n",img->bits_per_pixel);         /* bits per pixel (ZPixmap) */
 }

 save_ximage_bitmap24(img,"sinous_24.bmp");
 XDestroyImage(img);
 XFreePixmap (dsp, bg);
 //usleep(1000*10);
 XFreeGC (dsp, gc);
 XDestroyWindow(dsp,win);
 XCloseDisplay(dsp);
 
 return 0;
}

