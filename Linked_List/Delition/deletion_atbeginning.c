#include <stdio.h>
#include <stdlib.h>

struct Node{
  int data;
  struct Node* next;
};

void triversal(struct Node* head){
  struct Node* ptr = head;
  while (ptr->next != NULL){
    printf("%d\n", ptr->data);
    ptr = ptr -> next;
  }
}

struct Node* delition_inbeginning(struct Node* head){
  struct Node* ptr;
  ptr = head;
  head = head -> next;
  free(ptr);
  return head;
}

int main(){
  struct Node* head = (struct Node*)malloc(sizeof(struct Node));
  struct Node* first = (struct Node*)malloc(sizeof(struct Node));
  struct Node* second = (struct Node*)malloc(sizeof(struct Node));
  struct Node* third = (struct Node*)malloc(sizeof(struct Node));
  struct Node* fourth = (struct Node*)malloc(sizeof(struct Node));
  struct Node* fifth = (struct Node*)malloc(sizeof(struct Node));
  head -> data = 0;
  head -> next = first;
  first -> data = 1;
  first -> next = second;
  second -> data = 2;
  second -> next = third;
  third -> data = 3;
  third -> next = fourth;
  fourth -> data = 4;
  fourth -> next = fifth;
  fifth -> data = 5;
  fifth -> next = NULL;
  return 0;
  printf("before delition\n");
  triversal(head);
  head = delition_inbeginning(head);
  printf("after delition\n");
  triversal(head);
}
