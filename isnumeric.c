#include<stdio.h>
#include<stdlib.h>

#define endl printf("\n")
#define LEN(a) (sizeof(a) / sizeof(a[0]))

void findc(char *s, char sym, int *j){
  int n = 0;
  while(*s != '\0'){
    if (*s == sym){
      *j = n;
      break;
    }
    s++;
    n++;
  }
  return;
}

int isfloat(char *s){

  int yes = 0;
  int numeric = 0;
  int alpha = 0;
  int dot = 0;


  while(*s != '\0'){
    if (*s >= '0' && *s<='9') numeric++;
    if (*s >= 'a' && *s<='z') alpha++;
    if (*s >= 'A' && *s<='Z') alpha++;
    if (*s == '.') dot++;
    s++;
  }

  if ( numeric > 0 && (alpha == 0)) yes = 1;
  if ( numeric > 0 && (alpha > 0 )) yes = 0;
  if ( numeric == 0               ) yes = 0;
  if ( numeric == 0 && (dot > 0)  ) yes = 0;
  
  return yes;
}

int isint(char *s){

  int yes = 0;
  int numeric = 0;
  int alpha = 0;
  int dot = 0;


  while(*s != '\0'){
    if (*s >= '0' && *s<='9') numeric++;
    if (*s >= 'a' && *s<='z') alpha++;
    if (*s >= 'A' && *s<='Z') alpha++;
    if (*s == '.') dot++;
    s++;
  }

  if ( numeric > 0 && (alpha == 0) && (dot == 0)) yes = 1;
  if ( numeric > 0 && (alpha > 0 )              ) yes = 0;
  if ( numeric > 0 && (alpha == 0 ) && (dot > 0)) yes = 0;
  if ( numeric == 0               )               yes = 0;
  if ( numeric == 0 && (dot > 0)  )               yes = 0;
  
  return yes;
}

int main(void){

  char str[] = "{lat:12,lon:10,info:{par:vind,value:[1,2,3,4,5]}}";

  int nx = LEN(str);

  int j = -1;

  for (int i=0; i < nx; ++i){
    if (str[i] == 'p' && str[i+1] == 'a' && str[i+2] == 'r' ){
      j = i;
      break;
    }
  }
  for (int i=j; i <= (j+2);++i)printf("%c",str[i]);
  endl;
  
  int k = -1;
  for (int i=(j+3); i < nx; ++i){
    if (str[i] == ':'){
      k = i;
    }
  }


  char sar[] = "[1,2,3,4,5]";

  //int ny = sizeof(sar) / sizeof(sar[0]);

  findc(sar,'[',&j);
  findc(sar,']',&k);
  printf("sart %d and end %d\n",j,k);

  int nel = 0;

  for (int i=(j+1); i < k;++i){
    if (sar[i] != ','){
      printf("%d",sar[i]-'0');
      nel++; 
    }
  }
  endl;
  int *val = (int *)malloc(nel *sizeof(int));
  
  nel = 0;
  for (int i=(j+1); i < k;++i){
    if (sar[i] != ','){
      val[nel] = sar[i] - '0';
      nel++;
    }
  }
  for (int i=0; i < nel; ++i){
    printf("%d\n",val[i]);
  }
  free(val);

  char *sf[4] = {"1.2","1","1c","1Ac.2"};
  printf("%s string is float yes(1), no(0) : %d",sf[0],isfloat(sf[0]));endl;
  printf("%s string is float yes(1), no(0) : %d",sf[1],isfloat(sf[1]));endl;
  printf("%s string is float yes(1), no(0) : %d",sf[2],isfloat(sf[2]));endl;
  printf("%s string is float yes(1), no(0) : %d",sf[3],isfloat(sf[3]));endl;

  char *si[4] = {"1","1.1","1c","1Ac.2"};
  printf("%s string is int yes(1), no(0) : %d",si[0],isint(si[0]));endl;
  printf("%s string is int yes(1), no(0) : %d",si[1],isint(si[1]));endl;
  printf("%s string is int yes(1), no(0) : %d",si[2],isint(si[2]));endl;
  printf("%s string is int yes(1), no(0) : %d",si[3],isint(si[3]));endl;

  return 0;
  
}



  



