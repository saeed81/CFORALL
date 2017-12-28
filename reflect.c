#include<stdio.h>
#include<stdlib.h>

typedef void (*operate)(int *, int);

void increment(int *, int);
void decrement(int *, int);

enum {
  INCR, DECR
};

struct action{

  operate act[2];
};

int main(void){

  int a = 5;

  struct action Sact = {{&increment,&decrement}};

  Sact.act[INCR](&a,1);
  printf("%d\n",a);
  Sact.act[DECR](&a,2);
  printf("%d\n",a);
  
  return 0;
}


void increment(int *a, int c){
  *a += c;
}

void decrement(int *a, int c){
  *a -= c;
}








