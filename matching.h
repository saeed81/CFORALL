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
