#include "queue.h"
#include <stdio.h>
#include <stdbool.h>
int main(){
struct queue *Queue = (struct queue*)malloc(sizeof(struct queue));
createQueue(Queue,3);
push(Queue,5);
push(Queue,6);
push(Queue,7);
push(Queue,580);
push(Queue,580);
display(Queue);
printf("\n");
push(Queue,70);
display(Queue);
printf("\n");
resize(Queue,5);
push(Queue,580);
push(Queue,9280);
push(Queue,120);
display(Queue);
pop(Queue);
pop(Queue);
printf("\n");
display(Queue);
resize(Queue,2);
printf("\n");
display(Queue);
push(Queue,2001);
push(Queue,1201);
push(Queue,1501);

printf("\n");
display(Queue);
    return 0;
}