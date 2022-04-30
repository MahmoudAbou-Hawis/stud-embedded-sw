#include "stack.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
void createStack(struct stack *Stack, int capacity){
Stack->Capacity = capacity;
Stack->Array = (int*)malloc(capacity * sizeof(int));
Stack->Top = -1;
}

bool isFull(struct stack *Stack){
return (Stack->Top == Stack->Capacity-1);
}

bool isEmpety(struct stack *Stack){
return (Stack->Top == -1);
}

void push(struct stack *Stack, int value){
    if(isFull(Stack))
      return;
      Stack->Array[++Stack->Top]=value;
}

int pop(struct stack *Stack){
    if(isEmpety(Stack))
        return INT_MIN;
    return Stack->Array[Stack->Top--];
}

int peek(struct stack *Stack){
    if(isEmpety(Stack))
        return INT_MIN;
    return Stack->Array[Stack->Top];    
}

void resize(struct stack *Stack ,int newSize){
 Stack->Array = realloc(Stack->Array,newSize * sizeof(int));
 Stack->Top = (newSize-1 < Stack->Top)?newSize-1:Stack->Top;
 Stack->Capacity = newSize;
}

int size(struct stack *Stack ){
    if(isEmpety(Stack))
        return INT_MIN;
    return Stack->Top+1;
}

void display(struct stack *Stack ){
    if(isEmpety(Stack))
        return;
    for(int i = 0 ; i <=Stack->Top ; i++)
        printf("%d ",Stack->Array[i]);
    
}