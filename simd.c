#include<stdio.h>
#include<stdlib.h>
#include<xmmintrin.h>
#include<emmintrin.h>

int main(void){

  
  __m128 v0 = _mm_setr_ps(1.0f,2.0f,3.0f,4.0f);
  __m128 v1 = _mm_setr_ps(10.f,20.f,30.0f,40.0f);
  __m128 sum = _mm_add_ps(v0, v1);
  float vsum[4] = {0.0f};
  _mm_store_ps(vsum,sum);
  
  for (int i=0; i< 4; ++i) printf("%f\n",vsum[i]);

  v0 = _mm_setr_ps(10.0f,20.0f,30.0f,40.0f);
  v1 = _mm_setr_ps(10.f,20.f,30.0f,40.0f);
  sum = _mm_add_ps(v0, v1);
  _mm_store_ps(vsum,sum);
  
  for (int i=0; i< 4; ++i) printf("%f\n",vsum[i]);

  return 0;
}
