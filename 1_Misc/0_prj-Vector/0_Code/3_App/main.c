#include <stdio.h>
#include <stdlib.h>
#include "Vector.h"

int main() {
   struct vector v;
    init(&v);
    int element ;
    while (1){
        scanf("%d",&element);
        if(element==0)
            break;
        Push(&v,element);
    }
    display(&v);
    printf("%d %d ",v.index,v.capacity);

    return 0;
}
