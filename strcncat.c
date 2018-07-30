#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>

typedef struct vector{
  char *aa;
  int size;
  int counter;
}vector; 


void vector_init(vector *vv){
  vv->size = 0;
  vv->counter = 0;
  vv->aa = NULL;
  return;
}
void vector_add(vector *vv, char b){
  if (vv->aa == NULL){
    vv->size = 2;
    vv->aa = (char *)malloc(vv->size * sizeof(char));
    if (vv->aa == NULL) return;
    vv->aa[vv->counter] = b;
    vv->counter += 1;
  }
  else{
    if (vv->counter < vv->size ){
      vv->aa[vv->counter] = b;
      vv->counter += 1;
    }
    else{
      vv->size *= 2;
      char *temp = NULL;
      temp = (char *) realloc(vv->aa, vv->size * sizeof(char));
      if (temp == NULL) return;
      vv->aa = temp;
      vv->aa[vv->counter] = b;
      vv->counter += 1;
    }
  }
}

void vector_free(vector *vv){
  if (vv->aa != NULL)free(vv->aa);
  vv->aa = NULL;
  return;
}


void vector_dump(vector *vv){
  printf("=============================================\n");
  printf("vector_size = %-8d vector_counter = %-8d\n", vv->size, vv->counter);
  if(vv->aa == NULL){
    printf("input vector is empty\n");
    printf("=============================================\n");
  }else{
    for(int ii=0; ii < vv->counter; ++ii){
      printf("%c",vv->aa[ii]);
    }
    printf("=============================================\n");
  }
  return;
}

void string_concat_var(vector *vec,char *str, ...){
  vector_init(vec);
  if (str == NULL) return ;
  unsigned int len =0;
  va_list vv;
  va_start(vv,str);
  char *tmp = str;
  while(*tmp != '\0'){
    vector_add(vec,*tmp);
    len++;
    tmp++;
  }
  while ((tmp=va_arg(vv,char *)) != NULL){
    while(*tmp != '\0'){
      vector_add(vec,*tmp);
      len++;
      tmp++;
    }
  }
  va_end(vv);

  return ;
}

char *string_concat(char *str1, char *str2){
 
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
  //printf("%u\n",len12);
  char *str12 = (char *)malloc((len12+1) *sizeof(char));
  char *strout = str12;
  if (str12 == NULL) return NULL;
  len12 = 0;
  tmp = str1;
  while(*tmp != '\0' ){
    *str12 = *tmp;
    //printf("%c\n",*str12);
    tmp++;
    str12++;
  }
  tmp = str2;
  while(*tmp != '\0'){
    *str12 = *tmp;
    //printf("%c\n",*str12);
    tmp++;
    str12++;
  }
  *str12 = '\0';

  return strout;
}


int main(int argc,char *argv[]){
 
  char *name = NULL;
  name = string_concat(argv[1],argv[2]);
  printf("%s\n",name);
  if (name != NULL) free(name);
  vector vec;
  string_concat_var(&vec,"a","b","c","d","e","f","g","e","h",NULL);
  vector_dump(&vec);
  vector_free(&vec);
  return 0;
}
