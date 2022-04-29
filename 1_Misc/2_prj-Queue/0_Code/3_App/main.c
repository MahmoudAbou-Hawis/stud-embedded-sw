#include "queue.h"
#include <stdio.h>
#include <stdbool.h>
int main(){
struct queue *Queue = (struct queue*)malloc(sizeof(struct queue));
createQueue(Queue,3);
isEmpty(Queue);
lengh(Queue);
push(Queue,5);
push(Queue,6);
push(Queue,7);
push(Queue,8);
display(Queue);
printf("\n");
printf("%d %d\n",Queue->rear,Queue->front);
printf("%d\n",Queue->size);
pop(Queue);
pop(Queue);
pop(Queue);
printf("%d %d\n",Queue->rear,Queue->front);
push(Queue,51);
push(Queue,62);
push(Queue,70);
push(Queue,89);
display(Queue);
printf("\n");
pop(Queue);
printf("%d\n",Queue->rear);
printf("%d\n",Queue->size);
push(Queue,70);
push(Queue,80);
display(Queue);
    return 0;
}