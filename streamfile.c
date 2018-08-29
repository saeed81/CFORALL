#include<stdio.h>
#include<stdlib.h>


int whitespace(char c){
  if ((c == '\n') || (c == '\r') || (c == '\v') || (c == '\f') || (c == '\t') || (c == ' ')) return 1;
  return 0;
}

int main(int argc, char *argv[]){

  if (argc != 2 ) return 1;

  FILE *fin = fopen(argv[1],"r");

  int c  =  0;
  int nf = 0;
  int nl = 0;
  int cb = 0;
  int count = 0;
  int donefield = 0;
  while ((c=fgetc(fin)) != EOF){
    if ((count >0) && whitespace(c) && !whitespace(cb) && (donefield == 0)){
      nf+=1;
    }
    cb = c;
    count++;
    if (c == '\n'){
      donefield = 1;
      nl++; 
    }
  }

  printf("Number of filelds nf is %d \n",nf);
  printf("Number of lines   nl is %d \n",nl);

  fclose(fin);

  return 0;
}
  
  

