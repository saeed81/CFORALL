#include<stdio.h>
#include<stdlib.h>


char *zpad(char *str, int num){
  
  int len=0;
  char *t = str;

  while(*t != '\0'){
    len++;
    t++;
  }
  len++;
  printf("len is %d\n",len);
  len +=num;
  printf("len is %d\n",len);

  char *tmp = (char *)malloc(len*sizeof(char));
  char *sw = tmp;
  
  while (num--){
    *sw='0';
    printf("%c\n",*sw);
    sw++;
  }

  t = str;

  while(*t!='\0'){
    *sw = *t;
    printf("%c\n",*sw);
    sw++;
    t++;
  }
  *sw = '\0';
  return tmp;
}


int main(void){

  char val[] = "56464646464";

  char *zval = zpad(val,2);

  printf("%s\n",zval);

  free(zval);

  return 0;
}


