#include "stack.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
int main(){
struct stack *Stack = (struct stack*)malloc(sizeof(struct stack));
 createStack(Stack,3);
 push(Stack,7);
 push(Stack,5);
 push(Stack,9);
 push(Stack,10);
 display(Stack);
 resize(Stack,5);
 printf("\n");
 push(Stack,10);
 push(Stack,11);
 display(Stack);
  printf("\n");
 resize(Stack,3);
 pop(Stack);
 push(Stack,40);
 display(Stack);

    return 0;
}