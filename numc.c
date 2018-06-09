#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>

typedef enum type{
  DBL, FLT, INT, CHAR
}type;

//#pragma pack(push,1)
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
//#pragma pack(pop)

vector *zeros(type type, int nd, ...){

  if ((nd == 0) || (nd < 0) || (nd > 4)) return NULL;
  
  vector *vec = NULL;
  vec = (vector *)malloc(sizeof(vector));

  if (vec == NULL) return NULL;

  int nx   = 1;
  int ny   = 1;
  int nz   = 1;
  int nt   = 1;
  int size = 1;
  int dim  = nd;
    
  va_list va;
  va_start(va,nd);

  int ni =  0;
  int ncount = 0;
  
  while( nd--){
    ni=va_arg(va,int);
    if (ni <= 0 ) break;
    size *= ni;
    if (ncount == 0) nx = ni;
    if (ncount == 1) ny = ni;
    if (ncount == 2) nz = ni;
    if (ncount == 3) nt = ni;
    ncount++;
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
  
  if (vec    == NULL) return;
  if (vec->ar== NULL) return;
  if (value  == NULL) return;
  if (vec    == NULL) return;

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
  if (vec     == NULL) return;
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



void *get(vector *v, int i, int j, int k){

  if ((i > (v->nx -1)) || (j > (v->ny -1)) || (k > (v->nz -1))) return (void *)0;
  if (v->type == FLT)  return &(((float *)v->ar)[k+v->nz*j+i*(v->ny*v->nz)]);
  if (v->type == INT)  return &(((int *)v->ar)[k+v->nz*j+i*(v->ny*v->nz)]);
  if (v->type == DBL)  return &(((double *)v->ar)[k+v->nz*j+i*(v->ny*v->nz)]);
  if (v->type == CHAR) return &(((char *)v->ar)[k+v->nz*j+i*(v->ny*v->nz)]);

  return (void *)0;
}



void showinfomembers(vector *vec){

  if (vec == NULL) return;

  (void)printf("number of   elements   %d\n",vec->size);
  (void)printf("number of   dimensions %d\n",vec->dim );
  (void)printf("number of x elements   %d\n",vec->nx  );
  (void)printf("number of y elements   %d\n",vec->ny  );
  (void)printf("number of z elements   %d\n",vec->nz  );
  (void)printf("number of t elements   %d\n",vec->nt  );

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
  vector *veci = zeros(INT,2,3,5);
  showinfomembers(veci);
  fill(veci,&inivali);
  dump(veci);
  del(&veci);
    
  float inivalf = 0.250f;
  vector *vecf = zeros(FLT,3,2,3,4);
  showinfomembers(vecf);
  fill(vecf,&inivalf);
  float *valf = get(vecf,1,2,3);
  printf("%f\n",*valf);
  dump(vecf);
  del(&vecf);

  int nx = 20;
  int ny = 30;
  int nz = 10;
  
  
  char inivalc = 'A';
  vector *vecc = zeros(CHAR,3,nx,ny,nz);
  showinfomembers(vecc);
  fill(vecc,&inivalc);
  char *valc = NULL; 
  for (int i=0; i < nx;i++){
    for (int j=0; j < ny;j++){
      for (int k=0; k < nz;k++){
	valc = get(vecc,i,j,k);
	printf("valc is %c\n",*valc);
      }
    }
  }
  
  //dump(vecc);
  del(&vecc);
    
  return 0;
}
