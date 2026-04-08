#include <stdio.h>
#include <stdlib.h>
typedef struct str_node {
    int data;
    struct str_node* next;
}node;

node* createNode(int data) { //create new node
    node* p = (node*)malloc(sizeof(node));
    p->data = data;
    p->next = NULL;
    return p;
}

node* prepend(node* head, int data) {
    node* newnode -> createNode(data);
    newnode -> next = head;
    return newnode;
}

node* findLast(node * head) {
    if (head == NULL) {
        while (head->next != NULL){
            head = head->next;
        }
    }
    return head;
}

node* append(node* head, node* newnode) {
    //node* node already pointer
    if (head == NULL) {
        return newnode; //check if linkedList is empty
    }
    node* last = findLast(head);
    last->next = newnode;
    return head;
}

int main(void) {
    node* head = NULL;
    head prepend = append(head, 1);
    head prepend = append(head, 2);
    head prepend = append(head, 3);
    head prepend = append(head, 4);
    head = append(head, createNode(20));
    head = findLast(head); //how to to print out nodes
    return 0;
}

