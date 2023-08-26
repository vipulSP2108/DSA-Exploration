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

struct Node* delition_inbiginning(struct Node* head){
  struct Node* ptr;
  ptr = head;
  head = head -> next;
  free(ptr);
  return head;
}

struct Node* delition_atend(struct Node* head){
  struct Node* ptr = head;
  while (ptr -> next != NULL){
    ptr = ptr -> next;
  }
  free(ptr);
  return head;
}

struct Node* delition_atindex(struct Node* head, int index){
  struct Node* ptr = head;
  for(int i = 0; i != index-1; i++){
    ptr = ptr -> next;
  }
  struct Node* delition_ptr = ptr -> next;
  ptr -> next = delition_ptr -> next;
  free(delition_ptr);
  return head;
}

struct Node* delition_atNode(struct Node* ptr, struct Node* head){
  struct Node* delition_ptr = ptr;
  ptr = ptr -> next;
  free(delition_ptr);
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
  triversal(head);
  printf("next\n");
  head = delition_inbiginning(head);
  triversal(head);
  printf("next\n");
  head = delition_atend(head);
  triversal(head);
  printf("next\n");
  head = delition_atindex(1, head);
  triversal(head);
  printf("next\n");
  head = delition_atNode(third,head);
  triversal(head);
  printf("next\n");
}
