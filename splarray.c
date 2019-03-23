#include<stdio.h>
#include<stdlib.h>


struct string{
  char *beg;
  char *end;
};

int lenarray(char *text){
  
  int result = 0;
  char *str  = text; 
  if (text){
    while(*str != '\0'){
      if (*str == ',') result++;
      str++;
    }
  }
  if (text) result++;
  return result;
}

struct string getelement(char *text,int  i){

  struct string result = {NULL,NULL};
  int len = lenarray(text);
  if (text == NULL || i < 0 || i >= len) return result;

  char *str = text;
  int    nc = 0;
  char *beg = str;
  char *end = NULL;
  
  if (text){
    while(*str != '\0'){
      if (*str == ','){
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



int main(void){

  char *text = "1,2,3,4,5,6,7,8,9,10";
  
  int len = lenarray(text);
  printf("%d\n",len);

  for (int i=0; i < len;++i){
    printf("elm[%d] = ",i);
    print_string(getelement(text,i));
    printf("\n");
  }

  return 0;
}

