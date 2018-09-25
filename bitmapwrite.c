#include<stdio.h>
#include<stdlib.h>
#include<math.h>

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
  
int main(void){

  int width  = 400;
  int height = 400;
  char *filename = "test.bmp";
  unsigned char *image_out = (unsigned char *)malloc(height * width * 3);
  if (image_out == NULL) return 1;
  unsigned long pixel = 0x00000000;
  unsigned char *row = image_out;
  for (int i=0; i < height;i++){
    unsigned char *pt = (unsigned char *) row; 
    for (int j=0; j < width;j++){
      if (i >= 0   && i< 100) pixel=0x00ff0000;
      if (i >= 100 && i< 200) pixel=0x0000ff00;
      if (i >= 200 && i< 300) pixel=0x000000ff;
      if (i >= 300 && i< 400) pixel=0x0000ffff;
      *pt++ = (pixel & 0xff);
      *pt++ = ((pixel >> 8) & 0xff);
      *pt++ = ((pixel >> 16) & 0xff);
    }
    row += (width * 3);
  }
  writeimagetobitmap_24(image_out,width,height,filename);
  free(image_out);
  return 0;
}
