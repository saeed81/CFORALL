#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>


#define N (4096L)

char string[N] = {'\0'};
char stringa[N] = {'\0'};


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

  char *str1="www.smhi.se/";
  char *str2="oceandata";
  char *str3=":80";
  char *str4="?station";

  #if 0

  int ne = 0;

  while (*str1 != '\0'){
    string[ne] = *str1;
    str1++;
    ne++;
  }
  while (*str2 != '\0'){
    string[ne] = *str2;
    str2++;
    ne++;
  }
  while (*str3 != '\0'){
    string[ne] = *str3;
    str3++;
    ne++;
  }
  string[ne] = '\0';

  printf("%s\n",string);

  #endif

  joinstr(str1,str2,str3,str4,NULL);
  
  printf("%s\n",stringa);

  return 0;
}




