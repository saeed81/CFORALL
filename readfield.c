#include<stdio.h>
#include<stdlib.h>

int whitespace(char c){
  if ((c == '\n') || (c == '\r') || (c == '\v') || (c == '\f') || (c == '\t') || (c == ' ')) return 1;
  return 0;
}

int main(int argc, char *argv[]){
  if (argc != 2) return 1;
  FILE *fin = NULL;
  fin = fopen(argv[1],"r");
  fseek(fin,0,SEEK_END);
  long int fs = ftell(fin);
  fseek(fin,0,SEEK_SET);
  char *content = (char *)malloc((fs+1)*sizeof(char));
  content[fs] = '\0';
  fread(content,1,fs,fin);
  fclose(fin);
  
  int nfield = 0;
  int nline = 0;
  char *start;
  char *end;
  int found = 0;

  if (fs >=1){ 
    char *tmp = (char *)&content[0];
    char *bef = tmp;
    if (!whitespace(*bef)){ start = bef; found = 1;}
    while(*tmp != '\0'){
      if (!whitespace(*bef) && whitespace(*tmp)){
	nfield++;
	end = bef;
	found = 0;
	for (char *pt=start; pt <=end;++pt){printf("%c",*pt);}
	printf(" ");
	if (*tmp == '\n'){
	  nline++;
	  printf("number of field in line %d is %d\n", nline,nfield);
	  nfield = 0;
	  found = 0;
	  printf("\n");
	}
      }
      if (whitespace(*bef) && !whitespace(*tmp) && (found == 0)){
	start = tmp;
	found = 1;
      }
      tmp++;
      bef = tmp -1;
    }
  }
  
  free(content);
  return 0;
}
    
    
  

  
  

  
  


