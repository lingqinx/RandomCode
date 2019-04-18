#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct Node
{
	ElemType data;				
	struct Node *next;	
}Node,*LinkedList;

LinkedList Linsert(Node *r,ElemType x)
{	
	Node *p;
	p = (Node *)malloc(sizeof(Node));	 
	p->data = x;						 
	r->next = p;   
    r = p; 
    return r;
} 

LinkedList LRemove(LinkedList L,ElemType x)
{
	Node *p,*pre;					 
	p = L->next;
	while(p->data != x)				
	{	
		pre = p; 
		p = p->next;
	}
	pre->next = p->next;			 
	free(p);
	return L;
} 


int main()
{
	LinkedList start;
	Node *L;
	L = (Node *)malloc(sizeof(Node));
	L->data=10;	
	L->next = NULL;
	Node *r;
    r = L;
	r = Linsert(r, 1);
	r = Linsert(r, 4);
	r = Linsert(r, 3);
	
	r->next = NULL;
	for(start = L->next; start != NULL; start = start->next)
		printf("%d ",start->data);
	printf("\n");
	LRemove(L,4); 
	for(start = L->next; start != NULL; start = start->next)
		printf("%d ",start->data);
	printf("\n");
	
	return 0;
}