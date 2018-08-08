#include<stdio.h>
#include<stdlib.h>

typedef unsigned char uint8;
typedef unsigned int uint32; 

union data{
  uint8 ac[4];
  uint32 ii;
};

int main(void){
  uint8 red   = 0xaa;
  uint8 green = 0xbb;
  uint8 blue  = 0xcc;
  uint8 alpha = 0xdd;
  uint32 color  = 0x00000000;
#if 0
  uint32 tcolor = 0x00000000;
  tcolor |= (uint32)red;
  tcolor<<=24;
  color   = tcolor;
  tcolor  = 0x00000000;
  tcolor |= (uint32)green;
  tcolor<<=16;
  color  |= tcolor;
  tcolor  = 0x00000000;
  tcolor |= (uint32)blue;
  tcolor<<=8;
  color  |= tcolor;
  tcolor  = 0x00000000;
  tcolor |= (uint32)alpha;
  color  |= tcolor;
  printf("color is %08x\n",color);
  printf("color is %08x\n",(uint32)red);

  union data clr;
  clr.ac[0] = alpha;
  clr.ac[1] = blue;
  clr.ac[2] = green;
  clr.ac[3] = red;

  printf("color is %08x\n",clr.ii);
#endif
  color = 0x00000000;
  color = (((uint32)red << 24) | ((uint32)green << 16) | ((uint32)blue << 8) |  (uint32)alpha);
  printf("color is %08x\n",color);
  return 0;
}
  
  
  
