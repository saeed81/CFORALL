#include<stdio.h>
#include<stdlib.h>

char **split(char *st, char delim){
  
  int nc= 0;

  char *temp = st;

  while(*temp != '\0'){
    if ( *temp == delim){
      nc++;
      temp++;
    }
    else{
      temp++;
    }
  }

  printf("number of delimiter %c in string is %d\n",delim,nc);
  
  char **cout = NULL;

  if (nc > 0){
    cout = (char **) malloc(sizeof(char *)*(nc+1));
    int ni = 0;
    temp = st;
    char *tt = st;
    int nj = -1;
    while(*temp != '\0'){
      if ( *temp == delim){
	nj++;
	cout[nj] = (char *)malloc(sizeof(char) *ni);
	for (int i=0; i <ni;++i){
	  cout[nj][i] = *tt;
	  tt++;
	}
	ni=0;
	temp++;
	tt++;
      }
      else{
	temp++;
	ni++;
      }
    }
  }

  temp = st;
  int nj = 0;
  int ni = 0;
    
  while(*temp != '\0'){
      if ( *temp == delim){
	nj++;
	if (nj == nc){
	  char *tt = temp;
	  ni = 0;
	  while(*++tt != '\0'){
	    ++ni;
	  }
	  cout[nc] = (char*)malloc(sizeof(char)*ni);
	  tt = temp;
	  ni = 0;
	  while(*++tt != '\0'){
	    cout[nc][ni] = *tt;
	    ++ni;
	  }
	}
      }
      temp++;
  }
  
  return cout;
}
  
int main(void){
  
  char str[] ="time,lat,lon,lev,var,dim";

  char **cout = split(str,',');

  printf("%s\n",*cout);
  printf("%s\n",*(cout+1));
  printf("%s\n",*(cout+2));
  printf("%s\n",*(cout+3));
  printf("%s\n",*(cout+4));
  printf("%s\n",*(cout+5));
  return 0;
}
