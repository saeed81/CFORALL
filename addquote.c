#include<stdio.h>
#include<stdlib.h>


void add_quote(char *str){
  char *tmp = str;
  int exist = 0;
  int len = 0;
  while (*tmp != '\0'){
    if (*tmp == '\"') exist++;
    tmp++;
    len++;
  }
  char *reg = NULL;

  int n = 0;

  if (exist == 0){
    printf("string  %s with the length of %d has no quote character. We will add to it \n",str, len);
    reg = (char *)malloc(len+1+2);
    char *trg = reg;
    *reg = '\"';
    reg++;
    tmp = str;
    while (*tmp != '\0'){
      *reg = *tmp;
      n++;
      tmp++;
      reg++;
    }
    printf("n is %d \n",n);
    *reg = '\"';
    reg++;
    *reg='\0';
    reg = trg; 
    printf("reg is %s \n",reg);
    
    trg = reg;
    len = 0;
    while (*trg != '\0'){
      trg++;
      len++;
    }
    printf("string  %s with the length of %d has quote character. We will add to it \n",str, len);

    free(reg);
  }
}
  



int main(int argc, char *argv[]){

  char *str = "saeed";

  add_quote(str);

  #if 0
  
  char *tmp = str;

  int exist = 0;
  
  int len = 0;
  while (*tmp != '\0'){
    if (*tmp == '\"') exist++;
    tmp++;
    len++;
  }
  char *reg = NULL;

  if (exist == 0){
    printf("string  %s with the length of %d has no quote character. We will add to it \n",str, len);
    reg = (char *)malloc(len+1+2);
    char *trg = reg;
    *reg = '\"';
    reg++;
    tmp = str;
    while (*tmp != '\0'){
      *reg = *tmp;
      tmp++;
      reg++;
    }
    *reg = '\"';
    reg++;
    *reg='\0';
    reg = trg; 
    printf("reg is %s \n",reg);
    free(reg);
  }
#endif
  return 0;
}

