#include<stdbool.h>
#include <stdio.h>
struct LinkedList{
   struct Node* Head;
   struct Node* Last;
};
struct Node {
    int data;
    struct Node* nxtNode;
};
bool isEmbety(struct LinkedList *list);
void reverse(struct LinkedList *list);
void destroy(struct LinkedList *list);
void display(struct LinkedList *list);
int length(struct LinkedList *list);
struct Node*  Delete(int Key,struct LinkedList *list);
struct Node* Search(int Key ,struct LinkedList *list);
void push(int Value,struct LinkedList *list );