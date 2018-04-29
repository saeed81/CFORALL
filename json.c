#include<stdio.h>
#include<stdlib.h>


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
 
void get(char *content, long fs, char *key, char *value){

  long int  jf = -1, je = -1;
 
  for (long int i=0; i < fs; ++i){
    if (content[i] == '{') {
      jf = i;
      break;
    }
  }

  for (long int i=(fs-1); i >= 0; --i){
    if (content[i] == '}'){
      je = i;
      break;
    }
  }
 
  printf("first occurance of { is at position %ld \n", jf);
  printf("first occurance of } is at position %ld \n", je);


  for (long int i=0; i < jf; ++i){
    if (content[i] == ':') {
      jf = -1;
      break;
    }
  }

  printf("content[%d] is %c \n", fs -1, content[fs-1]);
  printf("content[%d] is %c \n", fs -2, content[fs-2]);
  printf("content[%d] is %c \n", fs -3, content[fs-3]);
  
  for (long int i=(fs-1); i > je; --i){
    if ((content[i] != ' ') && (content[i] != EOF) && (content[i] != '\n') ){
      je = -1;
      break;
    }
  }
  
  if ( jf == (-1) || je == (-1)) {
    printf("content is not a valid json object\n");
    return;
  }
  
  jf++; 
  je--;

  long int jlf = jf, jle = je; 
  long int klf = 0 , kle = 0 ; 
  
  char element[2048] = {'\0'};
  int nc = -1;
  int nk = -1;
  int stop = 0;
  for (long int i=jf; i <=je; ++i) {
    if (content[i] == ':'){
      for (int j = jlf; j < i; ++j){
	nc++;
	element[nc] = content[j];
      }
      for (int ii=0; ii <= nc; ++ii){
	printf("%c",element[ii]);
      }
      for (int ii=0; ii < 1024; ++ii){
	element[ii] = '\0';
      }
      printf("\n");
      for (int j = (i+1); j <=je; ++j){
	if (content[j] == ','){
	  jle = (j+1);
	  break;
	}
      }
      //we test if , inside of dictionary or not
      stop = 0;
      for (int j=(i+1);j< (jle-1) && !stop;++j){
	if (content[j] == '{'){
	  printf("is a dictionary starts at %d\n",j);
	  for (int k=(j+1); k <=je; ++k){
	    if (content[k] == '}'){
	      printf("end of this dictionary is at %d\n",k);
	      klf = (k+1);
	      jlf = klf;
	      stop = 1;
	      break;
	    }
	  }
	}
      }
      //now lets find the end of dictionary
    }
    if (stop == 0) jlf = jle; 
    nc = -1;
    printf("\n");
    printf("jlf is %d \n",jlf);
  }
  return;
}

void extract(char *content, long fs, char *key, char *value){

  long int  jf = -1, je = -1;
 
  for (long int i=0; i < fs; ++i){

    if (content[i] == '{') {
      jf = i;
      break;
    }
  }

  for (long int i=(fs-1); i >= 0; --i){

    if (content[i] == '}'){
      je = i;
      break;
    }
  }
  
  if ( jf == (-1) || je == (-1)) {
    printf("content is not a valid json object\n");
    return;
  }
  
  printf("first occurance of { is at position %ld \n", jf);
  printf("last occurance of } is at position %ld \n", je);

  jf++; 
  je--;

  long int jlf = jf, jle = je; 

  char element[1024] = {'\0'};
  int nc = -1;

  for (long int i=jf; i <=je; ++i) {
    if (content[i] == ','){
      for (int j = jlf; j < i; ++j){
	if (content[j] == ':') { 
	  break;
	}else{
	  nc++;
	  element[nc] = content[j];
	}
      }
      for (int ii=0; ii < nc; ++ii){
	printf("%c",element[ii]);
      }
      for (int ii=0; ii < 1024; ++ii){
	element[ii] = '\0';
      }
      nc = -1;
      printf("\n");
      jlf = ++i;
    }
  }
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

  get(content,fs,NULL,NULL);
  
  free(content);

  return 0;

}

