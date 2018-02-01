#include<stdio.h>
#include<stdlib.h>


void fulltrim(char *str){

  char *tmp = str;

  int ne =0;
  while(*str != '\0'){
    if (*str != ' '){
      *(tmp+ne) = *str;
      ne++;
    }
    str++;
  }
  
  *(tmp+ne) = '\0';

  printf("nonempty string %d\n",ne);
  printf("trimmed string %s\n",tmp);
  
  str = tmp;
}

char *trimStr(char *str){
  
  char *tmp = str;

  printf("input string %s\n",str);
  
  int nc = 0;

  while(*tmp!='\0'){
    if (*tmp != ' '){
      nc++; 
    }
    tmp++;
  }
  printf("total nonempty characters are %d\n",nc);

  char *trim = NULL;
  
  trim = malloc(sizeof(char)*(nc+1)); 

  if (trim == NULL) return NULL;

  tmp = str;

  int ne = 0;

  while(*tmp!='\0'){
    if (*tmp != ' '){
      trim[ne] = *tmp;
      ne++; 
    }
    tmp++;
  }
  trim[nc] = '\0';

  printf("trimmed string is %s\n",trim);

  return trim;
}


int main(void){
  
  char str[] = " s ta ck ove r fl o w  ";

  char *trim = trimStr(str);
  
  if (trim != NULL )free(trim);

  char name[] = " s a e ";

  fulltrim(name);

  printf("%s\n",name);
  
  return 0;
}
