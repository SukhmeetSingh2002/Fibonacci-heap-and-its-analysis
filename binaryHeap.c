#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int left(int *a,int i)
{
    return a[((2*(++i))-1)];    
}
int right(int *a,int i)
{
    return a[(((2*(++i))+1)-1)];
}
int parent(int *a,int i)
{
    return a[(((++i)/2)-1)];
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
    for (int i = *heapSize; i >= 0; i--)
    {
        minHeapyfy(a,i,heapSize);
    }
    
}

void decreaseKey(int i, int *a, int new_val)
{
    int temp;
    a[i]=new_val;
    while(i!=0 && a[parent(i)]>a[i])
    {
       temp=a[i];
       a[i]=a[parent(i)];
       a[parent(i)]=a[i];
       i=parent(a, i);
    }
}

int extractMin(int *a,int *heapSize)
{
    int minElt;
    if(*heapSize<0)
    {
        printf("Underflow\n");
    }
    else
    {
        minElt=a[0];
        a[0]=a[*heapSize-1];
        *heapSize--;
        minHeapyfy(a,0,heapSize);
    }
    return minElt;
}

int main()
{
    int sizeOfHeap=0;

    // allocating memory  
    int *a=(int *)(malloc(sizeOfHeap*sizeof(int)));

    // freeing memory
    free(a);
    return 0;
}
