#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>


#define N (4096L)

char string[N] = {'\0'};
char stringa[N] = {'\0'};

void joinstrdelim(char delim, char *str,...){

  va_list vs;

  va_start(vs,str);

  int ne = 0;
  char *tmp     = NULL;
  
  while(*str != '\0'){ 
    stringa[ne] = *str;
    str++;
    ne++;
  }
  stringa[ne] = delim;
  ne++;

  while((tmp=va_arg(vs,char *)) != NULL){
    
    while(*tmp != '\0'){ 
      stringa[ne] = *tmp;
      tmp++;
      ne++;
    }
    stringa[ne] = delim;
    ne++;
  }

  for (int i=(N-1); i>=0; --i ){
    if (stringa[i] == delim){
      stringa[i] = '\0';
      break;
    }
  }
  
  stringa[ne] = '\0';
  va_end(vs);
  return ;
}


void joinstr(char *str,...){

  va_list vs;

  va_start(vs,str);

  char *tmp = NULL;

  int ne = 0;

  while(*str != '\0'){ 
    stringa[ne] = *str;
    str++;
    ne++;
  }
  
  while((tmp=va_arg(vs,char *)) != NULL){
    
    while(*tmp != '\0'){ 
      stringa[ne] = *tmp;
      tmp++;
      ne++;
    }
  }
  stringa[ne] = '\0';
  va_end(vs);
  return ;
}


int main(void){

  char *str1="2018";
  char *str2="04";
  char *str3="12";
  char *str4="date";

  //joinstr(str1,str2,str3,str4,NULL);
  joinstrdelim('/',str1,str2,str3,str4,NULL);
  
  printf("%s\n",stringa);

  return 0;
}




