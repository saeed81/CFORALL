#include<stdio.h>
#include<stdlib.h>
#include<math.h>

static char Str[32]  = {'\0'};
static char RStr[32] = {'\0'};

#define Dir "./repo/"

static void reverse(char *s, char *t, int sign, int npadzero){
  
  char *tmp = s;
  int len = 0;
  while (*tmp !='\0' ){
    tmp++;
    len++;
  }
  tmp--;

  if (sign < 0){
    *t = '-';
    t++;
  }

  while(npadzero--){
    *t = '0';
    t++;
  }
  
  while (len >0 ){
    *t = *tmp;
    tmp--;
    len--;
    t++;
  }
  *t = '\0';
}

static void intostr(int a, char *st){
  int sign = 1;
  if (a < 0){
    sign = -1;
    a = (-a);
  }
  int index = 0;
  int r = -1 ;
  int q = 0;
  char cl[64] = {'\0'};
  do {
    r = a % 10;
    q = (a - r) / 10;
    *(cl+index) = (char)(r+'0');
    a = q;
    index++;
  }while(a >0);
  
  *(cl+index) = '\0';

  reverse(cl,st,sign,0);
  
}

static void floatostr(float a, char *str, int nafterdecimalpoint){
  int sign = 1;
  long long int ia = (long long int) (a);
  if (a < 0) {
    //printf("we are here\n");
    sign = -1;
    a = (-a);
    ia = (long long int) (a);
  }
  int npadzero = 0;
  long long int n = 1;
  float b = a - (float)ia;
  float bt = b;
  int hitnonzero = 0;
  
  for(int i=0; i < nafterdecimalpoint;++i){
    n *= 10L;
    bt *= 10L;
    if (((long long int)bt == 0) && (hitnonzero == 0)) npadzero++;
    if ((long long int)bt != 0 ) hitnonzero = 1;
    bt = bt - (long long int)bt;
  }
  if (nafterdecimalpoint == 1) npadzero = 0;

  b *= n;
  long long int ifrac = (long long int) b;
  int index = 0;
  long long int r = -1 ;
  long long int q = 0;
  char cl[64] = {'\0'};
  char ctmp[64] = {'\0'};
  do {
    r = ia % 10;
    q = (ia - r) / 10;
    *(cl+index) = (char)(r+'0');
    ia = q;
    index++;
  }while(ia >0);

  *(cl+index) = '\0';
  reverse(cl,ctmp,sign,0);

  char ck[64]    = {'\0'};
  char ctmp1[64] = {'\0'};
  
  r = -1 ;
  q = 0;
  index = 0;
  do {
    r = ifrac % 10;
    q = (ifrac - r) / 10;
    *(ck+index) = (char)(r+'0');
    ifrac = q;
    index++;
  }while(ifrac >0);

  *(ck+index) = '\0';
  if (sign > 0){
    reverse(ck,ctmp1,sign,npadzero);
  }else{
    reverse(ck,ctmp1,-sign,npadzero);
  }

  char *tmp = ctmp;
  while(*tmp != '\0'){
    *str = *tmp;
    str++;
    tmp++;
  }
  *str = '.';
  str++;
  tmp = ctmp1;

  while(*tmp != '\0'){
    *str = *tmp;
    str++;
    tmp++;
  }
  *str = '\0';
  
  return;

}

static int lenstr(char *st){
  int result = 0;
  if (st){
    while(*st != '\0'){
      result++;
      st++;
    }
  }
  return result;
}



static char *concat(char *st1, char *st2){
  
  int len = lenstr(st1) + lenstr(st2) + 1;
  
  char *result = (char *)malloc(len);
  
  int i = 0;
  while(*st1 != '\0'){
    *(result + i) = *st1;
    i++;
    st1++;
  }

  while(*st2 != '\0'){
    *(result + i) = *st2;
    i++;
    st2++;
  }

  *(result + i) = '\0';

  return result;
  
}

static char *concat2(char *st1, char *st2, char *st3){
  
  int len = lenstr(st1) + lenstr(st2) + lenstr(st3) + 1;
  
  char *result = (char *)malloc(len);
  
  int i = 0;
  while(*st1 != '\0'){
    *(result + i) = *st1;
    i++;
    st1++;
  }

  while(*st2 != '\0'){
    *(result + i) = *st2;
    i++;
    st2++;
  }
  
  while(*st3 != '\0'){
    *(result + i) = *st3;
    i++;
    st3++;
  }

  
  *(result + i) = '\0';

  return result;
  
}

static int fileexist(char *filename){
  
  int result = 0;
  FILE *file = fopen(filename,"rb");
  
  if (file){
    result = 1;
    fclose(file);
  }
  return result;
}


#define MAX_VC  (1024)


static void copy_file(char *filename, char *newfile){
  
  char *result = NULL;

  if (filename && newfile){
    FILE *file = fopen(filename,"rb");
    if (file){
      fseek(file,0,SEEK_END);
      long size = ftell(file);
      fseek(file,0,SEEK_SET);
      result = (char *)malloc(size+1);
      fread(result,size,1,file);
      *(result + size) = '\0';
      fclose(file);
      file = fopen(newfile,"wb");
      fwrite(result,size,1,file);
      fclose(file);
    }
  }
}

static void copy(char *filename){
  
  char ver[1024] = {'\0'};
  char *newfile = NULL;
  if (filename){
    for (int i=0; i < MAX_VC;++i){
      ver[0] = '\0';
      intostr(i, ver);
      newfile = concat2(Dir,filename, ver);
      if (!fileexist(newfile)){
	copy_file(filename,newfile);
	printf("version %d file %s\n",i,newfile);
	break;
      }
      if (newfile) free(newfile);
    }
  }
  if (newfile) free(newfile);
}


int main(int argc, char *argv[]){

  if (argc == 2){
    
    char *filename = argv[1];
    copy(filename);
  }

  return 0;


}




