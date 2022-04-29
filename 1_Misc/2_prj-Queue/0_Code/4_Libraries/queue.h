#include <stdio.h>
#include <stdbool.h>
struct queue
{
    int front;
    int rear;
    int *Array ;
    int Capacity;
    int size ;
};
int peek(struct queue *Queue);
int pop(struct queue *Queue);
void push(struct queue *Queue , int value);
int isEmpty(struct queue* Queue);
bool isFull(struct queue *Queue);
void createQueue(struct queue *Queue,int capacity);
bool lengh(struct queue *Queue);
void display(struct queue *Queue);
void clear(struct queue *Queue);
