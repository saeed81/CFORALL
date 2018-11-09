#include<stdio.h>
#include<stdlib.h>


struct Node{
  struct Node *next;
  struct Node *before;
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
    lst->last->before = NULL;
    lst->last->next = NULL;
  }
  else{
    struct Node *tmp = (struct Node *)malloc(sizeof(struct Node));
    tmp->a = a;
    lst->last->next = tmp;
    tmp->before = lst->last; 
    lst->last = tmp;
    lst->last->next = NULL;
  }
}


void sweep_list_forward(struct list *lst){
  for(struct Node *ll = lst->head;ll;ll = ll->next){
    printf("%d \n",ll->a);
  }

}

void sweep_list_backward(struct list *lst){
  for(struct Node *ll = lst->last;ll;ll = ll->before){
    printf("%d \n",ll->a);
  }

}




int main(void){

  struct list lst;
  init_list(&lst);
  for (int i=0; i < 5; ++i){
    add_list(&lst, i);
  }
  printf("forward ->>>\n");
  sweep_list_forward(&lst);
  printf("backward ->>>\n");
  sweep_list_backward(&lst);
  
  return 0;
  

}


    



