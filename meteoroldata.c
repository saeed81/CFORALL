#include<stdio.h>
#include<stdlib.h>
#define Arraycount(a) ((int)(sizeof(a) /sizeof(a[0])))


int Stringcmp(char *s1, char *s2){
  int result = 1;
  while (*s1 != '\0' && *s2 != '\0'){
    if (*s1 != *s2){
      result = 0;
      return result;
    }
    s1++;
    s2++;
  }
  if (*s1 != '\0' || *s2 != '\0' ) result = 0;
  return result;
}



struct Data {
  struct{
    int *data;
  }vara[24];
  char *name;
  int isflux;
};


int lowerbnd(int r, int pindex[], int np){
  int j = -1;
  for (int i=0; i < np;++i){
    if (r >= pindex[i]) {
      j = i;
    }
  }
  return j;
}
int upperbnd(int r, int pindex[], int np){
  int j = -1;
  for (int i=0; i < np;++i){
    if (r < pindex[i]) {
      j = i;
      break;
    }
  }
  if (r > pindex[np-1]) j = np -1;
  return j;
}


float lerp(int i1, int i2, float a1, float a2, int i3){
  if (i2 == i1) return a1;
  int w1 = i2 - i3;
  int w2 = i3 - i1;
  float result = w1 * a1 + w2 * a2;
  return (result / (w1 + w2));
}
	       
char *field[] = {"u","v","tp","lw","sw","sf","pr"};

int   pindex[] = {0,3,6,9,12,15,18,21};
int   rindex[] = {1,2,4,5,7,8,10,11,13,14,15,16,17,19,20,22,23};
float pvalue[] = {0.0,30.0,60.0,90.0,120.0,150.0,180.0,210.0};


void showinfo(struct Data *data){
  printf("=========================\n");
  printf("name is %s\n",data->name);
  printf("it is a flux (1) or not (0) %d\n",data->isflux);
  printf("=========================\n");
}


int main(void){
  
  int nt = 1721 * 961;
  
  struct Data met[Arraycount(field)] = {0};

  for (int j=0; j <Arraycount(field);++j){
    met[j].name = field[j];
    if (Stringcmp(field[j],"tp") ||  Stringcmp(field[j],"lw") || Stringcmp(field[j],"sw") || Stringcmp(field[j],"sf")){
      met[j].isflux = 1;
    }
    else {
      met[j].isflux = 0;
    }
    for (int i=0; i < 24;++i){
      met[j].vara[i].data = (int *)malloc(nt * sizeof(int));
      //for (int k=0; k <nt;++k){
	//met[j].vara[i].data[k] = (j * i *k);
      int il = lowerbnd(i, pindex, Arraycount(pindex));
      int iu = upperbnd(i, pindex, Arraycount(pindex));
      printf("%d \t lower bound is %d and upper bound is %d and value is %f\n",i,pindex[il],pindex[iu],lerp(pindex[il],pindex[iu],pvalue[il],pvalue[iu],i));
	//}
    }
  }
  for (int j=0; j <Arraycount(field);++j){
    showinfo(&met[j]);
  }
  
  for (int j=0; j <Arraycount(field);++j){
    for (int i=0; i < 24;++i){
      free(met[j].vara[i].data);
    }
  }

  return 0;
}
  


  
