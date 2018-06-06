#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>

typedef enum type{
  DBL, FLT, INT, CHAR,
}type;


typedef struct vector {
  void *ar;
  int size;
  int dim;
  type type;
}vector;


vector *zero(type type, int nx, ...){

  va_list va;

  va_start(va,nx);

  int numel = nx;
  int dim   = 1;
  int nd    = -1;
  while((nd=va_arg(va,int)) >0){
    numel *= nd;
    dim += 1;
  }

  va_end(va);

  printf("number of the elements %d\n",numel);
  printf("number of dimensions   %d\n",dim);

  vector *vec = (vector *)malloc(sizeof(vector*));

  switch (type){
  case INT:{
    vec->ar = (void *) malloc(numel *sizeof(int *));
  }break;
  case DBL:{ 
    vec->ar = (void *) malloc(numel *sizeof(double *));
  }break;
  case FLT:{ 
    vec->ar = (void *) malloc(numel *sizeof(float *));
  }break;
  case CHAR:{ 
    vec->ar = (void *) malloc(numel *sizeof(char *));
  }break;
  default:{
    vec->ar = NULL;
  }break;
  }
  vec->size = numel;
  vec->dim = dim;
  vec->type = type;
    
  return vec;

}

void fill(vector *vec, void *value){

  if (vec->ar != NULL){
  if (vec->type == INT) {
    for (int i=0; i < vec->size;++i){
      *((int *)vec->ar+i) = *((int *) value);
    }
  }
  if (vec->type == FLT) {
    for (int i=0; i < vec->size;++i){
      *((float *)vec->ar+i) = *((float *) value);
    }
  }
  }
}


void dump(vector *vec){
  if (vec->ar != NULL){
    if (vec->type == INT) {
    for (int i=0; i < vec->size;++i){
      printf("element %03d is %d\n",i,*((int*)vec->ar+i));
    }
  }
  if (vec->type == FLT) {
    for (int i=0; i < vec->size;++i){
      printf("element %03d is %f\n",i,*((float*)vec->ar+i));
    }
  }
  }
}
  
void del(vector **vec){
  if ((*vec)->ar != NULL){
    free((*vec)->ar);
    (*vec)->ar = NULL;
  }
  free(*vec);
  *vec = NULL;
}
  
int main(void){

  int   inivali = 10;
  vector *veci = zero(INT,2,3,4,0);
  fill(veci,&inivali);
  dump(veci);
  del(&veci);
  
  float inivalf = 0.250f;
  vector *vecf = zero(FLT,2,3,4,0);
  fill(vecf,&inivalf);
  dump(vecf);
  del(&vecf);
  
  return 0;
}
