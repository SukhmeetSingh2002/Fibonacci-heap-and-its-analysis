#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<time.h>
#define INT_MIN -50000
#define INT_MAX 80000

double time_spent=0;

int left(int*a,int i)
{
    return ((2*(++i))-1);    
}
int right(int*a,int i)
{
    return (((2*(++i))+1)-1);
}
int parent(int*a,int i)
{
    return (((++i)/2)-1);
}

void minHeapyfy(int *a,int i,int *heapSize)
{
    int leftChild=left(a,i),rightChild=right(a,i),temp=0,smallest=i;
    if(leftChild<*heapSize && a[i]>a[leftChild])//left child is smaller
    {
        smallest=leftChild;
    }
    if(rightChild<*heapSize && a[smallest]>a[rightChild])//right child is smaller
    {
        smallest=rightChild;
    }
    if(smallest!=i)
    {
        temp=a[i];
        a[i]=a[smallest];
        a[smallest]=temp;
        minHeapyfy(a,smallest,heapSize);
    }
}


void builMinHeap(int *a,int *heapSize)
{
    for (int i = *(heapSize)-1; i >= 0; i--)
    {
        minHeapyfy(a,i,heapSize);
    }
    
}

void decreaseKey(int i, int *a, int new_val)
{
    int temp;
    a[i]=new_val;
    while(i!=0 && a[parent(a,i)]>a[i])
    {
       temp=a[i];
       a[i]=a[parent(a,i)];
       a[parent(a,i)]=temp;
       i=parent(a, i);
    }
}
void insertNode(int **a, int* n, int Key,int *size){
    *n = *n + 1;
    if(*n>*size){
        *a=(int*)realloc(*a,(*n)*sizeof(int));
        *size=*n;
    }
    (*a)[*n - 1] = INT_MAX;
    decreaseKey(*n - 1,*a,Key);
}


int extractMin(int *a,int *heapSize)
{
    int minElt;
    if(*heapSize<=0)
    {
        printf("Underflow\n");
    }
    else
    {
        minElt=a[0];
        a[0]=a[*heapSize-1];
        *heapSize=*heapSize-1;
        minHeapyfy(a,0,heapSize);
    }
    return minElt;
}

int * bin_union(int *a,int* b, int x, int y,int* size){
    int *c = (int*)malloc((x+y)*sizeof(int));
    for(int i=0;i<x;i++)    c[i]=a[i];
    for(int i=0;i<y;i++)    c[i+x]=b[i];
    *size=x+y;
    return c;
}

int search(int *heap,int i,int n,int key){
    if(i>=n){
        return -1;
    }
    else if(heap[i]==key)
        return i;
    else{
        int x=search(heap,left(heap,i),n,key);
        if(x==-1)   x=search(heap,right(heap,i),n,key);
        return x;
    }
}

void delete_key(int*a,int index, int *n){
    decreaseKey(index,a,INT_MIN);
    extractMin(a,n);
}

int main()
{
    // FILE *fileOut;
    // FILE *fileIN;
    // fileOut = freopen("output.txt", "w", stdout);
    // fileIN = freopen("INSERT_UNION_BINARY.txt", "r", stdin);
    printf("please enter number of heaps you want to make: ");
    int k;
    scanf("%d",&k);
    // allocating memory  
    int **heap = (int **)malloc(k*sizeof(int*));
    int * n=(int*)malloc(k*sizeof(int));
    int *size=(int*)malloc(k*sizeof(int));
    for(int i=0;i<k;i++){
        heap[i]=NULL;
        n[i]=0;
        size[i]=0;
    }
    printf("Heaps are made and referenced form 0 to %d \n",k-1);
    int ref=-1;
    do{
        printf("Please enter heap reference number to continue operations\nenter -1 to exit");
        printf("\nIn case of union please enter reference number in which you need to merge and save\n");
        printf("Enter your choice:\n>>> ");
        scanf("%d",&ref);
        int work = 9;
        if(ref>=0 && ref<k){
            do{
                printf("\nPlease choose your choice\n");
                printf("1: insert\n2: union\n3: extract minimum\n4: decrease key\n5: delete node\n6: print heap\n7: Enter list of numbers and make heap(Only for new heap)\n8: Minimum\n9: exit\nEnter your choice:\n>>> ");
                scanf("%d",&work);
                if(work==1){
                    int value;
                    printf("Enter number to insert: \n>>> ");
                    scanf("%d",&value);
                    clock_t begin=clock();
                    insertNode(heap+ref,n+ref,value,size+ref);
                    clock_t end=clock();
                    time_spent+=(double)(end-begin)/CLOCKS_PER_SEC;
                }
                else if(work==2){
                    int value;
                    printf("Enter second reference value to merge(Note: heap with current referene number is %d):\n>>> ",ref);
                    scanf("%d",&value);
                    clock_t begin=clock();
                    int*temp=bin_union(heap[ref],heap[value],*(n+ref),*(n+value),size+ref);
                    free(heap[ref]);
                    heap[ref]=temp;
                    *(n+ref)=*(n+ref)+*(n+value);
                    builMinHeap(heap[ref],n+ref);
                    clock_t end=clock();
                    time_spent+=(double)(end-begin)/CLOCKS_PER_SEC;
                }
                else if(work==3 && heap[ref]!=NULL && *(n+ref)!=0){
                    clock_t begin=clock();
                    int value=extractMin(heap[ref],n+ref);
                    clock_t end=clock();
                    time_spent+=(double)(end-begin)/CLOCKS_PER_SEC;
                    printf("Minimum extracted is: %d \n",value);
                }
                else if(work==3 && (heap[ref]==NULL || *(n+ref)==0)){
                    printf("Heap is empty\n");
                }
                else if(work==4){
                    int key,newKey;
                    printf("Enter key to decrease value of key:\n>>> ");
                    scanf("%d",&key);
                    int index=search(heap[ref],0,*(n+ref),key);
                    if(index==-1)
                        printf("Key not present\n");
                    else{
                        printf("Enter value of new key:\n>>> ");
                        scanf("%d",&newKey);
                        clock_t begin=clock();
                        decreaseKey(index,heap[ref],newKey);
                        clock_t end=clock();
                        time_spent+=(double)(end-begin)/CLOCKS_PER_SEC;
                        printf("%d was decreased to %d\n",key,newKey);
                    }
                }
                else if(work==5){
                    printf("Enter key to delete node:\n>>> ");
                    int key;
                    scanf("%d",&key);
                    int index=search(heap[ref],0,*(n+ref),key);
                    if(index==-1)
                        printf("Key not present\n");
                    else{
                        clock_t begin=clock();
                        delete_key(heap[ref],index,n+ref);
                        clock_t end=clock();
                        time_spent+=(double)(end-begin)/CLOCKS_PER_SEC;
                        printf("%d was deleted\n",key);
                    }
                }
                else if(work==6){
                    if(*(n+ref)==0)
                        printf("HEAP is empty\n");
                    else{
                        for(int i=0;i<*(n+ref);i++){
                            printf("%d ,",heap[ref][i]);
                        }
                        printf("\n");
                    }
                }
                else if(work==7){
                    if(heap[ref]!=NULL){
                        printf("Heap is already present\n");
                    }
                    else{
                        printf("Enter size of heap:\n>>> ");
                        scanf("%d",n+ref);
                        *(size+ref)=*(n+ref);
                        printf("Enter elements in heap with spaces seperating them or in new line:\n");
                        heap[ref]=(int*)malloc((*n)*sizeof(int));
                        for(int i=0;i<(*(n+ref));i++)
                            scanf("%d",heap[ref]+i);
                        builMinHeap(heap[ref],n+ref);
                    }
                }
                else if(work==8){
                    if(*(n+ref)!=0)
                        printf("Minimum element is %d\n",heap[ref][0]);
                    else
                        printf("Empty Heap");
                }
                else if(work==9){
                    printf("Exiting function...\n");
                    work=9;
                }
                else{
                    printf("Please Enter a valid entry\n");
                    work=10;
                }
            }while(work!=9);
        }
    }while(ref!=-1);
    printf("Total time spent : %f\n",time_spent);
    // freeing memory
    for(int i=0;i<k;i++){
        if(heap[i]!=NULL)   free(heap[i]);
    }
    free(heap);
    free(n);
    // fclose(fileIN);
    // fclose(fileOut);
    return 0;
}
