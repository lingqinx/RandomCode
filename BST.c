#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
typedef int Elemtype;
 
typedef struct BiTNode{
    Elemtype data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;
 
void BSTInsert( BiTree *t, Elemtype element )
{
    if( NULL == *t ) {
        (*t) = (BiTree)malloc(sizeof(BiTNode));
        (*t)->data = element;
        (*t)->lchild = (*t)->rchild = NULL;
    }
 
    if( element == (*t)->data )
        return ;
 
    else if( element < (*t)->data )
        BSTInsert( &(*t)->lchild, element );
 
    else 
        BSTInsert( &(*t)->rchild, element );
}
 
void CreateBST( BiTree *t, Elemtype *a, int n )
{
    (*t) = NULL;
    for( int i=0; i<n; i++ )
        BSTInsert( t, a[i] );
}
 
void SearchBST( BiTree t, Elemtype key )
{
    BiTree p;
    p = t;
    if( p ) {
        printf("%d  ", p->data);
        if( key == p->data ){
            printf("\nthe data %d is found\n", p->data);
        }
        else if( (key < p->data) && (NULL != p->lchild) )
            SearchBST( p->lchild , key );
        else if( (key > p->data) && (NULL != p->rchild) )
            SearchBST( p->rchild , key );
        else
            printf("\nnot found!\n");
    }
}
 
void DelBSTNode( BiTree t, Elemtype key )
{
    BiTree p, q;
    p = t;
    Elemtype temp;
    while( NULL != p && key != p->data ) {
        q = p;
        if( key < p->data )
            p = p->lchild ;
        else
            p = p->rchild ;
    }
 
    if( NULL == p )
        printf("no this data!\n");
    else {
        if( NULL == p->lchild && NULL == p->rchild ) {
            if( p == q->lchild )
                q->lchild = NULL;
            if( p == q->rchild )
                q->rchild = NULL;
            free(p);
            p = NULL;
        }
        else if( (NULL == p->rchild && NULL != p->lchild) ) {  
            if( p == q->lchild )
                q->lchild = p->lchild ;
            else if( p == q->rchild )
                q->rchild = p->lchild ;
            free(p);
            p = NULL;
        }
        else if( NULL == p->lchild && NULL != p->rchild ) {   
            if( p == q->lchild )
                q->lchild = p->rchild ;
            if( p == q->rchild )
                q->rchild = p->rchild ;
            free(p);
            p = NULL;
        }
    
        else if( NULL != p->lchild && NULL != p->rchild ) {
                BiTree s, sParent; 
                sParent = p;
                s = sParent->lchild ;
                while( NULL != s->rchild )  { 
                    sParent = s;
                    s = s->rchild ; 
                }
                temp = s->data ;    
                DelBSTNode( t, temp );
                p->data = temp;
        }
    }
 
}
 

void InorderPrintBST( BiTree t )
{
    if( t ) {
        InorderPrintBST( t->lchild );
        printf("%d ", t->data);
        InorderPrintBST( t->rchild );
    }
}
 
int main()
{
    int n;
    int *a;
    Elemtype key;
    BiTree t;
    srand(time(NULL));
    int array[20];
    for (int i=0; i<20; i++){

        array[i] = rand()%50;
    } 
    CreateBST( &t, array, 20 );
    printf("inorder traversal:\n");
    InorderPrintBST( t );
    printf("\n\n");
    
    printf("search 15:\n");
    SearchBST( t, 15 );  
    printf("search 8:\n");
    SearchBST( t, 8 );  
    printf("search 18:\n");
    SearchBST( t, 18 ); 
    printf("\n\n");

    printf("insert 5:\n");
    BSTInsert(&t, 5);
    InorderPrintBST( t );
    printf("\n");
    printf("insert 7:\n");
    BSTInsert(&t, 7);
    InorderPrintBST( t );
    printf("\n");
    printf("insert 17:\n");
    BSTInsert(&t, 17);
    InorderPrintBST( t );
    printf("\n");
    printf("insert 51:\n");
    BSTInsert(&t, 51);
    InorderPrintBST( t );
    printf("\n\n");


    printf("delete 17:\n");
    DelBSTNode(t, 17);
    InorderPrintBST( t );
    printf("\n");
    printf("delete 5:\n");
    DelBSTNode(t, 5);
    InorderPrintBST( t );
    printf("\n");
    printf("delete 51:\n");
    DelBSTNode(t, 51);
    InorderPrintBST( t );
    printf("\n");
    printf("delete 17:\n");
    DelBSTNode(t, 17);
    InorderPrintBST( t );
    printf("\n");

    return 0;
}