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

typedef vector * mat;

vector *matrix(type type, int nd, ...){

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

void dumponscreen(vector *vec){
  if (vec     == NULL) return;
  if (vec->ar == NULL) return;

  void *tmp = vec->ar;
  int size = vec->size;
  
  if (vec->ar != NULL){
    if (vec->type == INT) {
      for (int i=0; i < size;++i){
	(void)printf("element %03d is %d\n",i,*((int*)tmp+i));
      }
    }
    if (vec->type == FLT) {
      for (int i=0; i < size;++i){
	(void)printf("element %03d is %f\n",i,*((float*)tmp+i));
      }
    }
    if (vec->type == DBL) {
      for (int i=0; i < size;++i){
	(void)printf("element %03d is %f\n",i,*((double*)tmp+i));
      }
    }
    if (vec->type == CHAR) {
      for (int i=0; i < size;++i){
	(void)printf("element %03d is %c\n",i,*((char*)tmp+i));
      }
    }
    
  }
}
void *get(vector *v, int i, ...){
  if (v     == NULL ) return (void *)0;
  if (v->ar == NULL ) return (void *)0;

  if (i < 0 ) return (void *)0;
  va_list va;
  va_start(va,i);
  int ncount = 1;
  int j =0, k =0, l= 0, ii=0;
  int dim = v->dim;
  int nx  = v->nx;
  int ny  = v->ny;
  int nz  = v->nz;
  int nt  = v->nt;
  void *tmp = v->ar;
  while(--dim){
    ii=va_arg(va,int);
    if (ncount == 1) j = ii;
    if (ncount == 2) k = ii;
    if (ncount == 3) l = ii;
    ncount++;
  }
  va_end(va);

  if ((j < 0) || (k < 0) || (l < 0)) return (void *)0;
  if ((i > (nx -1)) || (j > (ny -1)) || (k > (nz -1)) || ( l> (nt -1))) return (void *)0;
  if (v->type == FLT )  return &(((float *)tmp)[l+k*nt+j*nt*nz+i*nt*nz*ny]);
  if (v->type == INT )  return &(((int   *)tmp)[l+k*nt+j*nt*nz+i*nt*nz*ny]);
  if (v->type == DBL )  return &(((double*)tmp)[l+k*nt+j*nt*nz+i*nt*nz*ny]);
  if (v->type == CHAR)  return &(((char  *)tmp)[l+k*nt+j*nt*nz+i*nt*nz*ny]);

  return (void *)0;
}


void set(vector *v, void *value, int i, ...){

  if (i < 0 ) return;
  if (v == NULL ) return;
  if (v->ar == NULL) return;
  va_list va;
  va_start(va,i);
  int ncount = 1;
  int j =0, k =0, l= 0, ii=0;
  int dim = v->dim;
  int nx  = v->nx;
  int ny  = v->ny;
  int nz  = v->nz;
  int nt  = v->nt;
  void *tmp  = v->ar;
  while(--dim){
    ii=va_arg(va,int);
    if (ncount == 1) j = ii;
    if (ncount == 2) k = ii;
    if (ncount == 3) l = ii;
    ncount++;
  }
  va_end(va);

  if ((j < 0) || (k < 0) || (l < 0)) return;
  if ((i > (nx -1)) || (j > (ny -1)) || (k > (nz -1)) || ( l> (nt -1))) return;
  if (v->type == FLT )  ((float *)tmp)[l+k*nt+j*nt*nz+i*nt*nz*ny] = *(float *)value; 
  if (v->type == INT )  ((int   *)tmp)[l+k*nt+j*nt*nz+i*nt*nz*ny] = *(int   *)value; 
  if (v->type == DBL )  ((double*)tmp)[l+k*nt+j*nt*nz+i*nt*nz*ny] = *(double*)value;
  if (v->type == CHAR)  ((char  *)tmp)[l+k*nt+j*nt*nz+i*nt*nz*ny] = *(char  *)value;

  return;
}


void seriealize(vector *vec, char *filename){

  if (vec      == NULL) return;
  if (vec->ar  == NULL) return;
  if (filename == NULL) return;
  FILE *file = NULL;
  file = fopen(filename,"w+");
  if (file == NULL){
    printf("problem in opening the file %s\n",filename);
    return;
  }
  int nx  = vec->size;
  int nxn = nx -1;
  if (vec->type == INT) {
    fprintf(file,"int array[%d]={",vec->size);
    for (int i=0; i <nxn; ++i){
      (void)fprintf(file,"%d,",*((int*)vec->ar+i));
    }
  }
  if (vec->type == FLT) {
    fprintf(file,"float array[%d]={",vec->size);
    for (int i=0; i < nxn;++i){
      (void)fprintf(file,"%f,",*((float*)vec->ar+i));
    }
  }
  if (vec->type == DBL) {
    fprintf(file,"double array[%d]={",vec->size);
    for (int i=0; i < nxn;++i){
      (void)fprintf(file,"%f,",*((double*)vec->ar+i));
    }
  }
  if (vec->type == CHAR){
    fprintf(file,"char array[%d]={",vec->size);
    for (int i=0; i < nxn;++i){
      (void)fprintf(file,"%c,",*((char*)vec->ar+i));
    }
  }
  int i = nxn;

  if (vec->type == INT) {
    (void)fprintf(file,"%d};",*((int*)vec->ar+i));
  }
  if (vec->type == FLT) {
         (void)fprintf(file,"%f};",*((float*)vec->ar+i));
  }
  if (vec->type == DBL) {
    (void)fprintf(file,"%f};",*((double*)vec->ar+i));
  }
  if (vec->type == CHAR) {
    (void)fprintf(file,"%c};",*((char*)vec->ar+i));
  }

  fclose(file);
  
  return;    
}  
  

  


void showinfomembers(vector *vec){

  if (vec == NULL)     return;
  if (vec->ar == NULL) return;
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
  
  int   inivali = 0;
  mat veci = matrix(INT,2,1024,1024);
  showinfomembers(veci);
  fill(veci,&inivali);
  dumponscreen(veci);
  for (int i=0; i < 1024;i++){
    for (int j=0; j < 1024;j++){
      inivali = i * j;
      set(veci,&inivali,i,j);
    }
  }
  seriealize(veci,"array.dat");
  del(&veci);
  return 1;
  
  float inivalf = 0.250f;
  mat vecf = matrix(FLT,3,2,3,4);
  showinfomembers(vecf);
  fill(vecf,&inivalf);
  float *valf = get(vecf,1,2,3);
  printf("%f\n",*valf);
  dumponscreen(vecf);
  del(&vecf);
   
  int nx = 2;
  int ny = 3;
  int nz = 4;
  char inivalc = 'C';
  mat vecc = matrix(CHAR,3,nx,ny,nz);
  showinfomembers(vecc);
  fill(vecc,&inivalc);
  char *valc = NULL; 
  for (int i=0; i < nx;i++){
    for (int j=0; j < ny;j++){
      for (int k=0; k < nz;k++){
	valc =get(vecc,i,j,k);
	printf("valc is %c\n",*valc);
      }
    }
  }

  inivalc = 'X';
  set(vecc,&inivalc,1,1,1);
  valc = get(vecc,1,1,1);
  printf("valc is %c\n",*valc);

  inivalc = 'Y';
  set(vecc,&inivalc,1,2,3);
  valc = get(vecc,1,2,3);
  printf("valc is %c\n",*valc);
    
  dumponscreen(vecc);
  del(&vecc);

  nx = 1001, ny = 1001, nz = 1;
  inivalf = 0.250f;
  vecf = matrix(FLT,3,nx,ny,nz);
  showinfomembers(vecf);
  fill(vecf,&inivalf);

  for (int i=0; i < nx;i++){
    for (int j=0; j < ny;j++){
      for (int k=0; k < nz;k++){
	inivalf = (float)(i*j*k);
	set(vecf,&inivalf,i,j,k);
      }
    }
  }
  #if 1
  for (int i=0; i < nx;i++){
    for (int j=0; j < ny;j++){
      for (int k=0; k < nz;k++){
	valf = get(vecf,i,j,k);
	printf("(%d,%d,%d)\t%p\n",i,j,k,(void *)valf);
      }
    }
  }

  //dumponscreen(vecf);

  seriealize(vecf,"MYMATRIX.dat");
  #endif
  del(&vecf);
  

  
  return 0;
}
