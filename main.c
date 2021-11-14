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


void Fibonnaci_link(heap* fibHeap,node* p2, node* p1)
{
    (p2->left)->right=p2->right;
    (p2->right)->left=p2->left;
    if(p1->right==p1)
    {
        fibHeap->min=p1;
    }
    p2->left=p2;
    p2->right=p2;
    p2->parent=p1;
    if(p1->child==NULL)
    {
        p1->child=p2;
    }
    else
    {
        p2->right=p1->child;
        p2->left=(p1->child)->left;
        ((p1->child)->left)->right=p2;
        (p1->child)->left=p2;
    }
    if(p2->key<(p1->child)->key)
    {
        p1->child = p2;
    }
    p1->degree+=1;
    p2->mark=false;
}

void heap_consolidate(heap* H){
    int k=degree(H);
    node** x;
    x=(node**)malloc((k+1)*sizeof(node*));
    for(int i=0;i<=k;i++){
        x[i]=NULL;
    }
    node*temp=H->min;
    node* temp1=temp;
    do{
        node* temp2=temp;
        int d=temp2->degree;
        while(x[d]!=NULL){
            node*temp3=x[d];
            if(temp2->key>temp3->key){
                node* temp5=temp3;
                temp3=temp2;
                temp2=temp5;
            }
            Fibonnaci_link(H,temp3,temp2);
            x[d]=NULL;
            d++;
        }
        x[d]=temp2;
        temp=temp->right;
    }while(temp!=temp1);
    H->min=NULL;
    for(int i=0;i<=k;i++){
        if(x[i]!=NULL){
            if(H->min==NULL){
                H->min=x[i];
                x[i]->left=x[i];
                x[i]->right=x[i];
            }
            else{
                insert(H,x[i]);
                if(x[i]->key<H->min->key)
                    H->min=x[i];
            }
        }
    }
}

void Extract_min(heap* fibHeap)
{
    if(fibHeap->min!=NULL)
    {
        node *temp=fibHeap->min;
        node *ptr;
        ptr=temp;
        node *x=NULL;
        if(temp->child!=NULL) 
        {
            x=temp->child;
            do
            {
                ptr=x->right;
                (fibHeap->min->left)->right=x;
                x->right=fibHeap->min;
                x->left=fibHeap->min->left;
                fibHeap->min->left=x;
                if( (x->key) < (fibHeap->min->key) )
                {
                    fibHeap->min=x;
                }
                x->parent=NULL;
                x=ptr;
            }while(ptr!=temp->child);
        }
        (temp->left)->right=temp->right;
        (temp->right)->left=temp->left;
        fibHeap->min=temp->right;
        if(temp==temp->right && temp->child==NULL)
            fibHeap->min=NULL;
        else 
        {
            fibHeap->min=temp->right;
            heap_consolidate(fibHeap);
        }
        fibHeap->n--;
    }
}

int main()
{
    // fibHeap = (heap *)malloc(sizeof(heap));
}
