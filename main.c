#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include<time.h>
#define INT_MIN -50000


double time_spent=0;
typedef struct node
{
    int key;
    struct node *parent;
    struct node *child;
    struct node *left;
    struct node *right;
    int degree;
    bool mark;
    bool found;
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
    temp->found=false;
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
    if(h1->min != NULL && h2->min != NULL){
        node* temp1=h1->min->right;
        node* temp2=h2->min->left;
        h1->min->right=h2->min;
        h2->min->left=h1->min;
        temp1->left=temp2;
        temp2->right=temp1;}
    if (h1->min == NULL || (h2->min != NULL && (h2->min->key < h1->min->key)))
        temp->min=h2->min;
    return temp;
}

void cut(heap* h,node* child,node* parent){
    if(parent->child==child){
        if(child->right==child)
            parent->child=NULL;
        else
            parent->child=child->right;
    }
    if(parent->child!=NULL){
        child->right->left=child->left;
        child->left->right=child->right;
    }
    insert(h,child);
    child->parent=NULL;
    child->mark=false;
    parent->degree--;
}

void cascading_cut(heap* fibHeap,node* y)
{
    node* parent=y->parent;
    if(parent!=NULL)
    {
        if(y->mark==false)
            y->mark=true;
        else
        {
            cut(fibHeap,y,parent);
            cascading_cut(fibHeap,parent);
        }
        
    }
}


void fib_heap_decrease_key(heap* fibHeap, node* oldNode, int newKey)
{
    if (fibHeap->min==NULL)
    {
        printf("\nHeap empty.");
    }
    else if(oldNode->key < newKey)
    {
        printf("\nThe new value is greater than the current value.");
    }
    else
    {
        oldNode->key=newKey;
        node* temp=oldNode->parent;
        if( temp!=NULL && ((oldNode->key)<(temp->key)) ) 
        {
            cut(fibHeap,oldNode,temp);
            cascading_cut(fibHeap,temp);
        }
        if( oldNode->key < fibHeap->min->key )
        {
            fibHeap->min=oldNode;
        }
    }
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

int degree(heap*h){
    return (int)(log2(h->n))+1;
}

void heap_consolidate(heap* H){
    int k=degree(H);
    node** x;
    x=(node**)malloc((k+1)*sizeof(node*));
    for(int i=0;i<=k;i++){
        x[i]=NULL;
    }
    node*temp2=H->min;
    node* temp1=temp2;
    do{
        int d=temp2->degree;
        while(x[d]!=NULL){
            node*temp3=x[d];
            if(temp2->key>temp3->key){
                node* temp5=temp3;
                temp3=temp2;
                temp2=temp5;
            }
            Fibonnaci_link(H,temp3,temp2);
            if(temp1==temp3)
                temp1=temp2;
            x[d]=NULL;
            d++;
        }
        x[d]=temp2;
        temp2=temp2->right;
    }while(temp2!=temp1);
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

int Extract_min(heap* fibHeap)
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
        return temp->key;
    }
}



void search(heap* fibHeap,node* fibHeapNode,int value,int newKey,int *done)
{
    node *temp=fibHeapNode;
    temp->found=true;
    if(temp->key==value)
    {
        *done=1;
        temp->found=false;
        clock_t begin=clock();
        fib_heap_decrease_key(fibHeap,temp,newKey);
        clock_t end=clock();
        time_spent+=(double)(end-begin)/CLOCKS_PER_SEC;
        return;
    }
    else
    {
        if(temp->child!=NULL)
            search(fibHeap,temp->child,value,newKey,done);
        if(!temp->right->found)
            search(fibHeap,temp->right,value,newKey,done);
    }
    temp->found=false;
    
}

void fib_heap_delete(heap* h,int key,int *done){
    search(h,h->min,key,INT_MIN,done);
    clock_t begin=clock();
    int temp=Extract_min(h);
    clock_t end=clock();
    time_spent+=(double)(end-begin)/CLOCKS_PER_SEC;
}

void print(node* n,char* s,int dep){
    node*temp=n;
    s[dep]='\\';
    s[++dep]='\0';
    do{
        printf("%s         %d\n",s,temp->key);
        if(temp->child!=NULL)
            print(temp->child,s,dep);
        temp=temp->right;
    }while(temp!=n);
}

int main(){
    // FILE *fileOut;
    // FILE *fileIN;
    // fileOut = freopen("output.txt", "w", stdout);
    // fileIN = freopen("INSERT_UNION_FIB.txt", "r", stdin);
    heap** fibheap;
    printf("Please enter number of fibonacci heaps you want to make:\n>>> ");
    int n;
    scanf("%d",&n);
    fibheap=(heap**)malloc(n*sizeof(heap*));
    for(int i=0;i<n;i++)
        fibheap[i]=make_heap();
    printf("Heaps are made and referenced form 0 to %d \n",n-1);
    int ref=-1;
    do{
        printf("Please enter heap reference number to continue operations\nEnter -1 to exit");
        printf("\nIn case of union please enter reference number in which you need to merge and save\n");
        printf("Enter your choice:\n>>> ");
        scanf("%d",&ref);
        int work = 8;
        if(ref>=0 && ref<n){
            do{
                printf("\nPLease choose your choice\n");
                printf("\n1: insert\n2: union\n3: extract minimum\n4: decrease key\n5: delete node\n6: print heap\n7: Minimum\n8: exit\nEnter your choice:\n>>> ");
                scanf("%d",&work);
                if(work==1){
                    int value;
                    printf("Enter number to insert: \n>>> ");
                    scanf("%d",&value);
                    clock_t begin=clock();
                    fib_heap_insert(fibheap[ref],value);
                    clock_t end=clock();
                    time_spent+=(double)(end-begin)/CLOCKS_PER_SEC;
                }
                else if(work==2){
                    int value;
                    printf("Enter second reference value to merge(Note: heap with current referene number is %d):\n>>> ",ref);
                    scanf("%d",&value);
                    clock_t begin=clock();
                    fibheap[ref]=fib_heap_union(fibheap[ref],fibheap[value]);
                    clock_t end=clock();
                    time_spent+=(double)(end-begin)/CLOCKS_PER_SEC;
                    printf("Merged %d and %d into %d\n",ref,value,ref);
                }
                else if(work==3 && fibheap[ref]->min!=NULL){
                    clock_t begin=clock();
                    int value=Extract_min(fibheap[ref]);
                    clock_t end=clock();
                    time_spent+=(double)(end-begin)/CLOCKS_PER_SEC;
                    printf("Minimum extracted is: %d \n",value);
                }
                else if(work==3 && fibheap[ref]->min==NULL){
                    printf("Heap is empty\n");
                }
                else if(work==4){
                    int *done=(int*)malloc(sizeof(int));
                    *done=0;
                    int key,newKey;
                    printf("Enter old value of key:\n>>> ");
                    scanf("%d",&key);
                    printf("Enter value of new key:\n>>> ");
                    scanf("%d",&newKey);

                    if(fibheap[ref]->min!=NULL)
                        search(fibheap[ref],fibheap[ref]->min,key,newKey,done);
                    if(fibheap[ref]->min!=NULL && *done==1 && newKey<=key)
                        printf("%d was decreased to %d\n",key,newKey);
                    else if(newKey<=key)
                        printf("Key not present\n");
                }
                else if(work==5){
                    int *done=(int*)malloc(sizeof(int));
                    *done=0;
                    printf("Enter key to delete node:\n>>> ");
                    int key;
                    scanf("%d",&key);

                    if(fibheap[ref]->min!=NULL)
                        fib_heap_delete(fibheap[ref],key,done);
                    if(fibheap[ref]->min!=NULL && *done==1)
                        printf("%d was deleted\n",key);
                    else
                        printf("Key not present\n");
                }
                else if(work==6){
                    if(fibheap[ref]->min!=NULL){
                        char s[100]="";
                        print(fibheap[ref]->min,s,0);
                    }
                    else{
                        printf("HEAP is empty\n");
                    }
                }
                else if(work==7){
                    if(fibheap[ref]->n!=0)
                        printf("Minimum element is %d\n",fibheap[ref]->min->key);
                    else
                        printf("Empty Heap");
                }
                else if(work==8){
                    printf("Exiting function...\n");
                }
                else{
                    printf("Please Enter a valid entry\n");
                    work=10;
                }
            }while(work!=8);
        }
    }while(ref!=-1);
    printf("\nSuccessfully executed all operations.\n");
    printf("%f",time_spent);
    // printf("\nSuccessfully executed all operations.\n");
    // fclose(fileOut);
    // fclose(fileIN);
    return 0;
}
