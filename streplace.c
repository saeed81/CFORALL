#include<stdio.h>
#include<stdlib.h>

int lenstr(char *string){
  int len = 0;
  if (string == NULL) return len;
  char *tmp = string;
  while(*tmp!='\0'){
    tmp++;
    len++;
  }
  return len;
}


void stringreplace(char *src, char *sub, char *rep){
  
  if ((src == NULL) || (sub == NULL) || (rep == NULL))return;

  int len1  = 0, len2 = 0;
  char *t1  = src;
  char *t2  = sub;
  char *t3  = rep;
  char *beg = NULL;
  char *end = NULL;

  while(*t1 != '\0'){
    len1++;
    t1++;
  }
  while(*t2 != '\0'){
    len2++;
    t2++;
  }
  if (len2 > len1 )return;
  t1 = src;
  t2 = sub;
  int isexist = 0;
  while(*t1 != '\0'){
    t2 = sub;
    t3 = rep;
    if (*t1 == *t2){
      isexist = 1;
      beg = t1; 
      char *next =  t2+1;
      char *ts   =  t1+1;
      while (*next != '\0' && *ts != '\0'){
	if (*next != *ts ){
	  isexist = 0;
	  break;
	}
	end = ts;
	next++;
	ts++;
      }
    }
    if (isexist) {
      for (char *it = beg; it <=end;++it) *it = ' ';
      for (char *it=beg; (it <=end) && (*t3 != '\0'); ++it){
	*it = *t3;
	t3++;
      }
    }
    t1++;
  }

  char *tmp  = src;
  char *cout = src;
  int ne = 0;
  while (*tmp != '\0'){
    if (*tmp != ' '){
      *(cout + ne) = *tmp;
      ne++;
    }
    tmp++;
  }
  *(cout+ne) = '\0';
  return;
}

int main(void){

  char src[] = "wind.json";
  printf("size is %d \n",lenstr(src));
  stringreplace(src, "json", "nc");
  printf("size is %d \n",lenstr(src));
  stringreplace(src, "wind", "all");
  printf("size is %d \n",lenstr(src));
  char *tmp = src;
  while(*tmp != '\0' ){
    printf("%c",*tmp);
    tmp++;
  }
  
  printf("\n");

  return 0;
}




