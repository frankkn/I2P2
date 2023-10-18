#include <string.h>

void insert(Node**, char*, int);
void erase1(Node**, int);
void erase2(Node**, char*);
void reverse(Node**, int, int);

void insert(Node** head, char* color, int idx){
    Node *cur = (*head);
    for(int i = 0; cur->next != NULL && i < idx; ++i){ // cur->next != NULL !!
    	cur = cur->next;
    }
	Node* node = (Node*)malloc(sizeof(Node));
    strcpy(node->color, color);
    node->next = cur->next;
    cur->next = node;
}

void erase1(Node** head, int idx){
	Node *cur = (*head), *prev = NULL;
    if(cur->next == NULL) return; // !!
    for(int i = 0; cur->next != NULL && i < idx; ++i){
    	prev = cur;
    	cur = cur->next;
    }
    Node *tmp = cur->next;
    prev->next = tmp;
    free(cur);
}

void erase2(Node** head, char* color){
	Node *cur = (*head), *prev = NULL;
    while(cur){ // !!
    	if(!strcmp(cur->color, color)){
        	prev->next = cur->next;
            free(cur);
        	cur = prev;
        }
        prev = cur;
        cur = cur->next;
    }
}
           
void reverse(Node** head, int d1, int d2){
	Node *cur = (*head), *sp = NULL;
    for(int i = 0; cur->next != NULL && i < d1; ++i){
    	sp = cur;
        cur = cur->next;
    }
    Node *follow = cur->next;
    for(int i = d1; cur->next != NULL && i < d2; ++i){
        cur->next = follow->next;
        follow->next = sp->next;
        sp->next = follow;
        follow = cur->next;
    }
}