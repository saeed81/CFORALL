#include<stdio.h>
#include<stdlib.h>
#include<math.h>

char Str[32]  = {'\0'};
char RStr[32] = {'\0'};

void reverse(char *s, char *t, int sign, int npadzero){
  
  char *tmp = s;
  int len = 0;
  while (*tmp !='\0' ){
    tmp++;
    len++;
  }
  tmp--;

  if (sign < 0){
    *t = '-';
    t++;
  }

  while(npadzero--){
    *t = '0';
    t++;
  }
  
  while (len >0 ){
    *t = *tmp;
    tmp--;
    len--;
    t++;
  }
  *t = '\0';
}

void intostr(int a, char *st){
  int sign = 1;
  if (a < 0){
    sign = -1;
    a = (-a);
  }
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

  reverse(cl,st,sign,0);
  
}


void floatostr(float a, char *str, int nafterdecimalpoint){
  int sign = 1;
  int ia = (int) (a);
  if (a < 0) {
    //printf("we are here\n");
    sign = -1;
    a = (-a);
    ia = (int) (a);
  }
  int npadzero = 0;
  long long int n = 1;
  float b = a - (float)ia;
  float bt = b;
  int hitnonzero = 0;
  //printf("b is %f\n",b);
  for(int i=0; i < nafterdecimalpoint;++i){
    n *= 10L;
    bt *= 10L;
    if (((int)bt == 0) && (hitnonzero == 0)) npadzero++;
    if ((int)bt != 0 ) hitnonzero = 1;
    bt = bt - (int)bt;
  }
  b *= n;
  int ifrac = (int) b;
  //printf("=======================\n");
  //printf("a is %f\n",a);
  //printf("ia is %d\n",ia);
  //printf("b is %f\n",b);
  //printf("ifrac is %d\n",ifrac);
  //printf("=======================\n");
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
  reverse(cl,ctmp,sign,0);

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
  if (sign > 0){
    reverse(ck,ctmp1,sign,npadzero);
  }else{
    reverse(ck,ctmp1,-sign,npadzero);
  }

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
  float fa = -12233.25;
  char cf[64] = {'\0'};
  floatostr(fa,cf,2);
  printf("%s\n",cf);
  fa = 10.13074;
  char cf1[64] = {'\0'};
  floatostr(fa,cf1,4);
  printf("%s\n",cf1);
  float dx = (2.0 * 3.145) / (100000);
  for (int i=0; i < 100000; ++i){
    char cf[64] = {'\0'};
    floatostr(5.0*sin(i * dx) *cos(i * dx) ,cf,4);
    printf("%s\t\t%f\n",cf,5.0*sin(i * dx)*cos(i * dx));
    if ((i %10) == 0 )printf("\n");
  }
  printf("\n");
  return 0;
}

 
    
  

