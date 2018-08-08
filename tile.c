#include<stdio.h>
#include<stdlib.h>

#define width  (1024)
#define height (1024)
#define wd     (128)


int main(void){

  //unsigned char bc = '\0';
  //unsigned char gc = '\0';
  //unsigned char rc = '\0';
  //unsigned char ac = '\0';

#if 0
  union intochar{
    int ia;
    unsigned char ca[4];
  };
  
  union intochar inchar;

  inchar.ia = height;
 
  printf("%d\n",inchar.ca[0]);
  printf("%d\n",inchar.ca[1]);
  printf("%d\n",inchar.ca[2]);
  printf("%d\n",inchar.ca[3]);

  printf("=====================================\n");
  printf("%c\n",0 + '0'  );
  printf("%u\n",(unsigned char)'M'  );
  printf("%u\n",(unsigned char)height );
  printf("%u\n",(unsigned char)(height >> 8)  );
  printf("%u\n",(unsigned char)(height >> 16));
  printf("%u\n",(unsigned char)(height >> 24) );
  #endif
  int filesize = 54 + 3 * width * height + height * ((4- (width *3)%4)%4); // the last one is 4 byte padding  
  
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

  FILE *fout = NULL;

  fout = fopen("test.bmp","wb");
  unsigned char *imag = NULL;

  imag = (unsigned char *)malloc(width *height *3);

  unsigned char *pt = (unsigned char *)imag;

  for (int i=0; i < (width *height *3);++i){
    *pt = 0;
    pt++;
  }
  pt = (unsigned char *)imag;

  int numtile = width / wd;

  printf("numtile is %d\n",numtile);
  int ibeg = 0;
  int iend = 0;
  int jbeg = 0;
  int jend = 0;
  int ncount = 0;
  int ip = 0;
  int jp = 0;
  int gtile = 0;
  unsigned char bmppad[3] = {0,0,0}; 
  for (int j=0;j< height;++j){
    for (int i=0; i < width ;++i){
      ip = i;
      jp = j;
      ncount = 0;
      for (int jj=0; jj < numtile; ++jj){
	if ( jj % 2 == 0) ncount = 1;
	if ( jj % 2 == 1) ncount = 0;
	for (int ii=0; ii < numtile; ++ii){
	  ibeg = ii * wd;
	  iend = (ii + 1) * wd - 1;
	  jbeg = jj * wd;
	  jend = (jj + 1) * wd - 1;
	  ncount++;
	  if ( (ip >= ibeg) && (ip <= iend) && (jp >= jbeg) && (jp <= jend)){
	    if ( (ncount %2) == 0){
	      //printf("here_1 %d\t%d\n",ip,jp);
	      *pt = 0xff;
	      pt++;
	      *pt = 0xff ;
	      pt++;
	      *pt = 0xff;
	      pt++;
	    }
	    else{
	      //printf("here_2 %d\t%d\n",ip,jp);
	      *pt = 0x00;
	      pt++;
	      *pt = 0x00 ;
	      pt++;
	      *pt = 0x00;
	      pt++;
	    }
	  }
	}
      }
    }
  }
  fwrite(fileinfo,1,14,fout);
  fwrite(bmpinfo,1,40,fout);
  
  for (int i=0; i < height;++i){
    fwrite(imag+width*(height-i-1)*3,3,width,fout);
    fwrite(bmppad,1,(4-(width *3)%4)%4,fout);
  }

  fclose(fout);

  free(imag);
  
    
  return 0;
}
