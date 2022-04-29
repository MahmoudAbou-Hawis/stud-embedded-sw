#include <stdio.h>
#include "LinkedList.h"
#include<stdbool.h>

void push(int Value,struct LinkedList *list ){
     struct Node *NewNode =(struct Node*) malloc(sizeof(struct Node));
     NewNode->data = Value;
     NewNode->nxtNode=NULL;
     if(list->Head==NULL){
         list->Head = NewNode;
         list->Last = NewNode;
         return;
     }
     list->Last->nxtNode = NewNode;
     list->Last = NewNode;
} 
bool isEmbety(struct LinkedList *list){
    return (list->Head==NULL);
}
struct Node* Search(int Key ,struct LinkedList *list){
    struct Node *Current = list->Head;
    while(Current!=NULL){
        if(Key == Current->data)
            return Current;
        Current = Current->nxtNode;
    }
    return NULL;
} 
struct Node* Delete(int Key,struct LinkedList *list){ 
    struct Node *Current = list->Head;
    struct Node *Last = list->Head;
    while (Current!=NULL){
        if (Current->data==Key)
        {
            if(Current==Last){
                if(list->Head != list->Last)
                list->Head =list->Head->nxtNode;
                else{
                    list->Head=NULL;
                    list->Last=NULL;
                }
            }
           Last->nxtNode = Current->nxtNode;
           return Current;
        }
        Last = Current;
        Current=Current ->nxtNode;     
    }
    return NULL;
}
int length(struct LinkedList *list){
    int len = 0;
    struct Node *Current = list->Head;
    while(Current!=NULL){
        len++;
        Current=Current->nxtNode;
    }
    return len;
}
void display(struct LinkedList *list){
   struct Node *Current =list->Head;
   while(Current!=NULL){
        printf("%d ",Current->data);
        Current=Current->nxtNode;
    }
    return;
}
void destroy(struct LinkedList *list){
    struct Node *Current = list->Head;
    struct Node *Pointer = list->Head;
    while(Current!=NULL){
        Pointer = Current;
        Current = Current->nxtNode;
        free(Pointer);
    }
    list->Head=NULL;
    list->Last=NULL; 
    return;
}
void reverse(struct LinkedList *list){
   struct Node *last = NULL;
   struct Node *Current = list->Head;
   struct Node* temp = NULL;
   while (Current!=NULL)
   {
       temp = Current->nxtNode;
       Current->nxtNode = last;
       last= Current;
       Current = temp;  
   }
    list->Last = list->Head;
    list->Head = last;
}