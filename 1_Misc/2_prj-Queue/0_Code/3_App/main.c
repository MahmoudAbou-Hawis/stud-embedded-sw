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
clear(Queue);
push(Queue,1920);
push(Queue,30);
display(Queue);
    return 0;
}