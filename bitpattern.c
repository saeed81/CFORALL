#include<stdio.h>
#include<stdlib.h>


int stringcmp(char *s1, char *s2){

  if ((s1 == NULL) || (s2 == NULL)) return 0;
  int equal = 1;
  while( *s1 != '\0' &&  *s2 != '\0' ){
    if (*s1 != *s2){
      equal = 0;
      break;
    }
    s1++;
    s2++;
  }
  if (*s1 != '\0' || *s2 != '\0') equal = 0;
  
  return equal;
}

void floatbitpattern(float aa, char *sa){
  char bit[33] = {'\0'};
  unsigned char co = 1;
  unsigned char *pt = (unsigned char *)&aa;
  int nc = 0;
  for (unsigned int i=0; i < sizeof(float); ++i){
    for (unsigned int j=0; j < 8;++j){
      bit[nc] = ((*pt >> j) & co) + '0';
      nc++;
    }
    pt++;
  }
  //char *tmp = sa;
  for (int i=31;i >=0;--i){
    *sa++ = bit[i];
    //tmp++;
  }
  *sa = '\0';
}  

void doublebitpattern(double aa, char *sa){
  char bit[65] = {'\0'};
  unsigned char co = 1;
  unsigned char *pt = (unsigned char *)&aa;
  int nc = 0;
  for (unsigned int i=0; i < sizeof(double); ++i){
    for (unsigned int j=0; j < 8;++j){
      bit[nc] = ((*pt >> j) & co) + '0';
      nc++;
    }
    pt++;
  }
  for (int i=63;i >=0;--i){
    *sa++ = bit[i];
  }
  *sa = '\0';
}  

int main(void){
  char bit[33] = {'\0'};
  float aa = 1.0 / 4.0;
  unsigned char co = 1;
  unsigned char *pt = (unsigned char *)&aa;
  int nc = 0;
  for (unsigned int i=0; i < sizeof(float); ++i){
    for (unsigned int j=0; j < 8;++j){
      //printf("%d ",((*pt >> j) & co));
      bit[nc] = ((*pt >> j) & co) + '0';
      nc++;
    }
    pt++;
  }
  printf("\n");
  for (int i=31;i >=0;--i)printf("%c ",bit[i]);
  printf("\n");
  char bit1[33] = {'\0'};
  floatbitpattern(aa, bit1);
  for (int i=0;i <32;++i)printf("%c ",bit1[i]);
  printf("\n");
  char bit2[33] = {'\0'};
  floatbitpattern(aa * 1.00000001, bit2);
  for (int i=0;i <32;++i)printf("%c ",bit2[i]);
  printf("\n");
  printf("%d\n",stringcmp(bit1,bit2));
  printf("%f\n",aa * 1.00000001);
  printf("%d\n",(int)sizeof(double));
  char bit3[65] = {'\0'};
  double ab = 1.0 / 2.0;
  doublebitpattern(ab, bit3);
  for (int i=0;i <64;++i)printf("%c ",bit3[i]);
  printf("\n");
  printf("%d\n",stringcmp("sa", "sa"));

  
  return 0;
}
  
