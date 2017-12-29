#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>

union {

  struct {
    void (*add)(int *, int);
    void (*mul)(int *, int);
  };

}LIBI;

union {

  struct {
    void (*add)(float *, float);
    void (*mul)(float *, float);
  };

}LIBF;




void addc(int *a, int c){
  *a += c; 
}

void addf(float *a, float c){
  *a += c; 
}

void mulc(int *a, int c){
  *a *= c; 
}

void mulf(float *a, float c){
  *a *= c; 
}


int main(void){

  LIBI.add = addc;
  LIBF.add = addf;
  LIBI.mul = mulc;
  LIBF.mul = mulf;

  int ia = 10;
  int ib = 2;
  float fa = 20.0f;
  float fb = 2.0f;
  
  LIBI.add(&ia,ib);
  LIBF.add(&fa,fb);

  printf("%d\n",ia);
  printf("%f\n",fa);

  LIBI.mul(&ia,ib);
  LIBF.mul(&fa,fb);

  printf("%d\n",ia);
  printf("%f\n",fa);

  return 0;
}


