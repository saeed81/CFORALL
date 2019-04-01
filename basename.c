#include<stdio.h>
#include<stdlib.h>


void basename(char *str){

  char *t1 = str;
  char *t2 = str;
  while(*t1 != '\0'){

    if (*t1 == '/'){
      for (char *c = t2; c<= t1;++c )*c = ' ';
      t2 = t1;
    }
    t1++;
  }

  t1 = str;
  int nn = 0;
  while(*str != '\0'){
    if (*str != ' ' ){
      *(t1 + nn) = *str;
      nn++;
    }
    str++;
  }
  if (nn > 0)*(t1 + nn) = '\0';
  str = t1;
}

int main(void){


  char filename[] = "/usr/bin/mybin/main.c";

  basename(filename);

  printf("%s\n",filename);

  return 0;
  
}
