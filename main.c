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

heap *fibHeap;

heap *MAKE_HEAP()
{
}

node *allocateMemoryNode()
{
    node *temp = (node *)malloc(sizeof(node));
    temp->degree = 0;
    temp->parent = NULL;
    temp->child = NULL;
    temp->mark = false;
    return temp;
}

void fib_heap_insert(int key)
{
    node *newNode = allocateMemoryNode();
    newNode->key = key;
    if (fibHeap->min == NULL)
        fibHeap->min = newNode;
    else
    {
        if (fibHeap->min->right == NULL)
        {
            fibHeap->min->right = newNode;
            newNode->left=fibHeap->min;
            newNode->right=fibHeap->min;
        }
        else
        {
            newNode->right=fibHeap->min->right;
            newNode->left=fibHeap->min;
            fibHeap->min->right->left=newNode;
            fibHeap->min->right=newNode;
        }
        if(newNode->key<fibHeap->min->key)
            fibHeap->min=newNode;
    }
    fibHeap->n=fibHeap->n+1;
}

void Fibonnaci_link(node* p2, node* p1)
{
    (p2->left)->right=p2->right;
    (p2->right)->left=p2->left;
    if(p1->right==p1)
    {
        fibHeap->mini=p1;
    }
    p2->left=p2;
    p2->right=p2;
    p2->parent=p1;
    if(p1->child==NULL)
    {
        p1->child=p2;
    }
    p2->right=p1->child;
    p2->left=(p1->child)->left;
    ((p1->child)->left)->right=p2;
    (p1->child)->left=p2;
    if(p2->key<(p1->child)->key)
    {
        p1->child = p2;
    }
    p1->degree+=1;
}

int main()
{
    fibHeap = (heap *)malloc(sizeof(heap));
}
