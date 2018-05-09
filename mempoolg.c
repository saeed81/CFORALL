#include<stdio.h>
#include<stdlib.h>

#define MEMSIZE (64 * 1024L * 1024L)

char POOL[MEMSIZE] = {0};

typedef struct{
  char *beg;
  char *end;
  char *cpool;
  int cur;
}Pool;


void init_pool(Pool *pool, int np){
  pool->cpool = POOL;
  pool->beg = pool->cpool;
  pool->end = (pool->cpool + np -1);
  pool->cur = -1;
}

void del_pool(Pool *pool){
  pool->cpool = NULL;
  pool->beg = NULL;
  pool->end = NULL;
  pool->cur = 0;
}

char *push_pool(Pool *pool,int ni){
  char *temp = NULL;
  if ( pool->beg != NULL && ( (pool->end -pool->beg + 1) >= ni)){
    temp = pool->beg;
    pool->beg += ni;
    pool->cur += ni;
  }
  return temp;
}

void print_address(void *pt, int nx){
  char *temp = (char *)pt;
  if (temp != NULL){
  for (int i=0; i < nx; i++){
    printf("%p\n",(void *)temp);
    temp++;
  }
  }
}


void print_values(char *pt, int nx){
  char *temp = pt;
  if (temp != NULL){
  for (int i=0; i < nx; i++){
    printf("%c\n",*temp);
    temp++;
  }
  }
}

void info_pool(Pool *pool){
  printf("beg = %p \t end = %p\t cur= %d\n",(void *)pool->beg,(void *)pool->end,pool->cur);
}

int main(void){

  Pool pool =  {NULL, NULL, NULL, 0};
  init_pool(&pool,MEMSIZE);  
  info_pool(&pool);
  printf("\n");

  char *ar1 = NULL;
  ar1 = push_pool(&pool,4);
  info_pool(&pool);

  printf("address char \n");
  print_address(ar1,4);

  printf("address POOL \n");
  printf("%p\n",(void *)(POOL));
  printf("%p\n",(void *)(POOL+1));
  printf("%p\n",(void *)(POOL+2));
  printf("%p\n",(void *)(POOL+3));

  *ar1 = 'a';
  *(ar1+1) = 'b';
  *(ar1+2) = 'c';
  *(ar1+3) = 'c';
  
  print_values(ar1,4);

  printf("\n");

  char *ar2 = NULL; 
  ar2 = push_pool(&pool,2);
  *ar2 = 'A';
  *(ar2+1) = 'B';
  print_values(ar2,2);
  info_pool(&pool);
  print_address(ar2,2);
 

  int *ip = (int *)(push_pool(&pool,16));
  
  ip[0] = 1;
  ip[1] = 2000;
  ip[2] = 30000;
  ip[3] = 400000;

  printf("%d\n",ip[0]);
  printf("%d\n",ip[1]);
  printf("%d\n",ip[2]);
  printf("%d\n",ip[3]);

  printf("%p\n",ip);
  printf("%p\n",ip+1);
  printf("%p\n",ip+2);
  printf("%p\n",ip+3);

  info_pool(&pool);
  
  float *fp = (float *)(push_pool(&pool,4*sizeof(float)));

  if (fp != NULL ){
    fp[0] = 1.0;
    fp[1] = 2.0;
    fp[2] = 3.0;
    fp[3] = 4.0;
    printf("%p\n",fp);
    printf("%p\n",fp+1);
    printf("%p\n",fp+2);
    printf("%p\n",fp+3);
  }

  float *fpp = (float *)(push_pool(&pool,1024*sizeof(float)));

  if (fpp != NULL ){
    for (int i=0; i < 1024;++i){
      *(fpp+i) = (float)(i * i);
    }
    
    for (int i=0; i < 20;++i){
      printf("%f\n",*(fpp+i));
    }
  }
  info_pool(&pool);
  del_pool(&pool);

  return 0;
}
