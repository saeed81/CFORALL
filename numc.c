#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>

typedef enum type{
  DBL, FLT, INT, CHAR,
}type;


#pragma pack(push,1)
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
#pragma pack(pop)

vector *zero(type type, int nd, ...){

  if ((nd == 0) || (nd < 0)) return NULL;
  
  vector *vec = NULL;
  vec = (vector *)malloc(sizeof(vector));

  if (vec == NULL) return NULL;

  vec->ar =NULL;
  
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
  
  vec->nx   = nx;
  vec->ny   = ny;
  vec->nz   = nz ;
  vec->nt   = nt;
  vec->size = size;
  vec->dim  = dim;
  vec->type = type;
  vec->ar   = NULL;
  
  switch (type){
  case INT:{
    vec->ar = (void *) malloc(size *sizeof(int));
  }break;
  case DBL:{ 
    vec->ar = (void *) malloc(size *sizeof(double));
  }break;
  case FLT:{ 
    vec->ar = (void *) malloc(size *sizeof(float));
  }break;
  case CHAR:{ 
    vec->ar = (void *) malloc(size *sizeof(char));
  }break;
  default:{
    vec->ar = NULL;
  }break;
  }
    
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
    if (vec->type == DBL) {
      for (int i=0; i < vec->size;++i){
	*((double *)vec->ar+i) = *((double *) value);
      }
    }
    if (vec->type == CHAR) {
      for (int i=0; i < vec->size;++i){
	*((char *)vec->ar+i) = *((char *) value);
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
    if (vec->type == DBL) {
      for (int i=0; i < vec->size;++i){
	(void)printf("element %03d is %f\n",i,*((double*)vec->ar+i));
      }
    }
    if (vec->type == CHAR) {
      for (int i=0; i < vec->size;++i){
	(void)printf("element %03d is %c\n",i,*((char*)vec->ar+i));
      }
    }
    
  }
}


void showel(vector *vec){

  if (vec == NULL) return;

  (void)printf("number of   elements   %d\n",vec->size);
  (void)printf("number of   dimensions %d\n",vec->dim);
  (void)printf("number of x elements   %d\n",vec->nx);
  (void)printf("number of y elements   %d\n",vec->ny);
  (void)printf("number of z elements   %d\n",vec->nz);
  (void)printf("number of t elements   %d\n",vec->nt);

  return;
}


void del(vector **vec){

  if (*vec == NULL)return;
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
  vector *veci = zero(INT,2,3,0);
  fill(veci,&inivali);
  dump(veci);
  del(&veci);
    
  float inivalf = 0.250f;
  vector *vecf = zero(FLT,10,11,12,0);
  fill(vecf,&inivalf);
  dump(vecf);
  del(&vecf);

  char inivalc = 'A';
  vector *vecc = zero(CHAR,2,3,5,0);
  fill(vecc,&inivalc);
  dump(vecc);
  del(&vecc);
    
  return 0;
}
