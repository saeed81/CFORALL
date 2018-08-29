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
  int iposb = 0;
  int ipose = 0;
  int ncur = 0;
  int found = 0;
  int cfirst = 0;
  int cend = 0;
  int nftot = 0;

  while ((c=fgetc(fin)) != EOF){
    if ((count >0) && whitespace(c) && !whitespace(cb)){
      ipose = (count-1);
      nf+=1;
      found = 0;
      cend = cb;
      if (donefield == 0 ) nftot++;
      //printf("first %d \t end %d \n",iposb,ipose);
      if ((nf == 4) && (nl == 1170)){
	int fpos = ftell(fin);
	fseek(fin,iposb,SEEK_SET);
	for (int i=0; i <= (ipose-iposb);++i) printf("%c",fgetc(fin));
	printf("\t");
	fseek(fin,fpos,SEEK_SET);
	printf("\n");
      }
    }
    cb = c;
    count++;
   if (!whitespace(c) && (found == 0)){
     iposb = (count -1);
     found = 1;
     cfirst = c;
    }
   if (c == '\n'){
      donefield = 1;
      nl++; 
      found = 0;
      nf = 0;
   }
  }

  printf("Number of filelds nf is %d \n",nftot);
  printf("Number of lines   nl is %d \n",nl);

  fseek(fin,0,SEEK_SET);
  
  

  fclose(fin);

  return 0;
}
  
  

