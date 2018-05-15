#ifndef MATCHING_H
#define MATCHING_H

int checksymbolbeforeparse(char *str){

  char *tmp = str;

  char lsymbols[4] = {'{','(','[','\0'};
  char rsymbols[4] = {'}',')',']','\0'};
  int nr[4] = {-1,-1,-1,-1};
  int nl[4] = {-1,-1,-1,-1};
  
 
  for (int i=0; i < 3 ; ++i){
    tmp = str;
    while (*tmp != '\0'){
      if (*tmp == lsymbols[i]){
	nl[i] += 1 ;
      }
      tmp++;
    }
  }
  
  for (int i=0; i < 3 ; ++i){
    tmp = str;
    while (*tmp != '\0'){
      if (*tmp == rsymbols[i]){
	nr[i] += 1 ;
      }
      tmp++;
    }
  }
  
  int iok = 0;

  for (int i= 0; i < 3; ++i){
    if (nr[i] == nl[i] ) iok += 1;
  }
  
  if (iok != 3) return 1;
  
  return 0;
}

int checkforquote(char *str){
  
  char *tmp = str;
  int exist = 0;
  if (*tmp == '\"') exist++;
  while (*tmp != '\0'){
    tmp++;
  }
  tmp--;
  if (*tmp == '\"') exist++;
  
  if (exist == 2 ) return 0;
  
  return 1;
}
char *addquote(char *str){
  
  char *tmp = str;
  int exist = 0;
  int len   = 0;
  
  while (*tmp != '\0'){
    tmp++;
    len++;
  }
  char *reg = NULL;
  int n = 0;

  //printf("string  %s with the length of %d has no quote character. We will add to it \n",str, len);
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
  //printf("n is %d \n",n);
  *reg = '\"';
  reg++;
  *reg='\0';
  reg = trg;
  //printf("reg is %s \n",reg);
  
  trg = reg;
  len = 0;
  while (*trg != '\0'){
    trg++;
    len++;
  }
  //printf("string  %s with the length of %d has quote character. We will add to it \n",str, len);
  
  return reg;
}

void match(char *str, int element, int len, char lsymbol, int *index){

  char rsymbol = '0';

  switch (lsymbol){
  case '{':
    rsymbol = '}';
    break;
  case '(':
    rsymbol = ')';
    break;
  case '[':
    rsymbol = ']';
    break;
  default:
    break;
  }

  int openPose = (element-1);
  int closePose = openPose ;
  int counter  = 1;
  char c = ' ';
  while (counter > 0) {
    c = str[++closePose];
    if (c == lsymbol) {
      counter++;
    }
    else if (c == rsymbol) {
      counter--;
    }
    if (counter == 0) break;
  }
  
  //printf("closePos is %d\n", closePose);

  *index = closePose;

  return;

}

#endif
