#include <stdio.h>
#include <stddef.h>

struct _Node{
    int number;
    struct _Node* next;
};

Node *createList(int n)
{
    Node *tail = (Node*)malloc(sizeof(Node));
    tail->number = n;
    tail->next = tail; // !! 
    for(int i = n-1; i >= 1; --i){
    	Node *node = (Node*)malloc(sizeof(Node));
        node->number = i;
        node->next = tail->next;
        tail->next = node;
    }
    return tail->next; // !! 
}

void freeList(Node* head)
{
    while(head->next != head){ // !! 
    	Node *tmp = head->next;
        head->next = tmp->next;
        free(tmp);
    }
    free(head);
}

int getLen(Node* head){
	Node*cur = head;
    int len = 1;
    while(cur->next != head){ // !! 
        len++;
    	cur = cur->next;
    }
	return len;
}

int solveJosephus(Node **head, int step)
{
    for(int len = getLen(*head); len > 1; --len){
        for(int j = (step % len)-2 + len; j > 0; --j){
        	(*head) = (*head)->next;
        }
        Node *tmp= (*head)->next;
        (*head)->next = tmp->next;
    	free(tmp);
        (*head) = (*head)->next; // !!
    }
    return (*head)->number;
}

int main()
{
    int n, k;
    while( scanf("%d%d", &n, &k)!=EOF )
   {
        Node *head;
        head = createList(n);
        printf( "%d\n", solveJosephus(&head, k) );
        freeList(head);
    }
    return 0;
}