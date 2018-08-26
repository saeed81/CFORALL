#include<stdio.h>
#include<stdlib.h>
#include<X11/Xlib.h>
#include<X11/Xatom.h>
#include<unistd.h>
#include<math.h>
#include <string.h>

#if 0
int width, height;          /* size of image */
int xoffset;                /* number of pixels offset in X direction */
int format;                 /* XYBitmap, XYPixmap, ZPixmap */
char *data;                 /* pointer to image data */
int byte_order;             /* data byte order, LSBFirst, MSBFirst */
int bitmap_unit;            /* quant. of scanline 8, 16, 32 */
int bitmap_bit_order;       /* LSBFirst, MSBFirst */
int bitmap_pad;             /* 8, 16, 32 either XY or ZPixmap */
int depth;                  /* depth of image */
int bytes_per_line;         /* accelarator to next line */
int bits_per_pixel;         /* bits per pixel (ZPixmap) */
unsigned long red_mask;     /* bits in z arrangment */
unsigned long green_mask;
unsigned long blue_mask;
XPointer obdata;            /* hoo */
#endif


Pixmap GetRootPixmap(Display* display, Window root)
{
  Pixmap currentRootPixmap;
  Atom act_type;
  int act_format;
  unsigned long nitems, bytes_after;
  unsigned char *data = NULL;
  Atom _XROOTPMAP_ID;

  _XROOTPMAP_ID = XInternAtom(display, "_XROOTPMAP_ID", False);

  if (XGetWindowProperty(display, root, _XROOTPMAP_ID, 0, 1, False,
			 XA_PIXMAP, &act_type, &act_format, &nitems, &bytes_after,
			 &data) == Success) {

    if (data) {
      printf("here in getroot\n");
      currentRootPixmap = *((Pixmap *) data);
      XFree(data);
    }
  }

  printf("here in getroot\n");
  
  return currentRootPixmap;
}




long int numberoflines(FILE *file){

  long int nl = 0L;

  char c = ' ';
  while ((c = fgetc(file)) != EOF){
    if (c == '\n') nl++;
  }

  rewind(file);

  return nl;

}


float minval(float *a, int n){
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


float minvall(float *a, long int n){
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

#define infiniteloop for(;;)
#define LEN(a) (sizeof(a) / sizeof(a[0]))
  
#pragma pack (push,1)
typedef struct BITMAPFILEHEADER 
{
  short    bfType;
  int    bfSize;
  short    bfReserved1;
  short    bfReserved2;
  int   bfOffBits;
}BITMAPFILEHEADER;
#pragma pack (pop)
#pragma pack (push,1)
typedef struct BITMAPINFOHEADER
{
  int  biSize;
  int   biWidth;
  int   biHeight;
  short   biPlanes;
  short   biBitCount;
  int  biCompression;
  int  biSizeImage;
  int   biXPelsPerMeter;
  int   biYPelsPerMeter;
  int  biClrUsed;
  int  biClrImportant;
}BITMAPINFOHEADER;
#pragma pack (pop)
#pragma pack (push,1)
void saveXImageToBitmap(XImage *pImage)
{
  BITMAPFILEHEADER bmpFileHeader;
  BITMAPINFOHEADER bmpInfoHeader;
  FILE *fp;
  static int cnt = 0;
  char filePath[255];
  memset(&bmpFileHeader, 0, sizeof(BITMAPFILEHEADER));
  memset(&bmpInfoHeader, 0, sizeof(BITMAPINFOHEADER));
  bmpFileHeader.bfType = 0x4D42;
  bmpFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
  bmpFileHeader.bfReserved1 = 0;
  bmpFileHeader.bfReserved2 = 0;
  int biBitCount =32;
  int dwBmpSize = ((pImage->width * biBitCount + 31) / 32) * 4 * pImage->height;
  printf("size of short:%d\r\n",(int)sizeof(short));
  printf("size of int:%d\r\n",(int)sizeof(int));
  printf("size of long:%d\r\n",(int)sizeof(long));
  printf("dwBmpSize:%d\r\n",(int)dwBmpSize);
  printf("BITMAPFILEHEADER:%d\r\n",(int)sizeof(BITMAPFILEHEADER));
  printf("BITMAPINFOHEADER:%d\r\n",(int)sizeof(BITMAPINFOHEADER));
  bmpFileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +  dwBmpSize;

  bmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
  bmpInfoHeader.biWidth = pImage->width;
  bmpInfoHeader.biHeight = pImage->height;
  bmpInfoHeader.biPlanes = 1;
  bmpInfoHeader.biBitCount = 32;     //biBitCount;
  bmpInfoHeader.biSizeImage = 0;
  bmpInfoHeader.biCompression = 0;
  bmpInfoHeader.biXPelsPerMeter = 0;
  bmpInfoHeader.biYPelsPerMeter = 0;
  bmpInfoHeader.biClrUsed = 0;
  bmpInfoHeader.biClrImportant = 0;

  sprintf(filePath, "bitmap%d.bmp", cnt++);
  fp = fopen(filePath,"wb");
  if(fp == NULL)return;
  
  fwrite(&bmpFileHeader, sizeof(bmpFileHeader), 1, fp);
  fwrite(&bmpInfoHeader, sizeof(bmpInfoHeader), 1, fp);
  fwrite(pImage->data,1,pImage->width *pImage->height*32, fp);
  fclose(fp);
}
#pragma pack(pop)

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
  //fwrite(image->data,1,image->width *image->height*4, fout);
  fclose(fout);

  return;
}
  
int main(void){

  float a[] = {-1.0,1.0,2.20,3.0,4.1,5.0,5.1,5.0,6.8};
  printf("%f\n",minval(a,LEN(a)));
  printf("%f\n",maxval(a,LEN(a)));
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
  printf("Window width %u; height %u\n",width, height);

  XColor xcolour;
  Colormap cmap;
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
   
  
  colormap = DefaultColormap(dsp, 0);
  XParseColor(dsp, colormap, black_bits, &black_col); XAllocColor(dsp, colormap, &black_col);
  XParseColor(dsp, colormap, white_bits, &white_col); XAllocColor(dsp, colormap, &white_col);
  XParseColor(dsp, colormap, red_bits, &red_col); XAllocColor(dsp, colormap, &red_col);
  XParseColor(dsp, colormap, green_bits, &green_col);XAllocColor(dsp, colormap, &green_col);
  XParseColor(dsp, colormap, blue_bits, &blue_col);XAllocColor(dsp, colormap, &blue_col);
  XParseColor(dsp, colormap, yellow_bits, &yellow_col);XAllocColor(dsp, colormap, &yellow_col);
  XParseColor(dsp, colormap, magenta_bits, &magenta_col);XAllocColor(dsp, colormap, &magenta_col);
  XParseColor(dsp, colormap, cyan_bits, &cyan_col);XAllocColor(dsp, colormap, &cyan_col);

  width = 500;
  height= 500;
  //win = XCreateSimpleWindow(dsp,RootWindow(dsp,screen_num),0,0,width,height,0,WhitePixel(dsp,screen_num),WhitePixel(dsp,screen_num));
  win = XCreateSimpleWindow(dsp,RootWindow(dsp,screen_num),0,0,width,height,0,WhitePixel(dsp,screen_num),0xffffffff);
  XSelectInput(dsp, win, StructureNotifyMask);        // We want to get MapNotify events
  XMapWindow(dsp, win);         // "Map" the window (that is, make it appear on the screen) 
                                                                                                                    
  for(;;){XEvent e; XNextEvent(dsp,&e); if(e.type == MapNotify) break;} //Wait for the MapNotify event                                                                                 
                          
  
  // which means that the window has appeared on the screen.                       

  //XMapWindow(dsp,win);

  XFlush(dsp);
  
  unsigned long valuemask = 0;          /* which values in 'values' to  */
                                        /* check when creating the GC.  */
  XGCValues values;                     /* initial values for the GC.   */
  
  //gc = XCreateGC(dsp, win, valuemask, &values);
  gc = XCreateGC(dsp, win, 0, NULL);

  //XSetForeground(dsp, gc, WhitePixel(dsp, screen_num));
  //XSetBackground(dsp, gc, BlackPixel(dsp, screen_num));
  
  //XSync(dsp, False);

  unsigned int line_width = 4;          /* line width for the GC.       */
  int line_style = LineSolid;           /* style for lines drawing and  */
  int cap_style = CapButt;              /* style of the line's edje and */
  int join_style = JoinBevel;           /*  joined lines.               */
  XSetForeground(dsp, gc, green_col.pixel);
  XSetLineAttributes(dsp, gc,line_width, line_style, cap_style, join_style);
  /* define the fill style for the GC. to be 'solid filling'. */
  //XSetFillStyle(dsp, gc, FillSolid);
  //XDrawLine(dsp, win, gc, 10, 10, 100, 100);      // Draw theline                                                                                                                      
  //XFlush(dsp);  
  //XSetForeground(dsp, gc, blue_col.pixel);
  //XDrawLine(dsp, win, gc, 200, 200, 300, 300);      // Draw theline                                                                                                                      
  //XFlush(dsp);
  #if 0
  for (int k=0; k< 200;++k){
    for (int j=220; j < 280;++j){
      for (int i=220; i < 280;++i){
	XSetForeground(dsp, gc, i + j + k );
	XDrawPoint(dsp, win, gc, i +k, j +k);
	XFlush(dsp);
      }
    }
  }
  #endif 

  int pi = 4.0 * atan(1.0);
  int nx = width;
  float dx = (2.0 * pi) / (nx -1);
  float *ap  = (float *)malloc(nx *sizeof(float));
  float *ap1 = (float *)malloc(nx *sizeof(float));
  for (int i=0; i < nx; i++){
    ap[i]  = 10.0*sin(2.0*pi *i *dx);
    ap1[i] = 10.0*cos(2.0*pi *i *dx);
  }
  float vmin = minval(ap,nx);
  float vmax = maxval(ap,nx);

  float vmin1 = minval(ap1,nx);
  float vmax1 = maxval(ap1,nx);

  int yb, yn, xb, xn;
  int yb1, yn1, xb1, xn1;
  int y1;
  

  
  for (long int i=0; i < nx;i++){
    int y = (int)(height - height*(ap[i] -vmin) / (vmax -vmin));
    int y1 = (int)(height - height*(ap1[i] -vmin1) / (vmax1 -vmin1));
    int x = (int)(width*((float)i) / (nx));
    if (i == 0){
      xb = x;
      xn = x;
      yb = y;
      yn = y;
    }
    else {
      xb = xn;
      yb = yn;
      xn = x;
      yn = y;
    }
    if (i == 0){
      xb1 = x;
      xn1 = x;
      yb1 = y1;
      yn1 = y1;
    }
    else {
      xb1 = xn1;
      yb1 = yn1;
      xn1 = x;
      yn1 = y1;
    }
    XSetForeground(dsp, gc, 0x00ff00ff);
    XDrawPoint(dsp, win, gc, xn, yn);
    XFlush(dsp);
    XSetForeground(dsp, gc, 0x0000ff00);
    XDrawPoint(dsp, win, gc, xn1, yn1);
    XFlush(dsp);
  }
  






  
  XWindowAttributes gwa;

  XGetWindowAttributes(dsp, win, &gwa);
  width = gwa.width;
  height = gwa.height;
 printf("width and height are %d \t %d\n",width,height);
 //XGetImage(dsp,win,0,0,width,height,XAllPlanes,ZPixmap);
 //Pixmap bg = GetRootPixmap(dsp, win);
 //width = 512;
 //height = 512;
 XImage *img = NULL;
 //Pixmap bg = XCreatePixmap (dsp,win,width,height,DefaultDepth(dsp,screen_num));
 Pixmap bg = XCreatePixmap (dsp,win,width,height,24);
 if (bg) {
   //XGCValues gcv;
   //gcv.subwindow_mode = IncludeInferiors;
   //XChangeGC (dsp, gc, GCSubwindowMode, &gcv);
   XCopyArea (dsp, win, bg, gc,0, 0,width, height,0, 0);

   //gcv.subwindow_mode = ClipByChildren;
   //XChangeGC (dsp, gc, GCSubwindowMode, &gcv);

   img = XGetImage (dsp,bg,0, 0,width, height,AllPlanes, ZPixmap);

   //XFreePixmap (dsp, bg);
 }
 printf("hereeeee\n");
 //XImage *img   = XGetImage(dsp, bg, 0, 0, width, height, ~0, ZPixmap);
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
  
 if (img != NULL)
   {
     //saveXImageToBitmap(img);
     writeimagetobitmap(img,"sinous.bmp");
     //save image here
     XFreePixmap (dsp, bg);
   }
 usleep(1000*1000*10);
 XCloseDisplay(dsp);
 free(ap);
 free(ap1);
  return 0;
}

