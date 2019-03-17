#include<stdio.h>
#include<stdlib.h>

struct chunk {
  char *filename;
  void *content;
  int size;
  struct chunk *next;
};

struct stream{ 
  struct chunk *beg;
  struct chunk *end;
  int total;
};

void addchunk(struct stream *strm, char *filename){

  #if defined debug
  printf("%d\n",(int)(&((struct chunk *)0)->filename));
  printf("%d\n",(int)(&((struct chunk *)0)->content));
  printf("%d\n",(int)(&((struct chunk *)0)->size));
  printf("%d\n",(int)(&((struct chunk *)0)->next));
  #endif
  
  if (strm->beg == NULL){
    strm->beg = (struct chunk *)malloc(sizeof(struct chunk));
    strm->beg->filename = filename;
    strm->end = strm->beg;
    strm->end->next = NULL;
  }else{
    struct chunk * tmp = (struct chunk *)malloc(sizeof(struct chunk));
    tmp->filename   = filename;
    strm->end->next = tmp;
    strm->end       = tmp;
    strm->end->next = NULL; 
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
  
  addchunk(pstream, "pr01.c");
  addchunk(pstream, "pr02.c");
  addchunk(pstream, "pr03.c");
  addchunk(pstream, "pr04.c");
  addchunk(pstream, "pr05.c");
  addchunk(pstream, "pr06.c");
  addchunk(pstream, "pr07.c");
  addchunk(pstream, "pr08.c");
  addchunk(pstream, "pr09.c");
  addchunk(pstream, "pr10.c"); 

  showfilenames(pstream);
  printf("total chunks is %d\n",gettoalchunks(pstream));
  
  cleanstream(pstream);
  showfilenames(pstream);

  struct chunk *ch = (struct chunk *)malloc(sizeof(struct chunk));
  ch->filename = "test";
  printf("%s\n",ch->filename);
  free(ch);
  ch =  NULL;
    
  return 0;
}






  
  













