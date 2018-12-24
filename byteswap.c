#include<stdio.h>
#include<stdlib.h>
#include<math.h>







struct V2 {
  float x, y;
};

float dot_product(struct V2  v1, struct V2  v2 ){
  
  float result = 0.0;
  result= (v1.x * v2.x) + (v1.y * v2.y);
  return result;
}


float absvalue(struct V2  v1 ){
  float result = 0.0;
  result= sqrt((v1.x * v1.x) + (v1.y * v1.y));
  return result;
}


struct help{
  char *op;
  char *desc;
};


struct help ahelp[] = {
  {"add","summation"},
  {"sub","subtractin"},
  {NULL,NULL}
};

void showhelp(struct help *hh){

  for (;hh->op;hh++){
    printf("operator %s and description %s \n",hh->op,hh->desc);
  }
}
      
int main(void){

  printf("product is %f        \n",dot_product((struct V2){1.0,2.0}, (struct V2){3.0,4.0}));
  printf("absolute value is %f \n",absvalue((struct V2){1.0,2.0}));

  short int kk = 0x0102;
  short int kr = (kk >> 8) | (kk << 8);
  printf("kk is %#x\n",kk);
  printf("kr is %#x\n",kr);
  kk = 0x0100;
  kk >>= 8;
  printf("kk is %#x\n",kk);

  showhelp(ahelp);

  unsigned int lua = 0xfdfcfbfa;
  unsigned int bua = ((lua << 24) & 0xff000000) | ((lua << 8) & 0x00ff0000) |  ((lua >> 8) & 0x0000ff00) | (lua >> 24 & 0x000000ff);
  printf("lua is %#x\n",lua);
  printf("bua is %#x\n",bua);
  
  
  return 0;
}
  


  
  
  



