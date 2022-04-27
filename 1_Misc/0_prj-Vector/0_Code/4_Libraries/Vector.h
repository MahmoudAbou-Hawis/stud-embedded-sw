struct vector{
    int *ptr;
    int capacity;
    int index;
};
void display(struct vector *Vector);
void pop(struct vector *Vector);
void Push(struct vector *Vector , int element);
void init(struct vector *Vector);
