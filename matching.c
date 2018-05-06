#include<stdio.h>
#include<stdlib.h>


int main(void){

  char str[] = "(((())))";
  char *tmp = str;
  char *fstr = str;
  int nel = 1; //element number 1 based not zero 
  
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

  int nl = -1;
  int nlt = 0;
  int exist = 0;
  while(*tmp != '\0'){
    if (*tmp == ')'){
      printf("we reach ) at %d we do backward search now to find ( \n",nel);
      char *ltm = tmp;
      ltm--;
      nlt = (nel -1);
      exist = 0;
      while (ltm != fstr){
	if (*ltm == '('){
	  printf("we found corresponding %d(\n",nlt);
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
    if (str[i] == ')'){
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
    if (str[i] == ')'){
      npr++;
      if (npr == nm) imatch = i;
    }
  }
  printf("number of npr is %d \n", npr);
  printf("position of the match is at  %d \n", imatch);


  free(iloc);
  return 0;

}


