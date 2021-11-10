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
            newNode->left=fibHeap;
            fibHeap->min->right->left=newNode;
            fibHeap->min->right=fibHeap;
        }
        if(newNode->key<fibHeap->min->key)
            fibHeap->min=newNode;
    }
    fibHeap->n=fibHeap->n+1;
}

int main()
{
    fibHeap = (heap *)malloc(sizeof(heap));
}