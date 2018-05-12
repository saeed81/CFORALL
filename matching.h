#ifndef MATCHING_H
#define MATCHING_H

int checksymbolbeforeparse(char *str){

  char *tmp = str;

  char lsymbols[4] = {'{','(','[','\0'};
  char rsymbols[4] = {'}',')',']','\0'};
  int nr[4] = {-1,-1,-1,-1};
  int nl[4] = {-1,-1,-1,-1};
  
 
  for (int i=0; i < 3 ; ++i){
    tmp = str;
    while (*tmp != '\0'){
      if (*tmp == lsymbols[i]){
	nl[i] += 1 ;
      }
      tmp++;
    }
  }
  
  for (int i=0; i < 3 ; ++i){
    tmp = str;
    while (*tmp != '\0'){
      if (*tmp == rsymbols[i]){
	nr[i] += 1 ;
      }
      tmp++;
    }
  }
  
  int iok = 0;

  for (int i= 0; i < 3; ++i){
    if (nr[i] == nl[i] ) iok += 1;
  }
  
  if (iok != 3) return 1;
  
  return 0;
}

void match(char *str, int element, int len, char lsymbol, int *index){

  char rsymbol = '0';

  switch (lsymbol){
  case '{':
    rsymbol = '}';
    break;
  case '(':
    rsymbol = ')';
    break;
  case '[':
    rsymbol = ']';
    break;
  default:
    break;
  }

  char *tmp  = str;
  char *fstr = str;
  int nel    = element; //element number 1 based not zero
  
  int nsym = 0;

  while(*tmp != '\0'){
    if ( *tmp == lsymbol) nsym++;
    tmp++;
  }

  tmp = str;
 
  printf("tmp pointer is %c\n", *tmp);
  printf("in total we have %d %c\n", nsym,lsymbol);

  for (int i=1; i < nel; ++i){
    tmp++;
  }
  for (int i=1; i < nel; ++i){
    fstr++;
  }

  int n = nsym;
  printf("size str is %d\n",n);
  int *iloc = (int *)malloc(nsym*sizeof(int));
  for (int i=0; i < nsym; ++i ){
    iloc[i] = -1;
  }

  int nl    = -1;
  int nlt   = 0;
  int exist = 0;
  int stop = 0, notfound = 0;
  char *ltm = NULL;
  while(*tmp != '\0' && (notfound == 0)){
    if (*tmp == rsymbol){
      printf("we reach %c at %d we do backward search now to find %c \n",rsymbol,(tmp - fstr),lsymbol);
      ltm = tmp;
      ltm--;
      exist = 0;
      notfound = 1; 
      while (ltm > fstr){
	if (*ltm == lsymbol){
	  printf("we found corresponding %d %c\n",(ltm - fstr),lsymbol);
	  for (int i=0; i < n; ++i){
	    if (iloc[i] == (ltm - fstr) ){
	      exist = 1;
	      //notfound += 1;
	      break;
	    }
	  }
	  if(exist == 0){
	    for (int i=0; i < n; ++i){
	      if (iloc[i] < 0 ){
		iloc[i] = ltm - fstr;
		notfound = 0;
		break;
		//notfound = 1;
	      }
	    }
	  }
	  }
	ltm--;
      }
    }
    tmp++;
  }
   
  printf("\n");
  
  #if 1
  for(int i=0; i < n; ++i){
    printf("%i \n", iloc[i]);
  }
  #endif 

  int npr = 0;

  for(int i=(element-1); i <n; ++i ){
    if (str[i] == rsymbol){
      npr++;
    }
  }
  printf("number of %c is %d \n", rsymbol, npr);

  int nm= 0;

  for(int i=0; i <n; ++i ){
    if (iloc[i] > 0 ){
      nm++;
    }
  }
  printf("number of internal match is %d \n", nm);

  
  if (nm == 0) nm++;
  npr = 0;
  int imatch = 0;
  printf("number of internal match is %d \n", nm);
  for(int i=(element-1); i <len; ++i ){
    if (str[i] == rsymbol){
      npr++;
      if (npr == nm) imatch = i;
    }
  }
  *index = imatch;
  
  printf("number of npr is %d \n", npr);
  printf("position of the match is at  %d \n", imatch);


  free(iloc);
  
  return;

}

#endif
