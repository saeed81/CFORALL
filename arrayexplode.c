#include<stdio.h>
#include<stdlib.h>
#include"matching.h"


typedef struct tIndex{
  int findex;
  int lindex;
}Index;

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

char *array_value(char *st, char *cind){
  int len   = 0;
  char *tmp = st;
  if (st == NULL) return NULL;
  while(*tmp != '\0'){
    len++;
    tmp++;
  }
  len++;
  char type = '\0';
  int dicel  = 0;
  int rb     = 0;
  if (st[0] == '['){
    //printf("this is array\n");
    type = 'a';
  }
  match(&st[0], '[', &rb);
  //printf("rb %d\n",rb);
  
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
  char *cout = NULL;
  if (dicel == 1){
    while( j < len && stop){
      icol = 0;
      match(&st[j], '{', &index);
      //printf("j is %d and index is \t %c \n",j,st[j+index]);
      if (nel == fun(cind)){
	cout = NULL;
	int ncount = 0;
	cout = (char *)malloc(index+2);
	for (int i=j;i<=(j+index);++i){
	  //printf("%c",st[i]);
	  cout[ncount] = st[i];
	  ncount++;
	}
	cout[index+1] = '\0';
	stop = 0;
      }
      //printf("\n");
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
    //printf("number of elements is %d\n",nel);
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
	  j = (i+1);
	  icol = 1;
	  break;
	}
      }
      if (icol == 0 && nel == 0){
	if (nel == fun(cind)){
	  //printf("rb is %d",rb);
	  int ncount = 0;
	  last = rb -1;
	  cout = (char *)malloc(last-first+2);
	  for (int k=first;k <=last;++k){
	    //printf("%c",st[k]);
	    cout[ncount] = st[k];
	    ncount++;
	  }
	  cout[ncount] = '\0';
	  //printf("\n");
	  stop = 0;
	}
      }

      if (icol == 0 && nel > 0){
	first = last +1;
	last = rb -1;
	//printf("here2 %d\t %d\n",last,first);
	if (nel == fun(cind)){
	  int ncount = 0;
	  cout = (char *)malloc(last-first+2);
	  for (int k=first;k <= last;++k){
	    //printf("%c",st[k]);
	    cout[ncount] = st[k];
	    ncount++;
	  }
	  cout[ncount] = '\0';
	    //printf("\n");
	  stop = 0;
	}
      }

      if (icol == 1){
	//printf("here3 %d\t %d\n",last,first);
	if (nel == fun(cind)){
	  int ncount = 0;
	  cout = (char *)malloc(last-first+1);
	  for (int k=first;k < last;++k){
	    //printf("%c",st[k]);
	    cout[ncount] = st[k];
	    ncount++;
	  }
	  cout[ncount] = '\0';
	  //printf("\n");
	  stop = 0;
	}
      }
      nel++;
      //printf("j is %d\n",j);
    }
    //printf("number of elements is %d\n",nel);
  }

  return cout;
  //fun("10");
  //printf("%d\n",power10(5));
}

Index array_value_pt(char *beg, char *end, char *cind){
  int len   = 0;
  char *tmp = beg;
  while(tmp <= end){
    len++;
    tmp++;
  }
  char type = '\0';
  int dicel  = 0;
  int rb     = 0;
  if (*beg == '['){
    //printf("this is array\n");
    type = 'a';
  }
  match(beg, '[', &rb);
  //printf("rb %d\n",rb);
  int j = -1, i = 1;
  if (type == 'a'){
    for (char *it = (beg+1); it < end; ++it){
      if (*it == '{'){
	j = i;
	break;
	i++;
      }
    }
  }
  if (j > 0){
    dicel = 1;
    for (char *it=(beg+j-1); it> beg;--it){
      if ((*it != ' ') || (*it != '\t') || (*it!= '\r') || (*it != '\n') ){
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
  Index indout = {-1,-1};
  if (dicel == 1){
    while( j < (len-1) && stop){
      icol = 0;
      match(beg+j, '{', &index);
      //printf("j is %d and index is \t %c \n",j,st[j+index]);
      if (nel == fun(cind)){
	//cout = NULL;
	//int ncount = 0;
	//cout = (char *)malloc(index+2);
	//for (int i=j;i<=(j+index);++i){
	  //printf("%c",st[i]);
	//  cout[ncount] = st[i];
	//  ncount++;
	//}
	//cout[index+1] = '\0';
	indout.findex = j;
	indout.lindex = j + index;
	//printf("first index %c\n",*(beg+j));
	//printf("last index %c\n",*(beg+j + index));
	stop = 0;
      }
      //printf("\n");
      for (int i=(j+index+1);i < (len-1);++i){
	if (*(beg+i) == ','){
	  first = j;
	  last = i;
      	  j = i;
	  icol = 1;
	  break;
	}
      }
      nel++;
      if (icol == 0) break;
      for (int i=(j+1);i < (len-1);++i){
	if (*(beg+i) == '{'){
	  j = i;
	  break;
	}
      }
    }
    //printf("number of elements is %d\n",nel);
  }
  index = -1;
  icol  = -1;
  nel   = 0;
  j = 1;
  first = 1;
  last  = 1;
  stop = 1;
  if (dicel == 0 ){
    while( (j < (len-1)) && stop){
      icol = 0;
      for (int i=j;i < (len-1);++i){
	if (*(beg+i) == ','){
	  first = j;
	  last = i;
	  j = (i+1);
	  icol = 1;
	  break;
	}
      }
      if (icol == 0 && nel == 0){
	if (nel == fun(cind)){
	  indout.findex = first;
	  indout.lindex = last;
	  stop = 0;
	}
      }

      if (icol == 0 && nel > 0){
	first = last +1;
	last = rb -1;
	//printf("here2 %d\t %d\n",last,first);
	if (nel == fun(cind)){
	  indout.findex = first;
	  indout.lindex = last;
	  stop = 0;
	}
      }

      if (icol == 1){
	//printf("here3 %d\t %d\n",last,first);
	if (nel == fun(cind)){
	  indout.findex = first;
	  indout.lindex = last -1;
	}
	stop = 0;
      }
    }
      nel++;
      //printf("j is %d\n",j);
  }
    //printf("number of elements is %d\n",nel);
  return indout;
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
      match(&st[j], '{', &index);
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
  
  char c[]  = "[{[{}]},{[{}]}]";
  char cd[] = "[10,20]";
  
  //array_explode(c);
  //array_explode(cd);
  printf("%s\n",array_value(c,"2"));
  printf("%s\n",array_value(cd,"2"));
    
  return 0;

}
#endif
