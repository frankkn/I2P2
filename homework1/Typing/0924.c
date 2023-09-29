#define next ptr_to_next_node
#define prev ptr_to_prev_node

void insert(Node **C, char c)
{
    Node* cur = (*C);
    Node* b = (Node*)malloc(sizeof(Node));
    b->character = c;
    cur->next->prev = b;
    b->next = cur->next;
    b->prev = cur;
    cur->next = b;
}

void deletion(Node **C)
{
    Node* cur = (*C);
    if(cur->next == head) return;
    Node* b = cur->next;
    cur->next = b->next;
    b->next->prev = cur;
    free(b);
}

void backspace(Node **C)
{
    if((*C) == head) return;
    (*C) = (*C)->prev;
    Node* cur = (*C);
    deletion(&cur);
}

void go_left(Node **C, int t)
{
 	for(int i = 0; i < t; i++){
    	(*C) = (*C)->prev;
    }
}

void go_right(Node **C, int t)
{
    for(int i = 0; i < t; i++){
    	(*C) = (*C)->next;
    }
}

void go_home(Node **C)
{
    (*C) = head;
}

void go_end(Node **C)
{
    (*C) = head->prev;
}