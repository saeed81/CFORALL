#include<stdio.h>
#include<stdlib.h>
#include"matching.h"

int a[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40};

int power10(int n){
  int a = 1;
  while(n--){
    a *= 10;
  }
  return a;
}

void fun(char *c){
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
  #if 0  
  if ( c[0] >= '0' && c[0] <= '9'){
    printf("input character is digint\n");
    index = (c[0] - '0');
  }
  #endif
  if (index > 0) printf("%d\n",a[index]);
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
	//printf("there is something between { and [ and is %c\n",st[i]);
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

int main(void){
  char c[]  = "[{[{}]},{[{}]},{[{}]},{[{}]},{[{}]},{[{}]}]";
  char cd[] = "[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21]";
  array_explode(c);
  array_explode(cd);
  
  return 1;

  int len   = sizeof(c)  / sizeof(c[0]);
  int lend  = sizeof(cd) / sizeof(cd[0]);
  char type = '\0';
  int dicel = 0;

  if (c[0] == '['){
    printf("this is array\n");
    type = 'a';
  }

  int j = -1;
  if (type == 'a'){
    for (int i=1; i < len; ++i){
      if (c[i] == '{'){
	j = i;
	break;
      }
    }
  }
  
  if (j > 0){
    dicel = 1;
    for (int i=(j-1); i>0;--i){
      if ((c[i] != ' ') || (c[i] != '\t') || (c[i] != '\r') || (c[i] != '\n') ){
	printf("there is something between { and [ and is %c\n",c[i]);
	dicel = 0;
	break;
      }
    }
  }
  int index = -1;
  int icol  = -1;
  int nel = 0;
  if (dicel==1){
    while( j < len){
      icol = 0;
      match(&c[j], 1, '{', &index);
      printf("j is %d and index is \t %c \n",j,c[j+index]);
      nel++;
      for (int i=(j+index+1);i < len;++i){
	if (c[i] == ','){
	  j = i;
	  icol = 1;
	  break;
	}
      }
      if (icol == 0) break;
      for (int i=(j+1);i < len;++i){
	if (c[i] == '{'){
	  j = i;
	  break;
	}
      }
    }
  }
  printf("number of elements is %d\n",nel);
  
  if (cd[0] == '['){
    printf("this is array\n");
    type = 'a';
  }
  
  dicel = 0;
  j = 1;
  index = -1;
  icol  = -1;
  nel = 0;
  if (dicel == 0 ){
    while( j < lend){
      icol = 0;
      nel++;
      for (int i=j;i < lend;++i){
	if (cd[i] == ','){
	  j = (i+1);
	  icol = 1;
	  break;
	}
      }
      printf("j is %d\n",j);
      if (icol == 0) break;
    }
  }
  //fun("10");

  //printf("%d\n",power10(5));
  printf("number of elements is %d\n",nel);

  return 0;
}

