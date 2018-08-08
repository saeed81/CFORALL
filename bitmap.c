#include<stdio.h>
#include<stdlib.h>
#define M (1920)
#define N (1080)
#if glob
unsigned char image[M][N][4] = {{{0}}};
#endif
int main(void){
  #if stack
  unsigned char image[M][N][4] = {{{0}}};
#endif
  unsigned char *row  = (unsigned char *)image;
  unsigned int pitch = (N*4);  
  for (int i=0; i < M; ++i){
    unsigned int *pixel = (unsigned int *)row;
    for (int j=0; j < N; ++j){
      *pixel = 0x03020100;
      pixel++;
    }
    row += pitch;
  }
  long int ncount = 0L;
  for (int i=0; i < M; ++i){
    printf("%02d ",i);
    for (int j=0; j < N; ++j){
      printf("| %u %u %u %u |",image[i][j][0],image[i][j][1],image[i][j][2],image[i][j][3]);
      ncount++;
      if (ncount == 16){
	printf("\n");
	ncount = 0;
      }
    }
    printf("\n");
  }
  return 0;
}
