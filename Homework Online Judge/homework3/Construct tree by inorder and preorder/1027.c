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

int n;
int main(void)
{
    /*
    9
    1 2 3 4 5 6 7 8 9
    5 3 2 1 4 7 6 8 9
    9
    3 7 8 6 11 2 5 4 9
    2 7 3 6 8 11 5 9 4
    */
    int id = 1;
    while( ~scanf( "%d", &n ) )
    {
        int inorder[100], preorder[100];
        for( int i = 0; i < n; i++ )
            scanf( "%d", &inorder[i] );
        for( int i = 0; i < n; i++ )
            scanf( "%d", &preorder[i] );
        Node *root = buildTree( inorder, preorder, 0, n-1 );
        printf( "testcase%d: ", id++ );
        showPostorder( root );
        printf( "\n" );
        freeTree( root );
    }
    return 0;
}