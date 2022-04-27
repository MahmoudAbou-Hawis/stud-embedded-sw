#include <stdio.h>
#include <stdlib.h>
#include "Vector.h"
void init(struct vector *Vector){
    Vector->ptr = (int*) calloc(10,sizeof(int));
    Vector->capacity = 10;
    Vector->index=0;
}
void Push(struct vector *Vector , int element){
    Vector->ptr[Vector->index]=element;
    Vector->index++;
    if(Vector->index == Vector->capacity) {
        Vector->capacity +=10;
        Vector->ptr = realloc(Vector->ptr, Vector->capacity * sizeof(int));
    }
}
void pop(struct vector *Vector){
    if(Vector->index!=0)
    Vector->index--;
}
void display(struct vector *Vector){
    for(int i =0;i<Vector->index;i++)
        printf("%d ",Vector->ptr[i]);
}