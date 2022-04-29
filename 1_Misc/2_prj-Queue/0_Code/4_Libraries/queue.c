#include <stdio.h>
#include <stdbool.h>
#include "queue.h"
#include <limits.h>
#include <stdlib.h>
void createQueue(struct queue *Queue,int capacity){
    Queue->Capacity = capacity;
    Queue->Array =   Queue->Array = (int*)malloc(capacity *sizeof(int));
    Queue->size = 0;
    Queue->front = 0;
    Queue->rear = -1;
}
bool isFull(struct queue *Queue){
    return (Queue->size == Queue->Capacity);
}
bool lengh(struct queue *Queue){
    return Queue->size;
}
int isEmpty(struct queue* Queue)
{
    return (Queue->size == 0);
}
void push(struct queue *Queue , int value){
    if(isFull(Queue) ){
        return;
    }
    Queue->Array[++Queue->rear]=value;
    Queue->size=Queue->size + 1;
}
int pop(struct queue *Queue){
     if(isEmpty(Queue) ){
        return;
    }
    int element = Queue->Array[Queue->front];
    Queue->front = Queue->front+1;
    if(Queue->front > Queue->rear){
        Queue->rear=-1;
        Queue->front=0;
    }
    Queue->size = Queue->size-1;
    return element;
}
int peek(struct queue *Queue){
    if(!isEmpty(Queue) )
        return Queue->Array[Queue->front];
       return INT_MIN; 
}
void display(struct queue *Queue){
    if(!isEmpty(Queue))
        for(int i = 0 ;i < Queue->size ;i++)
            printf("%d ",Queue->Array[i]);
}
void clear(struct queue *Queue){
    Queue->front=0;
    Queue->rear = -1;
    Queue->size =0;
}