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