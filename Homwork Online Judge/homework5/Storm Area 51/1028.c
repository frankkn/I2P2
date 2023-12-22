#include <stdio.h>
#include<string.h>
int x, y, z; 
typedef enum{Num, Var, Op}Type;

typedef struct _Node{
	struct _node *l, *r;
    Type type; // 0:Num 1:Var 2:Op
    int val;
    char c; 
}Node;

Node* buildTree(){
	char pre[105]; scanf("%s", pre); // Separate token by space
    Node *now = (Node*)malloc(sizeof(Node));
    if(isdigit(pre[0])){
    	int v = 0, idx = 0;
        while(isdigit(pre[idx])){
        	v *= 10;
            v += (pre[idx] - '0');
            idx++;
        }
    	now->type = Num;
        now->val = v; // v:[1,100]
    }else if(pre[0] == 'x' || pre[0] == 'y' || pre[0] == 'z'){
    	now->type = Var;
        now->c = pre[0];
    }else if(pre[0] == '+' || pre[0] == '-' || pre[0] == '*' || pre[0] == '/'){
    	now->type = Op;
        now->c = pre[0];
    }
    if(now->type != Op) return now; // return leaf node(Num/Var)
    now->l = buildTree();
    now->r = buildTree();
    return now;
}

void freeTree(Node *root){
    if(!root) return;
    freeTree(root->l);
    freeTree(root->r);
    free(root);
}

int traverse(Node *now){
    if(now->type == Num){
    	printf("%d", now->val);
        return now->val;
    }else if(now->type == Var){
    	printf("%c", now->c);
        switch(now->c){
            case 'x': return x;
            case 'y': return y;
            case 'z': return z;
        }
    }else{
    	int left = traverse(now->l);
        printf("%c", now->c);
        int right = traverse(now->r);
        switch(now->c){
            case '+':	return left+right;
            case '-':	return left-right;
            case '*':	return left*right;
            case '/':	return left/right;
        }
    }
}

int main(){
	Node *root = buildTree();
   	scanf("%d %d %d", &x, &y, &z);
    int ans = traverse(root);
    printf("\n%d\n", ans);
    freeTree(root);
	return 0;
}