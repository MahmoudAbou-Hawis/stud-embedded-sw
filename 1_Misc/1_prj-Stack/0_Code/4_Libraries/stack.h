#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
struct stack{
int Top;
int *Array;
int Capacity;
};
int size(struct stack *Stack );
void resize(struct stack *Stack ,int newSize);
int peek(struct stack *Stack);
int pop(struct stack *Stack);
void push(struct stack *Stack, int value);
bool isEmpety(struct stack *Stack);
bool isFull(struct stack *Stack);
void createStack(struct stack *Stack, int capacity);
void display(struct stack *Stack );