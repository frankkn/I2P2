#define l ptr_to_left_node
#define r ptr_to_right_node

int preorder_index = 0;

int search(int* Inorder, int* Preorder){
	int idx = 0;
    while(Inorder[idx] != Preorder[preorder_index]){
    	idx++;
    }
    return idx;
} 

Node* buildTree(int* Inorder, int* Preorder, int inorder_start, int inorder_end)
{
    if(inorder_start > inorder_end) return NULL;
    Node* tree_node = (Node*)malloc(sizeof(Node));
    tree_node->number = Preorder[preorder_index];
    int inorder_mid = search(Inorder, Preorder);
    preorder_index++;
    tree_node->l = buildTree(Inorder, Preorder, inorder_start, inorder_mid-1);
    tree_node->r = buildTree(Inorder, Preorder, inorder_mid+1, inorder_end);
    return tree_node;
}
void showPostorder(Node* root)
{
    if(root == NULL)	return;
    showPostorder(root->l);
    showPostorder(root->r);
    printf("%d ", root->number);
}

void freeTree(Node *root)
{
    preorder_index = 0; // !!!
    if(root == NULL) return;
    freeTree(root->l);
    freeTree(root->r);
    free(root);
}