#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* next;
};

void traversal(struct Node* head){
    struct Node* ptr = head;
    while(ptr != NULL){
        printf("%d ", ptr -> data);
        ptr = ptr -> next;
    }
}

struct Node* insertion_inbetween(struct Node* head, int index, struct Node* New){
    struct Node* ptr = head;
    if(index == 0){
        New -> next = ptr;
        return New;
    }
    for(int count = 1; count != index; count++){
        ptr = ptr -> next;
    }
    New -> next = ptr -> next;
    ptr -> next = New;
    return head;
}

int main(){
    struct Node* head = (struct Node*)malloc(sizeof(struct Node));
    struct Node* first = (struct Node*)malloc(sizeof(struct Node));
    struct Node* second = (struct Node*)malloc(sizeof(struct Node));
    struct Node* third = (struct Node*)malloc(sizeof(struct Node));
    struct Node* fourth = (struct Node*)malloc(sizeof(struct Node));

    head -> data = 10;
    first -> data = 11;
    second -> data = 12;
    third -> data = 13;
    fourth -> data = 14;

    head -> next = first;
    first -> next = second;
    second -> next = third;
    third -> next = fourth;
    fourth -> next = NULL;

    traversal(head);
    struct Node* New = (struct Node*)malloc(sizeof(struct Node));
    New -> data = 100;
    int index = 3;
    head = insertion_inbetween(head, index, New);
    printf("\n");
    traversal(head);
}
