#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#define Arraycount(a) (sizeof(a) / sizeof(a[0]))
#define StringArraycount(a) (Arraycount(a) -1)
unsigned int stringlen(char *str){
  if (str == NULL) return 0;
  unsigned int len = 0;
  while(*str != '\0'){
    len++;
    str++;
  }
  return len;
}
void writetostring(char *buffer, int N, char *str,...){
  if (str == NULL) return;
  va_list vv;
  va_start(vv,str);
  char *tmp = buffer;
  int counter = 0;
  while(*str!='\0'){
    if (counter < N){
      *tmp = *str;
      tmp++;
    }
    counter++;
    str++;
  }
  while((str=va_arg(vv,char *)) != NULL){
    while(*str!='\0'){
      if (counter < N ){
	*tmp = *str;
	tmp++;
      }
      counter++;
      str++;
    }
  }
  va_end(vv);
  return;
}
int main(void){
  char *fname = "bathy_meter_ns01";
  char *suffix = ".nc";
  char filename[64] = {'\0'};
  writetostring(filename,StringArraycount(filename),fname,suffix,NULL);
  printf("%s\n",filename);
  char *pt  = "saeed";
  char *pt1 = "saeed";
  if (pt == pt1)printf("Yes it works %s\n",pt);
  return 0;
}
