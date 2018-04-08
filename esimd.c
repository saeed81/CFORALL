#include<stdio.h>
#include<stdlib.h>
#include<xmmintrin.h>
#include<emmintrin.h>

#define N (256)

float a[N] = {0};
float b[N] = {0};
float c[N] = {0};


int main(void){


  __m128 v0  = _mm_setr_ps(0.0f,0.0f,0.0f,0.0f);
  __m128 v1  = _mm_setr_ps(0.0f,0.0f,0.0f,0.0f);
  __m128 sum = _mm_setr_ps(0.0f,0.0f,0.0f,0.0f);
  float vsum[4] = {0.0f};
  
  for (long int i=0; i < N; ++i){
    a[i] = (float)i;
    b[i] = (float)(i);
  }
  int jt  = 0;
  int inc = 4;
  while ( jt <= (N-4)) {
    v0 = _mm_setr_ps(a[jt],a[jt+1],a[jt+2],a[jt+3]);
    v1 = _mm_setr_ps(b[jt],b[jt+1],b[jt+2],b[jt+3]);
    sum = _mm_add_ps(v0, v1);
    _mm_store_ps(vsum,sum);
    for (int i=0; i< 4; ++i) c[jt+i] = vsum[i];
    jt += inc;
  } 
  for (int i=0; i< N; ++i) printf("%12.6f%12.6f%12.6f\n",a[i],b[i],c[i]);
 
  return 0;
}
