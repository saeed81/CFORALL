#ifndef MATCHING_H
#define MATCHING_H

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

  for (int i=0; i < nel; ++i){
    tmp++;
  }
  for (int i=1; i < nel; ++i){
    fstr++;
  }

  int n = len;
  printf("size str is %d\n",n);
  n--;
  printf("size str is %d\n",n);
  int *iloc = (int *)malloc(n*sizeof(int));
  for (int i=0; i < n; ++i ){
    iloc[i] = -1;
  }

  int nl    = -1;
  int nlt   = 0;
  int exist = 0;
  while(*tmp != '\0'){
    if (*tmp == rsymbol){
      printf("we reach %c at %d we do backward search now to find %c \n",rsymbol,nel,lsymbol);
      char *ltm = tmp;
      ltm--;
      nlt = (nel -1);
      exist = 0;
      while (ltm != fstr){
	if (*ltm == lsymbol){
	  printf("we found corresponding %d%c\n",nlt,lsymbol);
	  nl++;
	  if (nl==0) {
	    iloc[nl] = nlt;
	    //break;
	  }
	  else{
	    for (int i=0; i< n;++i){
	      if (iloc[i] == nlt ){
		exist = 1;
		break;
	      }
	    }
	    if (!exist) iloc[nl] = nlt;
	  }
	}
	ltm--;
	nlt--;
      }
    }
    tmp++;
    nel++;
  }
   
  printf("\n");
  
  #if 0
  for(int i=0; i < n; ++i){
    printf("%i \n", iloc[i]);
  }
  #endif 

  int npr = 0;

  for(int i=0; i <n; ++i ){
    if (str[i] == rsymbol){
      npr++;
    }
  }
  printf("number of npr is %d \n", npr);

  int nm= 0;

  for(int i=0; i <n; ++i ){
    if (iloc[i] > 0 ){
      nm++;
      if ((iloc[i+1]) < 0 && (i <=(n-2))){
	break;
      }
    }
  }
  printf("number of internal match is %d \n", nm);

  npr = 0;
  int imatch = 0;
  nm++;
  for(int i=(element-1); i <n; ++i ){
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
