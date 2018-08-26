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
  *t = '\0';
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


void floatostr(float a, char *str, int nafterdecimalpoint){
  
  int ia = (int) (a);
  long long int n = 1;
  float b = a - ia;
  for(int i=0; i < nafterdecimalpoint;++i){
    n *= 10L;
  }
  b *= n;
  int ifrac = (int) b;
  printf("a is %f\n",a);
  printf("ia is %d\n",ia);
  printf("b is %f\n",b);
  printf("ifrac is %d\n",ifrac);
  int index = 0;
  int r = -1 ;
  int q = 0;
  char cl[64] = {'\0'};
  char ctmp[64] = {'\0'};
  do {
    r = ia % 10;
    q = (ia - r) / 10;
    *(cl+index) = (char)(r+'0');
    ia = q;
    index++;
  }while(ia >0);

  *(cl+index) = '\0';
  reverse(cl,ctmp);

  char ck[64]    = {'\0'};
  char ctmp1[64] = {'\0'};
  
  r = -1 ;
  q = 0;
  index = 0;
  do {
    r = ifrac % 10;
    q = (ifrac - r) / 10;
    *(ck+index) = (char)(r+'0');
    ifrac = q;
    index++;
  }while(ifrac >0);

  *(ck+index) = '\0';
  reverse(ck,ctmp1);

  char *tmp = ctmp;
  while(*tmp != '\0'){
    *str = *tmp;
    str++;
    tmp++;
  }
  *str = '.';
  str++;
  tmp = ctmp1;

  while(*tmp != '\0'){
    *str = *tmp;
    str++;
    tmp++;
  }
  *str = '\0';
  
  return;
}

  


int main(void){
  #if 0
  char st[64] = {'\0'};
  int kk = 123456789;
  intostr(kk, st);
  printf("%s\n",st);

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
  #endif
  float fa = 1233.87523687;
  char cf[64] = {'\0'};
  floatostr(fa,cf,2);
  printf("%s\n",cf);
  
  return 0;
}

 
    
  

