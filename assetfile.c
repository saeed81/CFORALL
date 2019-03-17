#include<stdio.h>
#include<stdlib.h>


struct string{
  char *beg;
  long int size;
};


struct chunk {
  char *filename;
  char *content;
  int size;
  struct chunk *next;
};

struct stream{ 
  struct chunk *beg;
  struct chunk *end;
  int total;
};


struct string readentirefile(char *filename){

  struct string result = {NULL,0};
  if (filename){
    FILE *file = fopen(filename,"rb");
    if (file){
      fseek(file,0,SEEK_END);
      result.size = ftell(file);
      fseek(file,0,SEEK_SET);
      result.beg = (char *)malloc(result.size +1);
      if (result.beg){
	fread(result.beg,1,result.size,file);
	*(result.beg + result.size) = '\0';
      }
      fclose(file);
    }
  }
  return result;
}



void addchunk(struct stream *strm, char *filename){

  #if defined debug
  printf("%d\n",(int)(&((struct chunk *)0)->filename));
  printf("%d\n",(int)(&((struct chunk *)0)->content));
  printf("%d\n",(int)(&((struct chunk *)0)->size));
  printf("%d\n",(int)(&((struct chunk *)0)->next));
  #endif
  
  if (strm->beg == NULL){
    strm->beg           = (struct chunk *)malloc(sizeof(struct chunk));
    strm->beg->filename = filename;
    struct string ctemp = readentirefile(filename);   
    strm->beg->content  = ctemp.beg;
    strm->beg->size     = ctemp.size;
    strm->end           = strm->beg;
    strm->end->next     = NULL;
  }else{
    struct chunk * tmp  = (struct chunk *)malloc(sizeof(struct chunk));
    tmp->filename       = filename;
    struct string ctemp = readentirefile(filename);   
    tmp->content        = ctemp.beg;
    tmp->size           = ctemp.size;
    strm->end->next     = tmp;
    strm->end           = tmp;
    strm->end->next     = NULL; 
  }
}

int gettoalchunks(struct stream *strm){
  int result = 0;
  for (struct chunk *first=strm->beg;first;first=first->next) result++; 
  return result;
}


void showfilenames(struct stream *strm){

  for(struct chunk *elm = strm->beg;elm;elm = elm->next){
    printf("%s\n",elm->filename);
  }
}


void showfilescontent(struct stream *strm){

  for(struct chunk *elm = strm->beg;elm;elm = elm->next){
    printf("content of the file %s\n",elm->filename);
    for (long int i=0; i < elm->size;++i)printf("%c",*(elm->content+i));
  }
}






void cleanstream(struct stream *strm){
  
  int nx = gettoalchunks(strm);
  struct chunk **elm =&(strm->beg), **elm1 = NULL;
  for (int i=0; i < nx;++i){
    elm1 = &((*elm)->next);
    free(*elm);
    *elm = NULL;
    elm = elm1;
  }
}



int main(int argc, char *argv[]){
  
  struct stream stream   = {(struct chunk *)0,(struct chunk *)0,0};
  struct stream *pstream = &stream;
  
  addchunk(pstream, "vector.c");
  addchunk(pstream, "visual.c");
  
  showfilenames(pstream);
  printf("total chunks is %d\n",gettoalchunks(pstream));
  showfilescontent(pstream);
  cleanstream(pstream);
  showfilenames(pstream);

    
  return 0;
}






  
  













