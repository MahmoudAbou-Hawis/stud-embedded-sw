#include "LinkedList.h"
int main(){
 struct LinkedList *list = (struct LinkedList*)malloc(sizeof(struct LinkedList));
 push(5,list);
 reverse(list);
 display(list);
  
    return 0;
}
