#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int key;
    struct node *parent;
    struct node *child;
    struct node *left;
    struct node *right;
    int degree;
    bool mark;
} node;

typedef struct heap
{
    node *min;
    int n;
} heap;

heap *MAKE_HEAP()
{
}

node* allocateMemoryNode()
{
    node* temp=(node* )malloc(sizeof(node));
    temp->degree=0;
    temp->parent=NULL;
    temp->child=NULL;
    return temp;
}


int main()
{
}