#include<stdio.h>
#include<stdlib.h>

#define MEMSIZE (8)

typedef struct{
  char *beg;
  char *end;
  char *cpool;
}Pool;


void getpool(Pool *pool, int np){
  pool->cpool = (char *) malloc(np*sizeof(char));
  pool->beg = pool->cpool;
  pool->end = (pool->cpool + np -1);
}

void destroypool(Pool *pool){
  if (pool->cpool != NULL )free(pool->cpool);
  pool->beg = NULL;
  pool->end = NULL;
}

char *push_pool(Pool *pool,int ni){
  char *temp = NULL;
  if ( pool->beg != NULL && ( (pool->end -pool->beg + 1) >= ni)){
    temp = pool->beg;
    pool->beg += ni;
  }
  return temp;
}

void print_address(char *pt, int nx){
  char *temp = pt;
  if (temp != NULL){
  for (int i=0; i < nx; i++){
    printf("%p\n",temp);
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




void pool_info(Pool *pool){
  printf("beg = %p \t end = %p\t\n",pool->beg,pool->end);
}

int main(void){

  Pool pool = {NULL,NULL,NULL};
  getpool(&pool,MEMSIZE);  
  pool_info(&pool);
  print_address(pool.cpool,MEMSIZE);

  printf("\n");

  char *ar1 = NULL;
  ar1 = push_pool(&pool,4);
  pool_info(&pool);
  print_address(ar1,4);
  
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
  pool_info(&pool);
  print_address(ar2,2);
 
  destroypool(&pool);

  return 0;
}
