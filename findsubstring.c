#include<stdlib.h>
#include<stdio.h>

int find(char *, char *);
int nfind(char *, char *);
int getLen(char *);

int main(void){

  char *reg = "name";
  char *sen = "my first name is saeed and my user name on github is saeed81. We are searching for substring name in this string";

  printf("strating index of substring in string is  %d\n",find(reg,sen));
  printf("number of substring instances in string is  %d\n",nfind(reg,sen));

  return 0;
}

int getLen(char *str){

  int len = 0;
  while(*str++){
    len += 1;
  }
  //printf("%s%d\n","the size of string is ",len);

  return len;
}

int find(char *reg, char *str){

  int  lnr = getLen(reg);
  int  lns = getLen(str);
  if ( lnr == 0 || lns == 0) return -1;
  if (lnr > lns) return -1;
  
  int i = 0;
  int ncount = 0;
  int k = 0;
  int result = -1;
  int ip = 0;
  for (int j=0; j < lns; ++j){
    i = 0; 
    if (str[j] == reg[i]){
      //printf("we found the first instance of the first character at j %d\n",j);
      //printf("we need to find the other characters\n");
      k  = j+1;
      ip = i + 1; 
      ncount = 1;
	while(str[k] == reg[ip]){
	  ++k;
	  ++ip;
	  ++ncount;
	}
	if (ncount == lnr){
	  //printf("we found the first instance\n");
	  //printf("index is %d\n",j);
	  result = j;
	  break;
	}
	else{
	   printf("no instance found we continue searching\n");
	}
      }
  }
  return result;
}
int nfind(char *reg, char *str){

  int  lnr = getLen(reg);
  int  lns = getLen(str);
  if ( lnr == 0 || lns == 0) return -1;
  if (lnr > lns) return -1;
  
  int i = 0;
  int ncount = 0;
  int k = 0;
  int result = 0;
  int ip = 0;
  for (int j=0; j < lns; ++j){
    i = 0; 
    if (str[j] == reg[i]){
      //printf("we found the first instance of the first character at j %d\n",j);
      //printf("we need to find the other characters\n");
      k  = j+1;
      ip = i + 1; 
      ncount = 1;
	while(str[k] == reg[ip]){
	  ++k;
	  ++ip;
	  ++ncount;
	}
	if (ncount == lnr){
	  //printf("we found the first instance\n");
	  //printf("index is %d\n",j);
	  result++;
	}
	else{
	   printf("no instance found we continue searching please wait\n");
	}

      }
  }
  return result;
}
