#include<stdio.h>
#include<stdlib.h>
#include"matching.h"
#include<stdarg.h>

int getLen(char *str){

  int len = 0;
  while(*str++){
    len += 1;
  }
  return len;
}

int iswhitespace(char c){
  if ( (c == ' ') || (c == '\t') || ( c == '\n') || (c == '\r')){
    return 1;
  }
  
  return 0;
}

void typevalue(char *ar, int findex, int lindex){

  if (ar[findex] == '[' && ar[lindex] == ']'){
    printf("value is array\n");
  }
  else if (ar[findex] == '{' && ar[lindex] == '}'){
    printf("value is dictionary\n");
  }
  else{
    printf("value is either string or float");
  }
  
  return;
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
 
char *json_load(char *filename){

  FILE *inp = NULL;

  inp = fopen(filename,"r");

  if (inp == NULL) return NULL;

  fseek(inp,0,SEEK_END);

  long int fs = ftell(inp);

  fseek(inp,0,SEEK_SET);

  char *content = NULL;
  
  content = (char *)malloc((fs+1) * sizeof(char));

  fread(content,1,fs,inp);

  fclose(inp);

  content[fs] = '\0';
  
  if (checksymbolbeforeparse(content) != 0){
    free(content);
    content = NULL;
  }

  return content;
}

void getvalue(char *content, char *key,...){

  if (content == NULL) return; 
  
  char *str = content;
  long int fs = 0L;
  while(*str != '\0'){
    fs++;
    str++;
  }
  fs++;

  va_list vs;

  va_start(vs,key);

  char *tmp = NULL;
  char *quotekey = NULL;
  
  if ( checkforquote(key)) {
    quotekey = addquote(key);
  }
  else{
    quotekey = key;
  }
  
  int first = -1, last = -1;
  find(quotekey,content,&first,&last);

  if ( first == (-1) || last == (-1)){
    printf("%s does not exist in the file \n",quotekey);
    return;
  }

  printf("key=>");
  for (int i=first;i<=last;++i)printf("%c",content[i]);

  int incol = -1;
  for (int i=(last+1);i < fs;++i){
    if (content[i] == ':'){
      incol = i;
      break;
    }
  }
  
  if (incol == -1)return;
  
  int ka = incol, kb = -1, kc = -1;
  int findex = -1;
  int lindex = -1;
  
  if (ka >= 0){
    for (int i=(ka+1); i < fs; ++i){
      if (content[i] == '{' || content[i] == '['){
	kb =  i;
	break;
      }
    }
  }
  //check what is between : and {
  //printf("kb is %d \n",kb);
  if (kb >= 0 ){
    int stop = 0; 
    for (int i=(kb-1); i >(ka) ; --i){
      if (iswhitespace(content[i]) == 0){
	//printf("there is something before {. Now we search for ,\n");
	stop = 1;
	break;
      }
    }
    if (stop){
      for (int i=(ka+1); i < (kb) ; ++i){
	if (content[i] == ','){
	  //printf("we found ,\n");
	  kc = i;
	  break;
	}
      }
      //printf("block 1 value=>\n");
      findex = (ka+1);
      lindex = (kc-1);
      for (int i=(ka+1); i < (kc) ; ++i){
	if (content[i] == '}'){
	  //printf("%c",content[i]);
	  lindex = (i-1);
	  break;
	}
      }
    }
    else{
      char *tmp1 = &content[kb];
      int index = -1;
      if (content[kb] == '{')match(tmp1, 1, (fs-kb+1),'{', &index);
      if (content[kb] == '[')match(tmp1, 1, (fs-kb+1),'[', &index);
      //printf("match { is at index %d and kb + index %d\n",index, kb +index);
      //printf("block 2 value=>\n");
      findex = kb;
      lindex = (kb+index);
      for (int i=(kb); i <= (kb+index) ; ++i){
	//printf("%c",content[i]);
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
      //printf("block 3 value=>\n");
      findex = (ka+1);
      lindex = (fs-1-1);
      for (int i=(ka+1); i < (fs-1) ; ++i){
	if (content[i] == '}'){
	  lindex = (i-1);
	  break;
	}
      }
    }
    else{
      //printf("block 4 value=>\n");
      findex = (ka+1);
      lindex = (kc -1);
      for (int i=(ka+1); i < kc ; ++i){
	printf("%c",content[i]);
      }
    }
  }
  int narg = 1;
  printf("\n");
  //first value found we contniue with second one
  //for (int i=findex; i <= lindex ; ++i){
  //	printf("%c",content[i]);
  //}

  printf("narg is %d and key is %s\n",narg,key);
  printf("value is \n");
  for (int i=findex; i <= lindex ; ++i){
    printf("%c",content[i]);
  }
   
  printf("\n");
  typevalue(content,findex,lindex);

  // we find the second value first value would a key now
  tmp = content;
  char *keyt = NULL;
  
  while((key=va_arg(vs,char *)) != NULL){
    keyt = (char *)malloc((lindex-findex+1+1)*sizeof(char));
    int ncount = 0;
    for (int i=findex; i <= lindex ; ++i){
      keyt[ncount]=tmp[i];
      //printf("%c\t%c\n",tmp[i],keyt[ncount]);
      ncount++;
    }
    //ncount++;
    keyt[ncount] = '\0';
    for (int i=0; i < ncount;++i){
      //printf("%c",keyt[i]);
    }
    if ((narg > 1) && (tmp != NULL)) free(tmp);
    
    if ( checkforquote(key) ) {
      quotekey = addquote(key);
    }
    else{
      quotekey = key;
    }
    first = -1, last = -1;
    find(quotekey,keyt,&first,&last);
    fs = (lindex-findex+1+1);
    
    //printf("%d\n",first);
    //printf("%d\n",last);

    if ( first == (-1) || last == (-1)){
      printf("%s does not exist in the file \n",quotekey);
      return;
    }

    //printf("key=>");
    //for (int i=first;i<=last;++i)printf("%c",keyt[i]);

    incol = -1;
    for (int i=(last+1);i < fs;++i){
      if (keyt[i] == ':'){
	incol = i;
	break;
      }
    }
    if (incol == -1)return;
  
    ka = incol, kb = -1, kc = -1;
    findex = -1;
    lindex = -1;
  
    if (ka >= 0){
      for (int i=(ka+1); i < fs; ++i){
	if (keyt[i] == '{' || keyt[i] == '['){
	  kb =  i;
	  break;
	}
      }
    }
  //check what is between : and {
  //printf("kb is %d \n",kb);
  
    if (kb >= 0 ){
      int stop = 0; 
      for (int i=(kb-1); i >(ka) ; --i){
	if (iswhitespace(keyt[i]) == 0){
	//printf("there is something before {. Now we search for ,\n");
	stop = 1;
	break;
      }
    }
    if (stop){
      for (int i=(ka+1); i < (kb) ; ++i){
	if (keyt[i] == ','){
	  //printf("we found ,\n");
	  kc = i;
	  break;
	}
      }
      //printf("block 1 value=>\n");
      findex = (ka+1);
      lindex = (kc-1);
      for (int i=(ka+1); i < (kc) ; ++i){
	if (keyt[i] == '}'){
	  //printf("%c",content[i]);
	  lindex = (i-1);
	  break;
	}
      }
    }
    else{
      char *tmp1 = &keyt[kb];
      int index = -1;
      if (keyt[kb] == '{')match(tmp1, 1, (fs-kb+1),'{', &index);
      if (keyt[kb] == '[')match(tmp1, 1, (fs-kb+1),'[', &index);
      //printf("match { is at index %d and kb + index %d\n",index, kb +index);
      //printf("block 2 value=>\n");
      findex = kb;
      lindex = (kb+index);
      for (int i=(kb); i <= (kb+index) ; ++i){
	//printf("%c",keyt[i]);
      }
    }
  }
  else{
    for (int i=(ka+1); i < fs; ++i){
      if (keyt[i] == ','){
	kc =  i;
	break;
      }
    }
    if ( kc < 0) {
      //printf("block 3 value=>\n");
      findex = (ka+1);
      lindex = (fs-1-1);
      for (int i=(ka+1); i < (fs-1) ; ++i){
	if (keyt[i] == '}'){
	  lindex = (i-1);
	  break;
	}
      }
    }
    else{
      //printf("block 4 value=>\n");
      findex = (ka+1);
      lindex = (kc -1);
      for (int i=(ka+1); i < kc ; ++i){
	printf("%c",keyt[i]);
      }
    }
  }
    printf("\n");
    
    narg++;
    printf("narg is %d and key is %s\n",narg,key);
    printf("value is \n");
    for (int i=findex; i <= lindex ; ++i){
      printf("%c",keyt[i]);
    }
    printf("\n");
    typevalue(keyt,findex,lindex);
    tmp = keyt;
    
  }
  if (keyt != NULL) free(keyt);
  
  return ;
}

#if 0

int main(int argc, char *argv[]){

  if ( argc != 2){
    printf("Usage %s jsonfile key\n", argv[0]);
    return 1;
  }

  char *content = json_load(argv[1]);
  getvalue(content,"server","prod",NULL);
  
  



  #if 0
  char *key      = argv[2];
  char *quotekey = NULL;

  if ( checkforquote(key) ) {
    quotekey = addquote(key);
  }
  else{
    quotekey = key;
  }
  
  int first = -1, last = -1;
  find(quotekey,content,&first,&last);

  //printf("%d\n",first);
  //printf("%d\n",last);

  if ( first == (-1) || last == (-1)){
    printf("%s does not exist in the file \n",quotekey);
    return 1;
  }

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
  int findex = -1;
  int lindex = -1;
  
  if (ka >= 0){
    for (int i=(ka+1); i < fs; ++i){
      if (content[i] == '{' || content[i] == '['){
	kb =  i;
	break;
      }
    }
  }
  //check what is between : and {
  //printf("kb is %d \n",kb);
  if (kb >= 0 ){
    int stop = 0; 
    for (int i=(kb-1); i >(ka) ; --i){
      if (iswhitespace(content[i]) == 0){
	//printf("there is something before {. Now we search for ,\n");
	stop = 1;
	break;
      }
    }
    if (stop){
      for (int i=(ka+1); i < (kb) ; ++i){
	if (content[i] == ','){
	  //printf("we found ,\n");
	  kc = i;
	  break;
	}
      }
      printf("block 1 value=>\n");
      findex = (ka+1);
      lindex = (kc-1);
      for (int i=(ka+1); i < (kc) ; ++i){
	if (content[i] == '}'){
	  //printf("%c",content[i]);
	  lindex = (i-1);
	  break;
	}
      }
    }
    else{
      char *tmp = &content[kb];
      int index = -1;
      if (content[kb] == '{')match(tmp, 1, (fs-kb+1),'{', &index);
      if (content[kb] == '[')match(tmp, 1, (fs-kb+1),'[', &index);
      //printf("match { is at index %d and kb + index %d\n",index, kb +index);
      printf("block 2 value=>\n");
      findex = kb;
      lindex = (kb+index);
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
      printf("block 3 value=>\n");
      findex = (ka+1);
      lindex = (fs-1-1);
      for (int i=(ka+1); i < (fs-1) ; ++i){
	if (content[i] == '}'){
	  lindex = (i-1);
	  break;
	}
      }
    }
    else{
      printf("block 4 value=>\n");
      findex = (ka+1);
      lindex = (kc -1);
      for (int i=(ka+1); i < kc ; ++i){
	printf("%c",content[i]);
      }
    }
  }
  
  printf("\n");
  
  //first value found we contniue with second one
  for (int i=findex; i <= lindex ; ++i){
	printf("%c",content[i]);
  }
  printf("\n");
  typevalue(content,findex,lindex);

  // we find the second value first value would a key now

  char *keyt = (char *)malloc((lindex-findex+1+1));
  int ncount = 0;
  for (int i=findex; i <= lindex ; ++i){
    keyt[ncount]=content[i];
    ncount++;
  }

  free(content);

  keyt[ncount] = '\0';
  
  key = "NS01_GEBCO";
  content = keyt;
  
  if ( checkforquote(key) ) {
    quotekey = addquote(key);
  }
  else{
    quotekey = key;
  }

  first = -1, last = -1;

  find(quotekey,content,&first,&last);

  //printf("%d\n",first);
  //printf("%d\n",last);

  if ( first == (-1) || last == (-1)){
    printf("%s does not exist in the file \n",quotekey);
    return 1;
  }

  printf("key=>");
  for (int i=first;i<=last;++i)printf("%c",content[i]);

  incol = -1;
  for (int i=(last+1);i < fs;++i){
    if (content[i] == ':'){
      incol = i;
      break;
    }
  }
  
  if (incol == -1)return 1;
  
  ka = incol, kb = -1, kc = -1;
  findex = -1;
  lindex = -1;
  
  if (ka >= 0){
    for (int i=(ka+1); i < fs; ++i){
      if (content[i] == '{' || content[i] == '['){
	kb =  i;
	break;
      }
    }
  }
  //check what is between : and {
  //printf("kb is %d \n",kb);
  
  if (kb >= 0 ){
    int stop = 0; 
    for (int i=(kb-1); i >(ka) ; --i){
      if (iswhitespace(content[i]) == 0){
	//printf("there is something before {. Now we search for ,\n");
	stop = 1;
	break;
      }
    }
    if (stop){
      for (int i=(ka+1); i < (kb) ; ++i){
	if (content[i] == ','){
	  //printf("we found ,\n");
	  kc = i;
	  break;
	}
      }
      printf("block 1 value=>\n");
      findex = (ka+1);
      lindex = (kc-1);
      for (int i=(ka+1); i < (kc) ; ++i){
	if (content[i] == '}'){
	  //printf("%c",content[i]);
	  lindex = (i-1);
	  break;
	}
      }
    }
    else{
      char *tmp = &content[kb];
      int index = -1;
      if (content[kb] == '{')match(tmp, 1, (fs-kb+1),'{', &index);
      if (content[kb] == '[')match(tmp, 1, (fs-kb+1),'[', &index);
      //printf("match { is at index %d and kb + index %d\n",index, kb +index);
      printf("block 2 value=>\n");
      findex = kb;
      lindex = (kb+index);
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
      printf("block 3 value=>\n");
      findex = (ka+1);
      lindex = (fs-1-1);
      for (int i=(ka+1); i < (fs-1) ; ++i){
	if (content[i] == '}'){
	  lindex = (i-1);
	  break;
	}
      }
    }
    else{
      printf("block 4 value=>\n");
      findex = (ka+1);
      lindex = (kc -1);
      for (int i=(ka+1); i < kc ; ++i){
	printf("%c",content[i]);
      }
    }
  }
  


  printf("\n");
  //free(content);
  free(keyt);
  #endif
  return 0;

}
#endif
