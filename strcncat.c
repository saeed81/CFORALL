#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>

typedef struct String{
  char *aa;
  int size;
  int counter;
}String; 

void String_init(String *str){
  str->size = 0;
  str->counter = 0;
  str->aa = NULL;
  return;
}

void String_add(String *str, char b){
  if (str->aa == NULL){
    str->size = 2;
    str->aa = (char *)malloc(str->size * sizeof(char));
    if (str->aa == NULL) return;
    str->aa[str->counter] = b;
    str->counter += 1;
  }
  else{
    if (str->counter < str->size ){
      str->aa[str->counter] = b;
      str->counter += 1;
    }
    else{
      str->size *= 2;
      char *temp = NULL;
      temp = (char *) realloc(str->aa, str->size * sizeof(char));
      if (temp == NULL) return;
      str->aa = temp;
      str->aa[str->counter] = b;
      str->counter += 1;
    }
  }
}

void String_free(String *str){
  if (str->aa != NULL)free(str->aa);
  str->aa = NULL;
  return;
}

void String_dump(String *str){
  printf("=============================================\n");
  printf("String_size = %-8d String_counter = %-8d\n", str->size, str->counter);
  if(str->aa == NULL){
    printf("input String is empty\n");
    printf("=============================================\n");
  }else{
    for(int ii=0; ii < str->counter; ++ii){
      printf("%c",str->aa[ii]);
    }
    printf("=============================================\n");
  }
  return;
}

void String_concat_var(String *vec,char *str, ...){
  String_init(vec);
  if (str == NULL) return ;
  unsigned int len =0;
  va_list vv;
  va_start(vv,str);
  char *tmp = str;
  while(*tmp != '\0'){
    String_add(vec,*tmp);
    len++;
    tmp++;
  }
  while ((tmp=va_arg(vv,char *)) != NULL){
    while(*tmp != '\0'){
      String_add(vec,*tmp);
      len++;
      tmp++;
    }
  }
  va_end(vv);

  return ;
}

char *String_concat(char *str1, char *str2){
 
  if ((str1 == NULL)|| (str2 == NULL) ) return NULL;
  unsigned int len1 =0, len2 = 0, len12 = 0;
  char *tmp = str1;
  while(*tmp != '\0'){
    len1++;
    tmp++;
  }
  tmp = str2;
  while(*tmp != '\0'){
    len2++;
    tmp++;
  }
  len12 = len1 + len2;
  char *str12 = (char *)malloc((len12+1) *sizeof(char));
  char *strout = str12;
  if (str12 == NULL) return NULL;
  len12 = 0;
  tmp = str1;
  while(*tmp != '\0' ){
    *str12 = *tmp;
    tmp++;
    str12++;
  }
  tmp = str2;
  while(*tmp != '\0'){
    *str12 = *tmp;
    tmp++;
    str12++;
  }
  *str12 = '\0';

  return strout;
}

int main(int argc,char *argv[]){
  char *name = NULL;
  name = String_concat("bb","cc");
  printf("%s\n",name);
  if (name != NULL) free(name);
  int i=10;
  for(;i;--i){
    String str;
    String_concat_var(&str,"a","b","c","d","e","f","g","e","h","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",NULL);
    String_dump(&str);
    String_free(&str);
  }
  return 0;
}
