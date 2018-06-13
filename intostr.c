#include<stdio.h>
#include<stdlib.h>

char Str[32]  = {'\0'};
char RStr[32] = {'\0'};

void reverse(char *s, char *t){
  
  char *tmp = s;
  int len = 0;
  while (*tmp !='\0' ){
    tmp++;
    len++;
  }
  tmp--;
  while (len >0 ){
    *t = *tmp;
    tmp--;
    len--;
    t++;
  }
}

void intostr(int a, char *st){
  
  int index = 0;
  int r = -1 ;
  int q = 0;
  char cl[64] = {'\0'};
  do {
    r = a % 10;
    q = (a - r) / 10;
    *(cl+index) = (char)(r+'0');
    a = q;
    index++;
  }while(a >0);
  
  *(cl+index) = '\0';

  reverse(cl,st);
  
}


int main(void){
  char st[64] = {'\0'};
  int kk = 123456789;
  intostr(kk, st);
  printf("%s\n",st);
  return 1;

  int index = 0;
  int a = 1234567;
  int r = -1 ;
  int q = 0;
  do {
    r = a % 10;
    q = (a - r) / 10;
    Str[index] = (char)(r+'0');
    a = q;
    index++;
  }while(a >0);

  Str[index] = '\0';
  reverse(Str,RStr);
  printf("%s\n",Str);
  printf("%s\n",RStr);

  return 0;
}
