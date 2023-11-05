#define next ptr_to_next_node
#define prev ptr_to_prev_node

void insert(Node **C, char c)
{
    Node *cur = (*C);
    Node *b = (Node*)malloc(sizeof(Node));
    b->character = c;
    Node *a = cur->next;
    b->next = a;
    a->prev = b;
    cur->next = b;
    b->prev = cur;
}

void deletion(Node **C)
{
    Node *cur = (*C);
    if(cur->next == head) return;
    Node *b = cur->next;
    Node *a = b->next;
    cur->next = a;
    a->prev = cur;
    free(b);
}

void backspace(Node **C)
{
    if((*C) == head) return; // !!
    (*C) = (*C)->prev;
	deletion(C);    
}

void go_left(Node **cur, int t)
{
	for(int i = 0; i < t; ++i){
    	(*cur) = (*cur)->prev;
    }    
}

void go_right(Node **cur, int t)
{
	for(int i = 0; i < t; ++i){
    	(*cur) = (*cur)->next;
    }   
}

void go_home(Node **cur)
{
    (*cur) = head;
}

void go_end(Node **cur)
{
    (*cur) = head->prev;
}

