#include<stdio.h>
#include<stdlib.h>


#define MEMSIZE (8)

char *getpool(size_t np){

  char *cpool = (char *)malloc(np *sizeof(char));
  return cpool;
}
void destroypool(char **cpool){
  if (*cpool != NULL )free(*cpool);
  *cpool = NULL;
}

void push_pool(char **pool, char **ar, int nx, int psize){
      *ar = *pool;
      *(ar+1) = *(pool+1);
}


void print_address(void *pt, int nx){
  for (int i=0; i < nx; ++i){
    (void)(printf("%p\n",pt+i));
  }
}

int main(void){

  char *pool = getpool(MEMSIZE);

  print_address(pool,MEMSIZE);

  printf("\n");

  char *arr = NULL;

  push_pool(&pool,&arr,4,MEMSIZE);

  print_address(arr,4);
  
  *arr = 'a';
  *(arr+1) = 'b';
  *(arr+2) = 'c';
  *(arr+3) = 'd';

  printf("%c\n",*arr);
  printf("%c\n",*(arr+1));
  printf("%c\n",*(arr+2));
  printf("%c\n",*(arr+3));
  
  destroypool(&pool);

  return 0;
}
