#include<stdio.h>
#include<stdlib.h>

int pow10(int n){
  int d = 1;
  if (n > 0){ 
    for (int i=0; i < n;++i) d *= 10;
  }
  return d;
}

int stoi(char *st){

  int nc=0;
  char *temp = st;

  while (*temp != '\0' ){
    nc++;
    temp++;
  }
  nc--;
  int d = 0;
  int c = 1;
  while (*st != '\0'){
    if (*st == '-'){
      c = -1;
      nc--; 
      st++;
    }
    else if (*st == '+'){
      c = 1;
      nc--; 
      st++;
    }
    else {
      d += ((int)(*st - '0')*pow10(nc));
      st++;
      nc--;
    }
  }

  return (c*d);
}

int main(void){

  char str[] = "+86";

  printf("%d\n",stoi(str));

  return 0;
}
  
