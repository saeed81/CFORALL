#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "colormaps_jet.h"

enum CLMAP {JET, BRIGHT, RED_BLUE,};

#define ArrayCount(a) (sizeof(a) / sizeof(a[0]))

typedef unsigned int  uint32;
typedef unsigned char uint8;


struct Colort{
  float red, green, blue, alpha;
  int ncol;
};


float minval(float *a, int n ){
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

void colortoRGBA(uint32 color, uint8 *red, uint8 *green, uint8 *blue, uint8 *alpha){

  *red = 0x0;
  *green = 0x0;
  *blue = 0x0;
  *alpha = 0x0;

  *alpha = (color >> 24) & (0xff);
  *red   = (color >> 16) & (0xff);
  *green = (color >> 8) & (0xff);
  *blue  = (color) & (0xff);
  return;
}

struct Colort *getcolorfromcolormap(enum CLMAP CLM, int *ncol){
  
  uint32 nt = ArrayCount(cmap_jet);
  struct Colort *scolor = NULL;
  scolor = (struct Colort *)malloc(sizeof(struct Colort)*nt);
  if (scolor == NULL){
    *ncol = 0;
    return NULL;
  }
  int ncount = 0;
  if (CLM == JET){
    for (size_t i= 0; i < (nt-2); i += 3){
      scolor[ncount].red   = (float)(cmap_jet[i]) / 255.0;
      scolor[ncount].green = (float)(cmap_jet[i+1]) / 255.0;
      scolor[ncount].blue  = (float)(cmap_jet[i+2]) / 255.0;
      scolor[ncount].alpha  = 0.0;
      ncount++;
    }
  }
  *ncol = ncount;
  return scolor;
}

void getrgbpoint(float *value, struct Colort *scolor, int nc, uint8 *red, uint8 *green, uint8 *blue){
  if (scolor == NULL) return;
  if (nc == 0 ) return;
  float zred = 0.0, zgreen = 0.0, zblue = 0.0; 
  int idx1;                 
  int idx2;                
  float fractBetween = 0;  
  if(*value <= 0.0){  idx1 = idx2 = 0;}    
  else if(*value >= 1.0){idx1 = idx2 = nc-1; }   
  else{
    *value = *value * (nc);        
    idx1  = floor(*value);          
    idx2  = idx1+1;                
    fractBetween = *value - (float)(idx1); 
    if (idx1 >= (nc-1) ){ idx1 = (nc-1); idx2 = (nc-1);} 
    if (idx2 > (nc-1) ) idx2 = (nc-1);
  }
  zred   = (scolor[idx2].red   - scolor[idx1].red  )*fractBetween + scolor[idx1].red;
  zgreen = (scolor[idx2].green - scolor[idx1].green)*fractBetween + scolor[idx1].green;
  zblue  = (scolor[idx2].blue  - scolor[idx1].blue )*fractBetween + scolor[idx1].blue;
  *red   = (uint8 )(zred * 255.0);
  *green = (uint8 )(zgreen * 255.0);
  *blue  = (uint8 )(zblue * 255.0);
}

int main(void){

  int nc = 0;
  struct Colort *scolor = getcolorfromcolormap(JET,&nc);
  for (int i=0; i < nc; ++i){
    printf("n %03d red %f \t green %f \t blue %f \t alpha %f\n", i, scolor[i].red, scolor[i].green,scolor[i].blue,scolor[i].alpha);
  }
  printf("=================================================\n");

  float pi = 4.0 * atan(1.0);
  int NX = 101;
  float dx = (2.0 * pi) / (NX -1); 
  float *ysin = (float *)malloc(NX *sizeof(float));
  for (int i=0; i < NX;++i) ysin[i] = 2.0 * sin(i*dx);
  float min = minval(ysin,NX), max = maxval(ysin,NX);
  uint8 ured =0, ugreen = 0, ublue = 0;
  float value = 0.0f;
  for (int i=0; i < NX;++i){
    value = (ysin[i] -min) / (max -min);
    getrgbpoint(&value,scolor, nc, &ured, &ugreen, &ublue);
    printf("value %10.6f red %03u green %03u blue %03u\n",value, ured,ugreen,ublue);
  }
  #if 0
  float red = 0.0, green = 0.0, blue = 0.0; 
  int idx1;                 // |-- Our desired color will be between these two indexes in "color".
  int idx2;                // |
  float fractBetween = 0;  // Fraction between "idx1" and "idx2" where our value is.
  float value = 0.0;
  for (int i=0; i < NX;++i){
    value = (ysin[i] -min) / (max -min);
    if(value <= 0.0){  idx1 = idx2 = 0;}    // accounts for an input <=0
    else if(value >= 1.0){idx1 = idx2 = nc-1; }    // accounts for an input >=0
    else{
      value = value * (nc);        // Will multiply value by 3.
      idx1  = floor(value);                  // Our desired color will be after this index.
      idx2  = idx1+1;                        // ... and before this index (inclusive).
      fractBetween = value - (float)(idx1);    // Distance between the two indexes (0-1).
      if (idx1 >= (nc-1) ){ idx1 = (nc-1); idx2 = (nc-1);} 
      if (idx2 > (nc-1) ) idx2 = (nc-1);
    }
    red   = (scolor[idx2].red   - scolor[idx1].red  )*fractBetween + scolor[idx1].red;
    green = (scolor[idx2].green - scolor[idx1].green)*fractBetween + scolor[idx1].green;
    blue  = (scolor[idx2].blue  - scolor[idx1].blue )*fractBetween + scolor[idx1].blue;
    printf("idx1 %d idx2 %d fraction %f red %u green %u blue %u\n",idx1, idx2,fractBetween,(uint8 )(red * 255.0),(uint8 )(green * 255.0),(uint8 )(blue * 255.0));
  }
  #endif
  free(scolor);
  free(ysin);
  return 0;
}
