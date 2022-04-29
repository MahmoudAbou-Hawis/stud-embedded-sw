#include "LinkedList.h"
int main(){
 struct LinkedList *list = (struct LinkedList*)malloc(sizeof(struct LinkedList));
 push(5,list);
 push(6,list);
 push(9,list);
 reverse(list);
 display(list);
 push(10,list);
  printf("\n"); 
  reverse(list);
  display(list);
  Delete(5,list);
  printf("\n");
  display(list);
    return 0;
}
