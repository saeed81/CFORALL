#include<stdio.h>
#include<stdlib.h>
#include"matching.h"



#define LEN(a) (sizeof(a) / sizeof(a[0]))

int main(void){


  char str[] = "named : {fn:saeed,ln:falaht,aa:{bb:cc,dd:ee}}, names : saeed";

  int len = LEN(str);

  printf("len is %d\n", len);

  int ka = -1, kb = -1, kc = -1, kd = -1;

  for (int i=0; i < len; ++i){
    if (str[i] == ':'){
      ka =  i;
      break;
    }
  }
  printf("ka is %d \n",ka);
  
  if (ka >= 0){
    for (int i=(ka+1); i < len; ++i){
      if (str[i] == '{'){
	kb =  i;
	break;
      }
    }
  }


  //check what is between : and {
  
  printf("kb is %d \n",kb);
  
  if (kb >= 0 ){
    int stop = 0; 
    for (int i=(kb-1); i >(ka) ; --i){
      if (str[i] != ' '){
	printf("there is soemthing before {. Now we search for ,\n");
	stop = 1;
	break;
      }
    }
    if (stop){
      for (int i=(ka+1); i < (kb) ; ++i){
	if (str[i] == ','){
	  printf("we found ,\n");
	  kc = i;
	  break;
	}
      }
      for (int i=(ka+1); i < (kc) ; ++i){
	printf("%c",str[i]);
      }
    }
    else {

      char *tmp = &str[kb];
      int index = -1;
      match(tmp, 1, (len-kb+1),'{', &index);
      printf("match { is at index %d and kb + index %d",index, kb +index);
      
      for (int i=(ka+1); i < len ; ++i){
	if (str[i] == '}'){
	  printf("we found ,\n");
	  kd = i;
	  break;
	}
      }
      for (int i=(kb+1); i < kd ; ++i){
	printf("%c",str[i]);
      }
    }
  }
    
  printf("\n");
  
  return 0;
}
