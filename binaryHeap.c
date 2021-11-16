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


void minHeapyfy(int *a,int i,int heapSize)
{
    int leftChild=left(a,i),rightChild=right(a,i),temp=0,smallest=i;
    if(leftChild<heapSize && a[i]>a[leftChild])//left child is smaller
    {
        smallest=leftChild;
    }
    if(rightChild<heapSize && a[smallest]>a[rightChild])//right child is smaller
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

void builMinHeap(int *a,int heapSize)
{
    for (int i = heapSize; i >= 0; i--)
    {
        minHeapyfy(a,i,heapSize);
    }
    
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