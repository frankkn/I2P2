#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
  int val;
  struct _Node *left;
  struct _Node *right;
} Node;

Node * create_node(int x)
{
    Node *np = (Node *) malloc(sizeof(Node));
    np->val = x;
    np->left = NULL;
    np->right = NULL;
    return np;
}

int find(int v, int *in, int si, int ei)
{
  while (si <= ei) {
    if (in[si] == v) {
      return si;
    }
    si++;
  }
  return ei;
}

Node * build_tree(int* pre, int* in, int idx, int si, int ei)
{
  Node *p;
  int fi;
  if (si > ei) {
    return NULL;
  } else {
    /*
    pre-order:  2 7 3 6 8 11 5 9 4
                si         fi      ei
    in-order:   3 7 8 6 11  2  5 9 4
    in-order left: 3 7 8 6 11
    in-order right: 5 9 4
    */
    fi = find(pre[idx], in, si, ei);
    //printf("fi: %d\n", fi);
    p = create_node(pre[idx]);
    p->left  = build_tree(pre, in, idx+1,        si, fi-1);
    p->right = build_tree(pre, in, idx+fi-si+1,  fi+1, ei);
    return p;
  }
}

void show_in_order(Node *tr)
{
  if (tr) {
    show_in_order(tr->left);
    printf("%d ", tr->val);
    show_in_order(tr->right);
  }
}

void show_pre_order(Node *tr)
{
  if (tr) {
    printf("%d ", tr->val);
    show_pre_order(tr->left);
    show_pre_order(tr->right);
  }
}

int main(void)
{
  int *pre;
  int *in;
  int N, i;
  Node *tr;

  scanf("%d", &N);
  pre = (int*) malloc(sizeof(int)*N);
  in = (int*)  malloc(sizeof(int)*N);

  for (i=0; i<N; ++i) {
    scanf("%d", &pre[i]);
  }

  for (i=0; i<N; ++i) {
    scanf("%d", &in[i]);
  }


  tr = build_tree(pre, in, 0, 0, N-1);
  /*
  tr = create_node(2);
  tr->left = create_node(7);
  tr->right = create_node(5);
  tr->left->left = create_node(3);
  tr->left->right = create_node(6);
  //pre-order: 2 7 3 6 8 11 5 9 4
  //in-order:  3 7 8 6 11 2 5 9 4

  */


  show_pre_order(tr);
  printf("\n");

  show_in_order(tr);
  printf("\n");

  return 0;
}