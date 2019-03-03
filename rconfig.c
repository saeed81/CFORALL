#include<stdio.h>
#include<stdlib.h>

enum type{
  STRING = 0,
  FLOAT  = 1,
  INT    = 2,
  NOTYPE = 3,
};


struct content{
  char *data;
  long int size;
};

struct section{
  char *beg;
  long int size;
  int nkeys;
};

struct member{
  char *data;
  long int size;
  enum type type;
};


struct position{
  char *beg;
  char *end;
};

char *Keys[] = {"os","lan","lang","cpu",NULL};


int lenstring(char *str){
  int result = 0;
  if (str){
    while(*str != '\0'){
      result++;
      str++;
    }
  }
  return result;
}

int iswhitespace(char C){

  int result = 0;
  if (C == ' ' || C == '\t' || C == '\v' || C == '\f' || C == '\b') result = 1;
  return result;
}


int isendofline(char C){

  int result = 0;
  if (C == '\n' || C == '\r') result = 1;
  return result;
}


int isemptynextline(char *C){

  int result = 0;
  char *CP   = C + 1;    
  if ((*C == '\n' || *C == '\r') && (*CP == '\n' || *CP == '\r') && *CP != '\0') result = 1;
  return result;
}

void removewhitespace(struct content *cont){
  if (cont){
    if (cont->data){
  char *st = cont->data;
  char *ss = cont->data;
  long int ne = 0;
  while(*st != '\0'){
    if (!iswhitespace(*st)){
      *(ss + ne) = *st;
      ne++;
    }
    st++;
  }
  *(ss + ne) = '\0';
  cont->data = ss;
  cont->size = ne;
    }
  }
}

struct content readfilecontent(char *filename){
  
  struct content result = {NULL,0};
  if (filename){
    FILE *file = fopen(filename,"rb");
    if (file){
      fseek(file,0,SEEK_END);
      result.size = ftell(file);
      fseek(file,0,SEEK_SET);
      result.data = (char *)malloc(result.size + 1);
      if (result.data){
	fread(result.data,1,result.size,file);
	*(result.data + result.size) = '\0';
      }
      fclose(file);
    }
  }

  removewhitespace(&result);
  
  return result;
}

void dumpcontent(struct content *cont){

  if (cont){
    if (cont->data){
      for (long int i=0; i< cont->size;++i ){
	printf("%c",*(cont->data +i));
      }
    }
  }
}

int numberofsections(struct content *cont){

  int result = 0;
  char *ss = NULL;
  int nn = 0;
  //sections are like that [   ]
  if (cont){
    if (cont->data){
      char *st = cont->data;
      while(*st != '\0'){
	if (*st == '['){
	  char *beg = st;
	  ss = st + 1;
	  while(*ss != '\0' ){
	    if (*ss == ']'){
	      char *end = ss;
	      printf("section \n");
	      for (char *C=beg;C <=end;++C){
		printf("%c",*C);
	      }
	      printf("\n");
	      result +=1;
	      st = ss;
	      break;
	    }
	    ss++; 
	  }
	}
	st++;
      }
    }
  }
  return result;
}

void dumpkeysinsection(struct content *cont, char *sec){

  char *ss   = NULL;
  int  nn    = 0;
  int  found = 0;
  char *beg  = NULL;
  char *end  = NULL;
  int lensec = lenstring(sec);
  
  if (cont){
    if (cont->data){
      char *st = cont->data;
      while(*st != '\0' && found == 0){
	if (*st == '['){
	  beg = st;
	  ss = st + 1;
	  while(*ss != '\0' ){
	    if (*ss == ']'){
	      end = ss;
	      char *ct = sec;
	      found = 1;
	      int lens = end - beg - 1 ;
	      for (char *C=beg+1;C <=end-1 && *ct != '\0';++C,++ct){
		if (*ct != *C){
		  found = 0;
		  break;
		}
	      }
	      if (found && lens != lensec ) found = 0;
	      st = ss;
	      break;
	    }
	    ss++; 
	  }
	}
	st++;
      }
      if (found && beg && end){
	 struct position pos = {NULL, NULL};
	 for (char *ct = end + 1;*ct != '\0' && *ct != '[';++ct ){
	   if (*ct == '='){
	     pos.end = ct - 1;
	     while (*pos.end != '\n') pos.end--;
	     pos.beg = pos.end+1;
	     printf("\nkey   :\n");
	     for (char *ckey=pos.beg;ckey < ct;++ckey)printf("%c",*ckey);
	     printf("\nvalue :\n");
	     pos.beg = ct + 1;
	     while (*pos.beg != '\n' && *pos.beg != '\0') pos.beg++;
	     pos.end = pos.beg - 1;
	     for (char *cval=ct + 1;cval<=pos.end;++cval)printf("%c",*cval);
	   }
	}
      }
    }
  }
  
  return;
}

struct member get(struct content *cont,char *sec, char *key){
  struct member result = {NULL,0,NOTYPE};

  if (!sec || !key || !cont || !cont->data ) return result;
  
  char *ss     = NULL;
  int  nn      = 0;
  int  found   = 0;
  char *beg    = NULL;
  char *end    = NULL;
  int matchkey = 0;
  struct position pos = {NULL, NULL};
  char *st = cont->data;
  char *tk   = key;
  int lenkey = lenstring(key);
  int lensec = lenstring(sec);
  int ncount = 0;
  printf("lensc is %d\n",lensec);
  while(*st != '\0' && found == 0){
    if (*st == '['){
      beg = st;
      ss = st + 1;
      while(*ss != '\0' ){
	if (*ss == ']'){
	  end = ss;
	  char *ct = sec;
	  found = 1;
	  ncount = 0;
	  int lens = end - beg - 1 ;
	  for (char *C=beg+1;C <=end-1 && *ct != '\0';++C,++ct){
	    if (*ct != *C){
	      found = 0;
	      break;
	    }
	    ncount++;
	  }
	  if (found && lens != lensec ) found = 0;
	  st = ss;
	  break;
	}
	ss++; 
      }
    }
    st++;
  }
  if (found && beg && end){
    for (char *ct = end + 1;*ct != '\0' && matchkey == 0 && *ct != '[';++ct ){
      if (*ct == '='){
	pos.end = ct - 1;
	while (*pos.end != '\n') pos.end--;
	pos.beg = pos.end+1;
	tk      = key;
	matchkey= 1;
	ncount = 0;
	int lenk = 0;
	for (char *ckey=pos.beg;ckey < ct;++ckey)lenk++;
	for (char *ckey=pos.beg;ckey < ct && *tk != '\0';++ckey){
	  if (*tk != *ckey){
	   matchkey = 0;
	   break;
	  }
	  ncount++;
	  tk++;
	}
	if (matchkey && lenk != lenkey) matchkey = 0;
	if (matchkey){
	  pos.beg = ct + 1;
	  while (*pos.beg != '\n' && *pos.beg != '\0') pos.beg++;
	  pos.end = pos.beg - 1;
	  result.data = ct + 1;
	  result.size = 0; 
	  for (char *cval=ct + 1;cval<=pos.end;++cval)result.size++;
	}
      }
    }
  }
  
  return result;
}


int main(void){

  struct content cont = readfilecontent("config.ini");
  dumpcontent(&cont);

  int nsections = numberofsections(&cont);
  printf("number of sections is %d\n",nsections);
  
  dumpkeysinsection(&cont, "drivers");
  dumpkeysinsection(&cont, "mcij");

  printf("==================\n");
  for (char **vk = &Keys[0];*vk;++vk){
    struct member memb1 = get(&cont,"mci",*vk);
    printf("%s =",*vk);
    for (int i = 0; i <=memb1.size;++i){
      printf("%c",*(memb1.data + i));
    }
    printf("==================\n");
  }

  return 0;


}
