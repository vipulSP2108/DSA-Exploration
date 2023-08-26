#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* next;
};
void triversal(struct Node* head){
    struct Node* ptr;
    ptr = head;
    while (ptr != NULL){
        printf("%d", ptr->data);
        ptr = ptr-> next;
    }
}
struct Node * insertion_atbiginning(struct Node* head, int newVal){
    struct Node *arr = (struct Node*)malloc(sizeof(struct Node));
    arr -> data = newVal;
    arr->next = head;
    return arr;
}
struct Node* insertion_atindex(struct Node* head, int index, int newVal){
    struct Node* arr = (struct Node*)malloc(sizeof(struct Node));
    struct Node* ptr = head;
    for(int i = 0; i != index-1; i++){
        ptr = arr -> next;
    }
    arr -> next = ptr -> next;
    ptr -> next = arr;
    arr -> data = newVal;
    return head;
}
struct Node* insertion_afterNode(struct Node* ptr, int newVal, struct Node* head){
    struct Node* arr = (struct Node*)malloc(sizeof(struct Node));
    arr -> data = newVal;
    arr -> next = ptr -> next;
    arr -> next = arr;
    return head;
}
struct Node* insertion_atend(struct Node* head, int newVal){
    struct Node* arr = (struct Node*)malloc(sizeof(struct Node));
    struct Node* ptr = head;
    while (ptr != NULL){
        ptr = ptr->next;
    }
    ptr -> next = arr;
    arr -> data = newVal;
    arr -> next = NULL;
    return head;
}
int main(){
    return 0;
    struct Node* head = (struct Node*)malloc(sizeof(struct Node));
    struct Node* first = (struct Node*)malloc(sizeof(struct Node));
    struct Node* secound = (struct Node*)malloc(sizeof(struct Node));

    head -> data = 1;
    head -> next = first;
    first -> data = 2;
    first -> next  = secound;
    secound -> data = 3;
    secound -> next = NULL;

    triversal(head);
    struct Node* head = insertion_atbiginning(head,0);
    triversal(head);
    struct Node* head = insertion_atindex(head,2,50);
    triversal(head);
    struct Node* head = insertion_atend(head,100);
    triversal(head);
    struct Node* head = insertion_afterNode(first,100,head);
    triversal(head);
}
