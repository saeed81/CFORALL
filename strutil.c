#include<stdio.h>
#include<stdlib.h>


unsigned int lenS(char *s){

  unsigned int nc = 0;

  while(*s != '\0'){
    nc++;
    s++;
  }

  return nc;
}


char *Strcat(char *s1, char *s2){

  unsigned int len1 = lenS(s1);
  unsigned int len2 = lenS(s2);

  char *s3 = NULL;

  s3 = (char *)malloc((len1+len2+1)*sizeof(char));

  if (s3 == NULL) return NULL;

  unsigned int nl=0;

  while(*s1 != '\0' ){
    *(s3+nl) = *s1;
    s1++;
    nl++;
  }
  while(*s2 != '\0' ){
    *(s3+nl) = *s2;
    s2++;
    nl++;
  }
  
  printf("%d\n",nl);

  s3[nl] = '\0';

  return s3;
}


int main(void){

  char fname[]  = "s";
  char lname[]  = "fat";

  printf("%d\n",lenS(fname));
  printf("%d\n",lenS(lname));

  char *fullname = Strcat(fname,lname);

  printf("%s\n",fullname);

  printf("%d\n",lenS(fullname));

  free(fullname);

  return 0;
}

