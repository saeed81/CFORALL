#include<stdio.h>
#include<stdlib.h>
#include"matching.h"

int power10(int n){
  int a = 1;
  while(n--){
    a *= 10;
  }
  return a;
}

int fun(char *c){
  char *tmp = c;
  int len = 0;
  while (*tmp != '\0'){
    len++;
    tmp++;
  }
  int index = 0;
  tmp = c;
  int ncount = 0;

  for (int i = (len-1); i>=0; --i){
    index += (c[i]-'0') * power10(ncount);
    ncount++; 
  }
  //if ( c[0] >= '0' && c[0] <= '9'){
  //  printf("input character is digint\n");
  //  index = (c[0] - '0');
  //}
  //printf("index is %d\n",index);

  return index;
  //if (index > 0) printf("%d\n",a[index]);
}

void array_value(char *st, char *cind){
  int len   = 0;
  char *tmp = st;
  if (st == NULL) return;
  while(*tmp != '\0'){
    len++;
    tmp++;
  }
  len++;
  char type = '\0';
  int dicel = 0;
  if (st[0] == '['){
    printf("this is array\n");
    type = 'a';
  }
  int j = -1;
  if (type == 'a'){
    for (int i=1; i < len; ++i){
      if (st[i] == '{'){
	j = i;
	break;
      }
    }
  }
  if (j > 0){
    dicel = 1;
    for (int i=(j-1); i>0;--i){
      if ((st[i] != ' ') || (st[i] != '\t') || (st[i] != '\r') || (st[i] != '\n') ){
	dicel = 0;
	break;
      }
    }
  }
  int index = -1;
  int icol  = -1;
  int nel   = 0;
  int first = 1;
  int last  = 1;
  int stop = 1;
  if (dicel == 1){
    while( j < len && stop){
      icol = 0;
      match(&st[j], 1, '{', &index);
      //printf("j is %d and index is \t %c \n",j,st[j+index]);
      if (nel == fun(cind)){
	for (int i=j;i<=(j+index);++i){
	  printf("%c",st[i]);
	}
      }
      printf("\n");
      for (int i=(j+index+1);i < len;++i){
	if (st[i] == ','){
	  first = j;
	  last = i;
      	  j = i;
	  icol = 1;
	  break;
	}
      }
      nel++;
      if (icol == 0) break;
      for (int i=(j+1);i < len;++i){
	if (st[i] == '{'){
	  j = i;
	  break;
	}
      }
    }
    printf("number of elements is %d\n",nel);
  }
  index = -1;
  icol  = -1;
  nel   = 0;
  j = 1;
  first = 1;
  last  = 1;
  stop = 1;
  if (dicel == 0 ){
    while( (j < len) && stop){
      icol = 0;
      for (int i=j;i < len;++i){
	if (st[i] == ','){
	  first = j;
	  last = i;
	  if (nel == fun(cind)){
	    for (int k=first;k < last;++k) printf("%c",st[k]);
	    printf("\n");
	    stop = 1;
	  }
	  j = (i+1);
	  icol = 1;
	  break;
	}
      }
      nel++;
      //printf("j is %d\n",j);
      if (icol == 0) break;
    }
    printf("number of elements is %d\n",nel);
  }
  //fun("10");
  //printf("%d\n",power10(5));
}

void array_explode(char *st){
  int len   = 0;
  char *tmp = st;
  if (st == NULL) return;
  while(*tmp != '\0'){
    len++;
    tmp++;
  }
  len++;
  char type = '\0';
  int dicel = 0;
  if (st[0] == '['){
    printf("this is array\n");
    type = 'a';
  }
  int j = -1;
  if (type == 'a'){
    for (int i=1; i < len; ++i){
      if (st[i] == '{'){
	j = i;
	break;
      }
    }
  }
  if (j > 0){
    dicel = 1;
    for (int i=(j-1); i>0;--i){
      if ((st[i] != ' ') || (st[i] != '\t') || (st[i] != '\r') || (st[i] != '\n') ){
	dicel = 0;
	break;
      }
    }
  }
  int index = -1;
  int icol  = -1;
  int nel   = 0;
  if (dicel == 1){
    while( j < len){
      icol = 0;
      match(&st[j], 1, '{', &index);
      //printf("j is %d and index is \t %c \n",j,st[j+index]);
      for (int i=j;i<=(j+index);++i){
	printf("%c",st[i]);
      }
      printf("\n");
      nel++;
      for (int i=(j+index+1);i < len;++i){
	if (st[i] == ','){
	  j = i;
	  icol = 1;
	  break;
	}
      }
      if (icol == 0) break;
      for (int i=(j+1);i < len;++i){
	if (st[i] == '{'){
	  j = i;
	  break;
	}
      }
    }
    printf("number of elements is %d\n",nel);
  }
  index = -1;
  icol  = -1;
  nel   = 0;
  j = 1;
  if (dicel == 0 ){
    while( j < len){
      icol = 0;
      nel++;
      for (int i=j;i < len;++i){
	if (st[i] == ','){
	  j = (i+1);
	  icol = 1;
	  break;
	}
      }
      printf("j is %d\n",j);
      if (icol == 0) break;
    }
    printf("number of elements is %d\n",nel);
  }
  //fun("10");
  //printf("%d\n",power10(5));
}

#if 0
int main(void){
  
  char c[]  = "[{[{}]},{[{}]},{[{}]},{[{}]},{[{}]},{[{}]}]";
  char cd[] = "[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21]";
  
  //array_explode(c);
  //array_explode(cd);
  array_value(cd,"11");
  fun("256");
  
  return 0;

}
#endif
