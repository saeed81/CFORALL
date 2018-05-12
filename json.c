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

  long int jlf = jf, jle = -1; 
  long int klf = 0 , kle = 0 ; 
  
  char element[2048] = {'\0'};
  int nc = -1;
  int nk = -1;
  int stop = 0;
  long int ncount = 0;
  for (long int i=jf; i <=je; ++i) {
    if (content[i] == ':'){
      /*for (int j = (i+1); j <=je; ++j){
	if (content[j] == ','){
	  jle = j;
	  break;
	}
      }
      */
      if (ncount == 0) jlf = jf;
      //we need to check if this : is inside of dictionary
      for (int j = jlf; j < i; ++j){
	nc++;
	element[nc] = content[j];
      }
      for (int ii=0; ii <= nc; ++ii){
	printf("%c",element[ii]);
      }
      printf("\n");
      //printf("jlf is now %d\n",jlf);
      for (int ii=0; ii < 2048; ++ii){
	element[ii] = '\0';
      }
      for (int j=(i+1);j<= (jle-1);++j){
	if (content[j] == '{'){
	  //printf("it seems like there is a dictionary around , at %d\n",j);
	  break;
	}
      }
      for (int j=(i+1);j<= (jle-1);++j){
	if (content[j] == '}'){
	  //printf(" , is not in a dictory %d\n",j);
	  break;
	}
      }

      //we test if , is inside of dictionary or not
      #if 0
      stop = 1;
      for (int j=(i+1);j<= (jle-1) && !stop;++j){
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
      #endif
      //now lets find the end of dictionary
      //if (stop == 0) jlf = jle;
      //printf("jlf is %d",jlf);
      jlf = (jle +1);
      ncount++;
    }
    nc = -1;
    //printf("\n");
  }
  printf("\n");
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

  fseek(inp,0,SEEK_SET);

  char *content = (char *)malloc((fs+1) * sizeof(char));

  fread(content,1,fs,inp);

  fclose(inp);

  content[fs] = '\0';

  printf("file size is %ld\n",fs);
  //printf("content is %s\n",content);

  int first = -1, last = -1;

  printf("%d\n",find("\"2017020803\"",content,&first,&last));

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
  
  if (incol == -1)return 1;
  
  int ka = incol, kb = -1, kc = -1;
 
  
  if (ka >= 0){
    for (int i=(ka+1); i < fs; ++i){
      if (content[i] == '{'){
	kb =  i;
	break;
      }
    }
  }
  //check what is between : and {
  
  printf("kb is %d \n",kb);
  
  if (kb >= 0 ){
    int stop = 0; 
    for (int i=(kb-1); i >(ka) ; --i){
      if (content[i] != ' '){
	printf("there is soemthing before {. Now we search for ,\n");
	stop = 1;
	break;
      }
    }
    if (stop){
      for (int i=(ka+1); i < (kb) ; ++i){
	if (content[i] == ','){
	  printf("we found ,\n");
	  kc = i;
	  break;
	}
      }
      for (int i=(ka+1); i < (kc) ; ++i){
	printf("%c",content[i]);
      }
    }
    else {

      char *tmp = &content[kb];
      int index = -1;
      match(tmp, 1, (fs-kb+1),'{', &index);
      printf("match { is at index %d and kb + index %d\n",index, kb +index);
      printf("value=>\n");
      for (int i=(kb); i <= (kb+index) ; ++i){
	printf("%c",content[i]);
      }
    }
  }
  else{
    for (int i=(ka+1); i < fs; ++i){
      if (content[i] == ','){
	kc =  i;
	break;
      }
    }
    if ( kc < 0) {
      printf("kc is < 0 value=>\n");
      for (int i=(ka+1); i < (fs-1) ; ++i){
	printf("%c",content[i]);
      }
    }
    else{
      printf("kc > 0 value=>\n");
      for (int i=(ka+1); i < kc ; ++i){
	printf("%c",content[i]);
      }
    }
  }
  
  printf("\n");
  #if 0
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
  #endif

  free(content);

  return 0;

}
