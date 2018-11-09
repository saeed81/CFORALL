#include<stdio.h>
#include<stdlib.h>


struct Node{
  struct Node *next;
  int a;
};

struct list{
  struct Node *head;
  struct Node *last;
  
};


void init_list(struct list *lst){
  lst->head = NULL;
  lst->last = NULL;
}



void add_list(struct list *lst, int a){

  if (lst->head == NULL){
    lst->head    = (struct Node *)malloc(sizeof(struct Node));
    lst->head->a = a;
    lst->last = lst->head;
  }
  else{
    struct Node *tmp = (struct Node *)malloc(sizeof(struct Node));
    tmp->a = a;
    lst->last->next = tmp;
    lst->last = tmp;
    lst->last->next = NULL;
    
  }
}


void sweep_list(struct list *lst){
  for(struct Node *ll = lst->head;ll;ll = ll->next){
    printf("%d \n",ll->a);
  }

}

int main(void){

  struct list lst;
  init_list(&lst);
  for (int i=0; i < 5; ++i){
    add_list(&lst, i);
  }
  sweep_list(&lst);
  
  return 0;
  

}


    



