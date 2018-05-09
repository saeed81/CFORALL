#ifndef MATCHING_H
#define MATCHING_H


#define LSYMB '{'
#define RSYMB '}'

void match(char *str,int first, int *last){
  
  char *tmp  = str;
  char *fstr = str;
  int  nel   = first; //element number 1 not an index 
  int  cnel  = nel;   //element number 1 not an index 
  
  for (int i=0; i < nel; ++i){
    tmp++;
  }
  for (int i=1; i < nel; ++i){
    fstr++;
  }

  int n = sizeof(str) / sizeof(*str);
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
    if (*tmp == RSYMB){
      printf("we reach %c at %d we do backward search now to find %c \n",RSYMB,nel,LSYMB);
      char *ltm = tmp;
      ltm--;
      nlt = (nel -1);
      exist = 0;
      while (ltm != fstr){
	if (*ltm == LSYMB){
	  printf("we found corresponding %d%c\n",nlt,LSYMB);
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

  for(int i=0; i < n; ++i){
    printf("%i \n", iloc[i]);
  }

  int npr = 0;

  for(int i=0; i <n; ++i ){
    if (str[i] == RSYMB){
      npr++;
    }
  }
  printf("number of npr is %d \n", npr);

  int nm= 0;

  for(int i=0; i <n; ++i ){
    if (iloc[i] > 0 ){
      nm++;
    }
  }
  printf("number of internal match is %d \n", nm);

  npr = 0;
  int imatch = 0;
  nm++;
  for(int i=0; i <n; ++i ){
    if (str[i] == RSYMB){
      npr++;
      if (npr == nm) imatch = i;
    }
  }
  *ilast = imatch;
  
  printf("position of the match for %c is at  %d %c\n", str[cnel-1],imatch,str[imatch]);

  free(iloc);
  
  return;

}

#endif
