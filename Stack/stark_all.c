#include <stdio.h>
#include <stdlib.h>

struct stach{
    int size;
    int high;
    int *arr;
};

int isempty(struct stach* ptr){
    if(ptr -> high == -1){
        return 1;
    }
    return 0;
}

int isfull(struct stach* ptr){
    if(ptr -> size == ptr -> high){
        return 1;
    }
    return 0;
}

void push(struct stach* ptr, int val){
    if(isfull(ptr) == 1){
        printf("Overflow, %d cannot be appended",val);
    }
    ptr -> high = ptr->high + 1;
    ptr -> arr[ptr -> high] = val;
}

int pop(struct stach* ptr){
    if (isempty(ptr) == 1){
        printf("this is empty");
        return 1;
    }
    int priv = ptr->arr[ptr -> high];
    ptr->high = ptr->high - 1;
    return priv;
}

int peek(struct stach* ptr, int i){
    if(ptr -> high - i + 1 <0){
        printf("Invalid index");
    }
    return ptr -> arr[ptr -> high - i +1];

}
int main(){
    struct stach* s;
    s->size = 3;
    s->high = -1;
    s->arr = (int*)malloc(s->size * sizeof(int));

    // printf("%d\n", isempty(s));
    // printf("%d\n", isfull(s));

    push(s,11);
    push(s,12);
    push(s,13);
    printf("%d\n",pop(s));
    printf("%d\n",pop(s));
    // printf("%d\n", peek(s,1));

    return 0;
}
