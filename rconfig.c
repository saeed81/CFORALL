#include<stdio.h>
#include<stdlib.h>

enum type{
  CHAR   = 0,
  STRING = 1,
  FLOAT  = 2,
  DOUBLE = 3,
  INT    = 4,
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

void removewhitespace(struct content *cont){

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


struct member get(struct content *cont,char *sec, char *subsec){
  struct member result = {NULL,0,CHAR};

  return result;
  
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

  char *ss = NULL;
  int nn = 0;
  int found = 0;
  char *beg = NULL;
  char *end = NULL;
  
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
	      for (char *C=beg+1;C <=end-1 && *ct != '\0';++C,++ct){
		if (*ct != *C){
		  found = 0;
		  break;
		}
	      }
	      st = ss;
	      break;
	    }
	    ss++; 
	  }
	}
	st++;
      }
      if (found && beg && end){
	for (char *ct = end + 1;*ct != '\0' && *ct != '[';++ct ){
	  if (*ct == '='){
	    struct position pos = {NULL, NULL};
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

int main(void){

  struct content cont = readfilecontent("config.ini");
  removewhitespace(&cont);
  dumpcontent(&cont);
  int nsections = numberofsections(&cont);
  printf("number of sections is %d\n",nsections);
  
  struct member memb1 = get(&cont,"input","dir");
  struct member memb2 = get(&cont,"input","owner");
  
  dumpkeysinsection(&cont, "drivers");
  
  
  return 0;


}
