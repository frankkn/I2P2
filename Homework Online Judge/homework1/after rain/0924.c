#include <stddef.h>

void insert(Node**, char*, int);
void erase1(Node**, int);
void erase2(Node**, char*);
void reverse(Node**, int, int);

void insert(Node** head, char* color, int idx){
	Node* cur = (*head);
    for(int i = 0; cur->next!=NULL && i < idx; i++){
    	cur = cur->next;
    }
    Node* newnode = (Node*)malloc(sizeof(Node));
    strcpy(newnode->color, color);
    newnode->next = cur->next;
    cur->next = newnode;
}

void erase1(Node** head, int idx){
	Node* cur = (*head), *prev = NULL;
    if(cur->next == NULL)	return;
    for(int i = 0; cur->next!=NULL && i < idx; i++){
    	prev = cur;
        cur = cur->next;
    }
    prev->next = cur->next;
    free(cur);
}

void erase2(Node** head, char* color){
	Node* cur = (*head), *prev = NULL;
    while(cur){
    	if(!strcmp(cur->color, color)){
        	prev->next = cur->next;
            free(cur);
            cur = prev;
        }
        prev = cur;
        cur = cur->next;
    }
}

void reverse(Node** head, int dest1, int dest2){
	Node* cur = (*head), *start_prev = NULL;
    for(int i = 0; cur->next != NULL && i < dest1; i++){
    	start_prev = cur;
        cur = cur->next;
    }
    Node* follow = cur->next;
    for(int i = dest1; cur->next != NULL && i < dest2; i++){
    	cur->next = follow->next;
        follow->next = start_prev->next;
        start_prev->next = follow;
    	//cur = cur->next;
        follow = cur->next;
    }