#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    char e;
    struct node *next;
} NODE;

typedef struct queue{
    NODE *head;
    NODE *tail;
} QUEUE;

char init_queue(QUEUE *queue); // 將隊列queue初始化{}
char enqueue(QUEUE *queue, char e); // 將元素e入隊列queue{}
char dequeue(QUEUE *queue, char *e); // 從隊列queue中取出一個元素e，並賦值給*e{}
char display_queue(QUEUE *queue); // 列印隊列中所有元素{}
char clear_queue(QUEUE *queue); // 清空隊列{} 

char init_queue(QUEUE *queue) {
    if(queue == NULL){
        return '0';  // Indicate failure
    }

    queue->head = NULL;
    queue->tail = NULL;

    return '1';  // Indicate success
}

char enqueue(QUEUE *queue, char e) { // Push from back
    NODE *node = (NODE *)malloc(sizeof(NODE));
    node->e = e;
    node->next = NULL;

    if(queue->tail == NULL){
        queue->head = node;
        queue->tail = node;
    }else{
        queue->tail->next = node;
        queue->tail = node;
    }

    return '1';  // Indicate success
}

char dequeue(QUEUE *queue, char *e) { // Pop from front
    if(queue == NULL || queue->head == NULL){
        return '0';  // Indicate failure
    }

    NODE *node = queue->head;
    *e = node->e;

    queue->head = queue->head->next;
    free(node);

    // If the queue is now empty, update tail to NULL
    if(queue->head == NULL){
        queue->tail = NULL;
    }

    return '1';  // Indicate success
}

char display_queue(QUEUE *queue) {
    if(queue == NULL || queue->head == NULL){
        printf("Queue is empty.\n");
        return '0';
    }

    NODE *cur = queue->head;
    printf("Queue elements: ");
    while(cur != NULL){
        printf("%c ", cur->e);
        cur = cur->next;
    }
    printf("\n");
    return '1';
}

char clear_queue(QUEUE *queue) {
    if(queue == NULL){
        return '0';  // Indicate failure
    }

    NODE *cur = queue->head;
    NODE *tmp;

    while(cur != NULL){
        tmp = cur;
        cur = cur->next;
        free(tmp);
    }

    queue->head = NULL;
    queue->tail = NULL;

    return '1';  // Indicate success
}

int main(){
    return 0;
}