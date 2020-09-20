#include<stdio.h>
#include<stdlib.h>

#define len(A) (sizeof(A) / sizeof(A[0]))

typedef struct{
  char fld1[512];
  char fld2[512];
}field;

typedef struct{
  int   xticks;
  int   yticks;
  float xmax;
  float xmin;
  float ymin;
  float ymax;
  float vmin;
  float vmax;
}config;

static int Pow10(int n){
  int d = 1;
  if (n > 0){ 
    for (int i=0; i < n;++i) d *= 10;
  }
  return d;
}

static float nPow10(int n){
  float d = 1.0;
  if (n > 0){ 
    for (int i=0; i < n;++i) d /= 10.0;
  }
  return d;
}

static int stoi(char *st){

  int sign = 0;

  int nc=0;
  char *temp = st;

  while (*temp != '\0' ){
    if ( *temp != ' ') nc++;
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
      sign += 1;
      if (sign > 1 ) return 0;
    }
    else if (*st == '+'){
      c = 1;
      nc--; 
      st++;
      sign += 1;
      if (sign > 1 ) return 0;
    }
    else if( *st != ' ') {
      d += ((int)(*st - '0')*Pow10(nc));
      st++;
      nc--;
    }
    else {
      st++;
    }
  }

  return (c*d);
}

static float stof(char *st){

  char *cin = st;
  int ishasdot = 0;
  while(*cin != '\0'){
    if (*cin == '.'){
      ishasdot = 1;
      break;
    }
    cin++;
  }
  if (ishasdot == 0) return (float)stoi(st);
  
  int sign = 0;
  int nc=0;
  char *temp = st;
  char *tint = st;

  while (*temp != '\0'){
    if ( *temp != ' '){
      if (*temp == '.'){
	break;
      }
      else{
	nc++;
      }
    }
    temp++;
  }
  nc--;
  float d = 0.0;
  int c = 1;
  while (*tint != '\0'){
    if (*tint == '-'){
      c = -1;
      nc--; 
      tint++;
      sign += 1;
      if (sign > 1 ) return 0.0;
    }
    else if (*tint == '+'){
      c = 1;
      nc--; 
      tint++;
      sign += 1;
      if (sign > 1 ) return 0.0;
    }
    else if( *tint != ' ') {
      if (*tint == '.') break;
      d += (float)((int)(*tint - '0')*Pow10(nc));
      tint++;
      nc--;
    }
    else {
      tint++;
    }
  }

  char *tm = st;

  while (*tm != '\0'){

    if (*tm == '.') break;
    tm++;
  }
  char *tm1 = (++tm);
  nc=0;
  float df = 0.0;
  while (*tm1 != '\0'){
    if ( *tm1 != ' ') {
    nc++; 
    df += (float)((int)(*tm1 - '0')*nPow10(nc));
    tm1++;
    }
  }
  
  return (c*(d + df));
}

static int isendofline(char c){
  
  int result = (c == '\n') ? 1 : 0;

  return result;
}

static int numberoflines(char *st){

  int result = 0;
  if (st){
    while(*st != '\0'){
      if (isendofline(*st)) result++;
      st++;
    }
  }
  return result;
}


static field split(char *str, char fr){
  
  field result = {{'\0'},{'\0'}};
  
  char *bf;
  char *af;
  char *temp = str;
  if (str){
    
    while(*str){
      if (*str == fr){
	bf = str - 1;
	af = str + 1;
	break;
      }
      str++;
    }
    str = temp;
    int i = 0;
    for (char *c = str; c <= bf ;++c)result.fld1[i++] = *c;
    result.fld1[i] = '\0';
    i = 0;
    for (char *c = af; *c && !isendofline(*c);++c) result.fld2[i++] = *c;
    result.fld2[i] = '\0';
  }
  return result;
}

static void showfield(field *fld){
  printf("%s\n",fld->fld1);
  printf("%s\n",fld->fld2);
}

static void Memset(void *ptr, int size){
  unsigned char *t = (unsigned char *)ptr;
  for (int i=0; i <size;++i) *t++ = 0; 
}

static char *readentirefile(char *filename){
  
  char *result = NULL;

  if (filename){
    FILE *file = fopen(filename,"rb");
    if (file){
      fseek(file,0,SEEK_END);
      long size = ftell(file);
      fseek(file,0,SEEK_SET);
      result = (char *)malloc(size+1);
      fread(result,size,1,file);
      *(result + size) = '\0';
      fclose(file);
    }
  }
  return result; 
}

static int iswhitespace(char c){
  int result = (c == '\r' || c == ' ' || c == '\t' || c == '\v' || c == '\f') ? 1 : 0;
  return result;
}

static void eatwhitespace(char *s){
  
  char *t = s;
  int n = 0;
  while(*s != '\0'){
    if (!iswhitespace(*s)){
      *(t + n) = *s;
      n++;
    }
    s++;
  }
  *(t + n) = '\0';
  s = t;
}

static int strequal(char *s1, char *s2){
  
  int result = 1;
  int len1 = 0, len2 = 0; 
  
  if (s1 && s2){
    
    while(*s1 != '\0' && *s2 != '\0'){
      if (*s1 != *s2){
	result = 0;
	break;
      }
      s1++;
      s2++;
      len1++;
      len2++;
    }
  }
    
  result = ((result == 1) && (len1 == len2)) ? 1 : 0;

  return result;

}

static void fill_config(config *config, char *key, char *value){
  
  if (strequal(key,"xticks")) config->xticks = stoi(value);
  if (strequal(key,"yticks")) config->yticks = stoi(value);
  if (strequal(key,"xmin"  )) config->xmin   = stof(value);
  if (strequal(key,"xmax"  )) config->xmax   = stof(value);
  if (strequal(key,"ymin"  )) config->ymin   = stof(value);
  if (strequal(key,"ymax"  )) config->ymax   = stof(value);
  if (strequal(key,"vmin"  )) config->vmin   = stof(value);
  if (strequal(key,"vmax"  )) config->vmax   = stof(value);
}


static void show_config(config *config){
  printf("xticks %d \n",config->xticks);
  printf("yticks %d \n",config->yticks);
  printf("xmin   %f \n",config->xmin);
  printf("xmax   %f \n",config->xmax);
  printf("ymin   %f \n",config->ymin);
  printf("ymax   %f \n",config->ymax);
  printf("vmin   %f \n",config->vmin);
  printf("vmax   %f \n",config->vmax);
}


static void removecomment(char *st){
  
  char *t = st;
  while(*t != '\0' ){
    if (*t == '#'){
      while (!isendofline(*t)){
	*t = ' ';
	t++;
      }
    }
    t++;
  }
  
}


static char *getLine(char *con, int n){
  
  char *result = NULL;
  char *t = con;
  int  in = 0;
  char *beg = NULL;
  char *end = NULL;
  while(*t != '\0'){
    if (isendofline(*t) && in == n){
      end = t;
      break;
    }
    if(isendofline(*t)) in++;
    t++;
  }
  end--;
    if (n == 0) beg = con;
  if (end){
    char *t1 = end;
    if (n > 0){
      while(t1 >= con){
	if (isendofline(*t1)){
	  beg = t1;
	  break;
	}
	t1--;
      }
    }
  }
  if (n > 0) beg++;
  result = (char *)malloc(end - beg +1);
  int i = 0;
  for (char *c = beg; c<=end;++c){
    *(result+i) = *c;
    i++;
  }
  *(result+i) = '\0';
  
  return result;
}

static config parseconfigfile(char *filename){
  
  config result;
  Memset(&result, sizeof(result));
  
  char *con    = readentirefile(filename);
  
  if (con){

    eatwhitespace(con);
    removecomment(con);
    eatwhitespace(con);
    printf("content is\n%s\n",con);

    char *keys[] = {"xticks","yticks","vmin","vmax","xmin","xmax","ymin","ymax"};
    
    for (int i=0; i < len(keys);++i){
      char *line = getLine(con,i);
      field fl   = split(line ,'=');
      fill_config(&result, fl.fld1, fl.fld2);
      free(line);
    }
    free(con);
  }

  return result; 
}

int main(void){

  config config = parseconfigfile("config");
  
  show_config(&config);
  
  return 0;
}
