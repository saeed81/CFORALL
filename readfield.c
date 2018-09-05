#include<stdio.h>
#include<stdlib.h>

int whitespace(char c){
  if ((c == '\n') || (c == '\r') || (c == '\v') || (c == '\f') || (c == '\t') || (c == ' ')) return 1;
  return 0;
}

int main(void){

  FILE *fin = NULL;
  fin = fopen("somedata","r");
  fseek(fin,0,SEEK_END);
  long int fs = ftell(fin);
  fseek(fin,0,SEEK_SET);
  char *content = (char *)malloc((fs+1)*sizeof(char));
  content[fs] = '\0';
  fread(content,1,fs,fin);
  fclose(fin);
  int nonwhite = 0;
  for (long int i=0; i < fs;++i){
    if (!whitespace(content[i])){
      nonwhite++;
    }
    if (content[i] == '\n' ){
      printf("%d number of nonwhite\n",nonwhite);
      nonwhite = 0;
    }
  }
  int nfield = 0;
  int nline = 0;
  if (fs >= 2){ 
    char *tmp = (char *)&content[1];
    while(*tmp != '\0'){
      char *bef = tmp -1;
      if (!whitespace(*bef) && whitespace(*tmp) ) nfield++;
      if (*tmp == '\n'){
	nline++;
	printf("number of field in line %d is %d\n", nline,nfield);
	nfield = 0;
      }
      tmp++;
    }
  }
  
  free(content);
  return 0;
}
    
    
  

  
  

  
  


