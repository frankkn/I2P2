#include <stdio.h>

typedef struct _Node{
	int number;
    struct _Node* l;
    struct _Node* r;
} Node;

int n;

int search(int *in, int *post, int size){
	int idx = 0;
    while(in[idx] != post[size-1]){
    	idx++;
    }
	return idx;
}

Node* buildTree(int *in, int *post, int size){
	if(size <= 0)	return NULL;
    Node* tree_node = (Node*)malloc(sizeof(Node));
    tree_node->number = post[size-1];
    int in_mid = search(in, post, size);
    tree_node->l = buildTree(in, post, in_mid);
    tree_node->r = buildTree(in+in_mid+1, post+in_mid, size-in_mid-1); // !!!
    return tree_node;
}

void showPreorder(Node *root){
	if(root == NULL)	return;
    printf("%d ", root->number);
    showPreorder(root->l);
    showPreorder(root->r);
}

void freeTree(Node* root){
	if(root == NULL)	return;
	freeTree(root->l);
    freeTree(root->r);
    free(root);
}

int main(){
	int id = 1;
    while( scanf("%d", &n) != EOF ){
        int in[101], post[101];
    	for(int i = 0; i < n; ++i) scanf("%d", &in[i]);
        for(int i = 0; i < n; ++i) scanf("%d", &post[i]);
        Node* root = buildTree(in, post, n);
        printf("testcase%d: ", id++);
        showPreorder(root);
        printf("\n");
        freeTree(root);
    }
	return 0;
}