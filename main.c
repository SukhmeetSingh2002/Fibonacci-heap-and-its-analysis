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

// heap *fibHeap;

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

void insert(heap* fibbHeap,node* newNode)
{
    if (fibbHeap->min == NULL)
        fibbHeap->min = newNode;
    else
    {
        if (fibbHeap->min->right == fibbHeap->min)
        {
            fibbHeap->min->left=newNode;
            fibbHeap->min->right = newNode;
            newNode->left=fibbHeap->min;
            newNode->right=fibbHeap->min;
        }
        else
        {
            newNode->right=fibbHeap->min->right;
            newNode->left=fibbHeap->min;
            fibbHeap->min->right->left=newNode;
            fibbHeap->min->right=newNode;
        }
        if(newNode->key<fibbHeap->min->key)
            fibbHeap->min=newNode;
    }
}

void fib_heap_insert(heap* fibHeap,int key)
{
    node *newNode = allocateMemoryNode();
    newNode->key = key;
    newNode->right=newNode;
    newNode->left=newNode;
    insert(fibHeap,newNode);
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

void cut(heap* h,node* x,node* y){
    if(y->child==x){
        if(x->right==x)
            y->child=NULL;
        else
            y->child=x->right;
    }
    if(y->child!=NULL){
        x->right->left=x->left;
        x->left->right=x->right;
    }
    insert(h,x);
    x->parent=NULL;
    x->mark=false;
}

void cascading_cut(heap* h,node* y){

}

void fib_heap_decrease_key(heap* h,node* x,int k){

}



int main()
{
    // fibHeap = (heap *)malloc(sizeof(heap));
}