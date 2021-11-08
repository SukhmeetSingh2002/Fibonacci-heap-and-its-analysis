#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct node{
    int x;
    struct node* p;
    struct node* left;
    struct node* right;
    int degree;
    bool mark;
}node;

typedef struct heap{
    node* min;
    int n;
}heap;

heap* MAKE_HEAP(){

}



int main(){

}