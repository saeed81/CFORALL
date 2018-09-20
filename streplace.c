#include<stdio.h>
#include<stdlib.h>

void begendsubstring(char *src, char *sub, char **beg, char **end){
  
  if ((src == NULL) || (sub == NULL)){
    *beg = NULL;
    *end = NULL;
    return ;
  }
  int len1 = 0, len2 = 0;
  char *t1 = src;
  char *t2 = sub;
  while(*t1 != '\0'){
    len1++;
    t1++;
  }
  while(*t2 != '\0'){
    len2++;
    t2++;
  }
  if (len2 > len1 ){
    *beg = NULL;
    *end = NULL;
    return ;
  }
  t1 = src;
  t2 = sub;
  int isexist = 0;
  while(*t1 != '\0'){
    t2 = sub;
    if (*t1 == *t2){
      isexist = 1;
      *beg = t1; 
      char *next =  t2+1;
      char *ts   =  t1+1;
      while (*next != '\0' && *ts != '\0'){
	if (*next != *ts ){
	  isexist = 0;
	  break;
	}
	*end = ts;
	next++;
	ts++;
      }
    }
    t1++;
  }

  if (!isexist) {
    *beg = NULL;
    *end = NULL;
  }

  return;
}

void replace(char *str, char *sub, char *rep, char *target, int N){
  char *beg = NULL;
  char *end = NULL;
  begendsubstring(str, sub, &beg, &end);
  if (beg != NULL && end != NULL){
    printf("we are here\n");
  }
  int ii = 0;
  if (beg != NULL && end != NULL){
    for (char *it=str; it <beg && ii < N ; ++it){
      *target = *it;
      target++;
      ii++;
    }
  }
  for (char *it=beg; (it <=end) && (ii < N) && (*rep != '\0'); ++it){
    *target = *rep;
    target++;
    ii++;
    rep++;
  }
  *target = '\0';
}


int main(void){

  char *src = "speed_direction.json";
  char cout[64] = {'\0'};
  replace(src, ".json", ".nc", cout, 64);
  char *tmp = cout;
  while(*tmp != '\0' ){
    printf("%c",*tmp);
    tmp++;
  }
  
  printf("\n");

  return 0;
}




