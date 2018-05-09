#include<stdio.h>
#include<stdlib.h>
#include"matching.h"

int getLen(char *str){

  int len = 0;
  while(*str++){
    len += 1;
  }
  return len;
}

int find(char *reg, char *str, int *first, int *last){

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
      *first = j;
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
	*last = (k-1);
	break;
      }
      else{
	//printf("no instance found we continue searching\n");
      }
    }
  }
  return result;
}

int Strcmp(char *s1, char *s2){
  
  int i = 0;
  int ns1 = 0, ns2 = 0;
  char *t1 = s1, *t2 = s2;
  while (*t1 != '\0'){
    ns1++;
    t1++;
  }
  while (*t2 != '\0'){
    ns2++;
    t2++;
  }
  
  if (ns2 != ns1) return i;

  t1 = s1;
  t2 = s2;
  while (*t1 != '\0'){
    if (*t1 != *t2) i = -1;
    t1++;
    t2++;
  }
  if ( i < 0 ) return 0;
  
  return 1;
}
 
int main(int argc, char *argv[]){

  FILE *inp = NULL;

  inp = fopen(argv[1],"r");

  if (inp == NULL) return 1;

  fseek(inp,0,SEEK_END);

  long int fs = ftell(inp);

  rewind(inp);

  char *content = (char *)malloc((fs+1) * sizeof(char));

  fread(content,1,fs,inp);

  fclose(inp);

  content[fs] = '\0';

  printf("file size is %ld\n",fs);
  printf("content is %s\n",content);

  int first = -1, last = -1;

  printf("%d\n",find("\"startdate\"",content,&first,&last));

  printf("%d\n",first);
  printf("%d\n",last);

  printf("key=>");
  for (int i=first;i<=last;++i)printf("%c",content[i]);

  int incol = -1;
  for (int i=(last+1);i < fs;++i){
    if (content[i] == ':'){
      incol = i;
      break;
    }
  }
  int ifkey = (incol+1);
  int iekey = -1;
  for (int i=(incol+1); i< fs;++i){
    if (content[i] == ','){
      iekey = (i-1);
      break;
    }
  }
  printf("\n");
  printf("value=>");
  for (int i=ifkey;i<=iekey;++i)printf("%c",content[i]);
  printf("\n");

  free(content);

  return 0;

}

