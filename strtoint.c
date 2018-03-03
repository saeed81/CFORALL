#include<stdio.h>
#include<stdlib.h>


int pow10(int n){
  int d = 1;
  if (n > 0){ 
    for (int i=0; i < n;++i) d *= 10;
  }
  return d;
}


int strtoi(char *st){

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
      printf("%d\n",nc);
    }
    else {
      d += ((int)(*st - '0')*pow10(nc));
      st++;
      nc--;
      printf("%d\n",nc);
    }
  }

  return (c*d);
}



int main(void){

  char str[] = "-865439";

  int a = (int)(str[1] - '0');
  int b = (int)(str[2] - '0');
  
  printf("%d\n",a);
  printf("%d\n",b);
  printf("%d\n",-(10 * a + b));

  printf("%d\n",strtoi(str));

  return 0;
}
  
