#include<stdio.h>
#include<stdlib.h>


char **splitstr(char *str,char delim, int *NF){
  char *tmp = str;
  int ncount = 0;
  while(*tmp != '\0'){
    if (*tmp == delim){
      ncount++;
    }
    tmp++;
  }
  char **cout = NULL;
  cout = (char **)malloc((ncount+1)*sizeof(char *));
  tmp = str;
  ncount=0;
  char *cc = NULL;
  cc = tmp;
  int nc=0;
  while(*tmp != '\0'){
    if (*tmp == delim){
      for (char *ck=cc;ck<tmp;ck++){
	nc++;
      }
      cout[ncount] = (char*)malloc(nc+1);
      nc=0;
      for (char *ck=cc;ck<tmp;ck++){
	cout[ncount][nc++] = *ck;
      }
      cout[ncount][nc] = '\0';
      ncount++;
      cc = tmp + 1;
    }
    tmp++;
  }
  tmp = cc;
  nc=0;
  while(*tmp++)nc++;
  cout[ncount] = (char*)malloc(nc+1);
  nc=0;
  while(*cc != '\0'){
    cout[ncount][nc++] = *cc;
    cc++;
  }
  cout[ncount][nc] = '\0';
  *NF = ncount;
  return cout;
}
  
int main(void){
  char *str = "80:70:60:50:40:30:20:10:00:wwwww:ssssss:777777:********";
  int NF = 0;
  char **cout = splitstr(str,':', &NF);
  for (int i=0; i <= NF;++i){
    printf("%s\n",cout[i]);
  }
  free(cout);
  return 0;
}
  
  
