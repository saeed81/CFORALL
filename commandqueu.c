#include<stdio.h>
#include<stdlib.h>

enum CMD {Init, Draw, Repaint, Clear,};
typedef void fun(void);

void init   (void){printf("init     commnad \n");}
void draw   (void){printf("draw     commnad \n");}
void repaint(void){printf("repaint  commnad \n");}
void clear  (void){printf("clear    commnad \n");}

struct queue{
  void **command;
  int size;
  int cur;
};

void inti_queue(struct queue *que, int size){
  que->command = (void **)malloc(sizeof(void *) * size);
  que->size = size;
  que->cur  = 0;
}

void push_command(struct queue *qu, fun *com){
  if (qu->cur < (qu->size)){
    *((fun**)qu->command + qu->cur) = *com;  
    qu->cur++;
  }
}

void run_allcommand(struct queue *qu){
  for (int i=0; i < qu->cur;++i){ 
    (**((fun**)qu->command + i))();
  }
}

void run_command(struct queue *qu, enum CMD cmd){
  (**((fun**)qu->command + cmd))();
}

int main(void){
  
  struct queue que;
  inti_queue(&que, 4);
  push_command(&que,&init);
  push_command(&que,&draw);
  push_command(&que,&repaint);
  push_command(&que,&clear);
  run_allcommand(&que);
  run_command(&que, Init);

  return 0;
}















