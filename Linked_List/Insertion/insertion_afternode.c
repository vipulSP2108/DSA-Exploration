#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* next;
};

void traversal(struct Node* head){
    struct Node* ptr = head;
    while (ptr != NULL){
        printf("%d ", ptr-> data);
        ptr = ptr -> next;
    }
}

struct Node* insertion_atNode(struct Node* where,struct Node* new,struct Node* head){
    struct Node* ptr;
    ptr = where -> next;
    where -> next = new;
    new -> next = ptr;
    return head;
}
int main(){
    struct Node* head = (struct Node*)malloc(sizeof(struct Node));
    struct Node* first = (struct Node*)malloc(sizeof(struct Node));
    struct Node* secound = (struct Node*)malloc(sizeof(struct Node));
    struct Node* third = (struct Node*)malloc(sizeof(struct Node));
    struct Node* fourth = (struct Node*)malloc(sizeof(struct Node));

    head -> next = first;
    first -> next = secound;
    secound -> next = third;
    third -> next = fourth;
    fourth -> next = NULL;

    head -> data = 10;
    first -> data = 11;
    secound -> data = 12;
    third -> data = 13;
    fourth -> data = 14;

    traversal(head);

    // insert after third ie, 13
    struct Node* new = (struct Node*)malloc(sizeof(struct Node));
    new -> data = 100;
    head = insertion_atNode(third, new, head);
    printf("\n");
    traversal(head);
}
