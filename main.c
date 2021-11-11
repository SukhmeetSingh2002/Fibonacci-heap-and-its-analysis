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

heap *make_heap()
{
    heap* temp=(heap*)malloc(sizeof(heap));
    temp->min=NULL;
    temp->n=0;
    return temp;
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

heap* fib_heap_union(heap*h1,heap*h2)
{
    heap*temp=make_heap();
    temp->min=h1->min;
    temp->n=h1->n+h2->n;
    if (h1->min == NULL || (h2->min != NULL && (h2->min->key < h1->min->key)))
        temp->min=h2->min;
    return temp;
}


int main()
{
    fibHeap = (heap *)malloc(sizeof(heap));
}