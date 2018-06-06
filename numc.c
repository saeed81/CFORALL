#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>

typedef enum type{
  DBL, FLT, INT, CHAR,
}type;


typedef struct vector {
  int  nx;
  int  ny;
  int  nz;
  int  nt;
  int  size;
  int  dim;
  type type;
  void *ar;
}vector;


vector *zero(type type, int nd, ...){

  if ((nd == 0) || (nd < 0)) return NULL;
  
  vector *vec = NULL;
  vec = (vector *)malloc(sizeof(vector));
  if (vec == NULL) return NULL;
  
  int nx   = 1;
  int ny   = 1;
  int nz   = 1;
  int nt   = 1;
  int size = 1;
  int dim  = 1;
    
  va_list va;
  va_start(va,nd);

  nx     = nd;
  size   = nd;
  dim    =  1;
  int ni = 1;
  
  while((nd=va_arg(va,int)) != 0){
    if (nd < 0) break;
    size *= nd;
    dim  += 1;
    ni++;
    if (ni == 2) ny = nd;
    if (ni == 3) nz = nd;
    if (ni == 4) nt = nd;
    if (ni == 4) break;
  }

  va_end(va);

  (void)printf("number of the elements %d\n",size);
  (void)printf("number of dimensions   %d\n",dim);
  (void)printf("number of x elements   %d\n",nx);
  (void)printf("number of y elements   %d\n",ny);
  (void)printf("number of z elements   %d\n",nz);
  (void)printf("number of t elements   %d\n",nt);
  (void)printf("number of ni           %d\n",ni);

  
  int numel = size;

  switch (type){
  case INT:{
    vec->ar = (void *) malloc( numel *sizeof(int));
  }break;
  case DBL:{ 
    vec->ar = (void *) malloc(numel *sizeof(double));
  }break;
  case FLT:{ 
    vec->ar = (void *) malloc(numel *sizeof(float));
  }break;
  case CHAR:{ 
    vec->ar = (void *) malloc(numel *sizeof(char));
  }break;
  default:{
    vec->ar = NULL;
  }break;
  }
  vec->nx   = nx;
  vec->ny   = ny;
  vec->nz   = nz ;
  vec->nt   = nt;
  vec->size = size;
  vec->dim  = dim;
  vec->type = type;
    
  return vec;

}

void fill(vector *vec, void *value){
  
  if (vec == NULL) return;
  if (vec->ar == NULL) return;
  if (value == NULL) return;
  
  
  if (vec == NULL) return;

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
  if (vec == NULL) return;
  if (vec->ar == NULL) return;
  
  if (vec->ar != NULL){
    if (vec->type == INT) {
    for (int i=0; i < vec->size;++i){
      (void)printf("element %03d is %d\n",i,*((int*)vec->ar+i));
    }
  }
  if (vec->type == FLT) {
    for (int i=0; i < vec->size;++i){
      (void)printf("element %03d is %f\n",i,*((float*)vec->ar+i));
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
  return;
    
}
  
int main(void){

  int   inivali = 10;
  vector *veci = zero(INT,200,300,0);
  fill(veci,&inivali);
  dump(veci);
  del(&veci);
    
  float inivalf = 0.250f;
  vector *vecf = zero(FLT,20,30,40,0);
  fill(vecf,&inivalf);
  dump(vecf);
  del(&vecf);
  
  return 0;
}
