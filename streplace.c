#include<stdio.h>
#include<stdlib.h>

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
  
  return;
}



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
    if (isexist) break;
    t1++;
  }

  if (!isexist) {
    *beg = NULL;
    *end = NULL;
  }

  return;
}

void replace_imutable(char *str, char *sub, char *rep, char *target, int N){
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
void replace(char *str, char *sub, char *rep){

  if (str == NULL || sub == NULL || rep == NULL) return;
  char *beg = NULL;
  char *end = NULL;
  begendsubstring(str, sub, &beg, &end);
  if (beg == NULL || end== NULL) return; 
  char *tmp = str;
  for (char *it = beg; it <=end;++it) *it = ' ';
}


int main(void){

  char src[] = "wind_speed_direction.json";
  stringreplace(src, ".json", ".nc");
  stringreplace(src, "wind", "all");
  char *tmp = src;
  while(*tmp != '\0' ){
    printf("%c",*tmp);
    tmp++;
  }
  
  printf("\n");

  return 0;
}




