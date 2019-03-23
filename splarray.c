#include<stdio.h>
#include<stdlib.h>


struct string{
  char *beg;
  char *end;
};

int lenarray(char *text, char FS){
  
  int result = 0;
  char *str  = text; 
  if (text){
    while(*str != '\0'){
      if (*str == FS) result++;
      str++;
    }
  }
  if (text) result++;
  return result;
}

int lenarray_bg(struct string *text, char FS){
  
  int result = 0;
  char *str  = text->beg; 
  if (text->beg){
    while(str <= text->end){
      if (*str == FS) result++;
      str++;
    }
  }
  if (text->beg) result++;
  return result;
}



struct string getelement_bg(struct string *text,int  i, char FS){

  struct string result = {NULL,NULL};
  int len = lenarray_bg(text,FS);
  if (text->beg == NULL || text->end == NULL || i < 0 || i >= len) return result;

  char *str = text->beg;
  int    nc = 0;
  char *beg = text->beg;
  char *end = NULL;
  
  while(str <= text->end){
    if (*str == FS){
      end = str - 1;
      if (i == nc){
	result.beg = beg;
	result.end = end;
	break;
      }
      beg = str + 1;
      nc++;
    }
      str++;
  }
  if (nc == 0 && i == 0 && len == 1){
    result.beg = text->beg;
    result.end = text->end;
  }
  if (nc == (len -1) && i == nc){
    result.beg = beg;
    result.end = text->end;
  }
  
      
  return result;
}

struct string getelement(char *text,int  i, char FS){

  struct string result = {NULL,NULL};
  int len = lenarray(text,FS);
  if (text == NULL || i < 0 || i >= len) return result;

  char *str = text;
  int    nc = 0;
  char *beg = str;
  char *end = NULL;
  
  if (text){
    while(*str != '\0'){
      if (*str == FS){
	end = str - 1;
	if (i == nc){
	  result.beg = beg;
	  result.end = end;
	  break;
	}
	beg = str + 1;
	nc++;
      }
      str++;
    }
    if (nc == 0 && i == 0 && len == 1){
      result.beg = text;
      str = text;
      while(*str != '\0') str++;
      result.end = str -1;
    }
    if (nc == (len -1) && i == nc){
      result.beg = beg;
      str = text;
      while(*str != '\0') str++;
      result.end = str -1;
    }
  }
      
  return result;
}


void print_string_pt(struct string *str){
  for (char *at= str->beg;at <= str->end;++at)printf("%c",*at);
}

void print_string(struct string str){
  for (char *at= str.beg;at <= str.end;++at)printf("%c",*at);
}

long long int pow10(long long int n){
  long long int d = 1;
  if (n > 0){
    for (long long int i=0; i < n;++i) d *= 10;
  }
  return d;
}


long long int stoi_bg(struct string *str){
  int sign = 0;
  long long int nc=0;
  char *temp = str->beg;

  while (temp<=str->end ){
    if ( *temp != ' ') nc++;
    temp++;
  }
  nc--;
  long long int d = 0;
  long long int c = 1;
  char *st = str->beg;
  while (st<=str->end ){
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
      d += ((int)(*st - '0')*pow10(nc));
      st++;
      nc--;
    }
    else {
      st++;
    }
  }

  return (c*d);
}

int main(void){

  char *text = "Mean sea level pressure:1,Total precipitation:2,2 metre temperature:3,10 metre V wind component:4,10 metre U wind component:5,Land-sea mask:6,Mean sea level pressure:7,Total precipitation:8,2 metre temperature:9,10 metre V wind component:10,10 metre U wind component:11,Land-sea mask:12";
  int len = lenarray(text,',');
  printf("%d\n",len);
  for (int i=0; i < len;++i){
    struct string str = getelement(text,i,',');
    printf("elm[%2d] = ",i);
    //print_string(str);
    struct string str1 = getelement_bg(&str,1,':');
    print_string(str1);
    printf("\n");
  }

  return 0;
}

