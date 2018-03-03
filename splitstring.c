#include<stdio.h>
#include<stdlib.h>

char **split(char *st, char delim, int *NF){
  
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
  *NF = (nc+1);
  //printf("number of delimiter %c in string is %d\n",delim,nc);
  char **cout = NULL;
  int ni = 0;
  int nj = -1;
  char *tt = st;
  if (nc > 0){
    cout = (char **) malloc(sizeof(char *)*(nc+1));
    temp = st;
    while(*temp != '\0'){
      if ( *temp == delim){
	nj++;
	cout[nj] = (char *)malloc(sizeof(char) *(ni+1));
	for (int i=0; i <ni;++i){
	  cout[nj][i] = *tt;
	  tt++;
	}
	cout[nj][ni] = '\0';
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
  nj = 0;
  ni = 0;
    
  while(*temp != '\0'){
      if ( *temp == delim){
	nj++;
	if (nj == nc){
	  tt = temp;
	  ni = 0;
	  tt++;
	  while(*tt != '\0'){
	    tt++;
	    ni++;
	  }
	  cout[nc] = (char*)malloc(sizeof(char)*(ni+1));
	  tt = temp;
	  ni = 0;
	  tt++;
	  while(*tt != '\0'){
	    cout[nc][ni] = *tt;
	    tt++;
	    ni++;
	  }
	  cout[nc][ni] = '\0';
	}
      }
      temp++;
  }
  return cout;
}
  
int main(void){
  
  int NF = 0;
  int NFF = 0;

  char str1[] ="t=time_counter";
  char **cout1 = split(str1,'=',&NF);

  for (int i=0; i < NF;++i){
    printf("%s\n",*(cout1+i));
  }

  char str[] ="t=time_counter&lat=latetitude&lon=longitude&z=level";
  char **cout = split(str,'&',&NF);

  for (int i=0; i < NF;++i){
    printf("%s\n",*(cout+i));
    char **coutt = split(*(cout+i),'=',&NFF);
    for (int j=0; j < NFF;++j){
      printf("%s\t",*(coutt+j));
    }
    printf("\n");
  }

  FILE *fin = fopen("config.dat","r");
  
  int nc = 0;
  while(!feof(fin)){
    char c = fgetc(fin);
    if (c == '\n') break;
      nc++;
  }

  printf("number of character in the file %d\n",nc);
  rewind(fin);

  char *fcontent = (char*)malloc(sizeof(char)*(nc+1));

  for (int i=0; i < nc;++i) fcontent[i] = ' ';

  fcontent[nc] = '\0';
 
  nc = 0;
  
  while(!feof(fin)){
    char c = fgetc(fin);
    if (c == '\n') break;
    fcontent[nc] =c;  
    printf("%c",fcontent[nc]);
    nc++;
  }
  printf("\n");
  fcontent[nc] = '\0';
  
  fclose(fin);

  
  NF = 0;
  NFF = 0;
  cout = NULL;
  cout = split(fcontent,'&',&NF);

  printf("%d NF\n",NF);

  for (int i=0; i < NF;++i){
    char **coutt = split(*(cout+i),'=',&NFF);
    for (int j=0; j < NFF;++j){
      printf("%s\t",*(coutt+j));
    }
    printf("\n");
  }

  return 0;
}
