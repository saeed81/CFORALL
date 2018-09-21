#include<stdio.h>
#include<stdlib.h>


#define Arraycount(a) (sizeof(a) / sizeof(a[0]))

void dumpcontainer(int **b){

  int **tmp = (int **)b;
  while (*tmp !=  NULL){
    printf("%d\n",**tmp);
    tmp++;
  }
}

void dumpcontainera(int **b,int n){
  int **tmp = (int **)b;
  for (int i=0; i < n;++i){
    printf("%d\n",**tmp);
    tmp++;
  }
}


int main(void){

  int a = 1;
  int b = 2;
  int c = 3;
  int d = 4;
  int *container[] ={&a,&b,&c,&d,NULL};
  int *containera[] ={&a,&b,&c,&d};
  dumpcontainer(container);
  dumpcontainera(containera,(int)Arraycount(containera));
  
  return 0;
}
 



