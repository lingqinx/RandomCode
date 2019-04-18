#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct Node
{
	ElemType data;				
	struct Node *next;	
}Node,*LinkedList;

LinkedList Linsert(LinkedList L,ElemType x)
{							
	Node *p;
	p = (Node *)malloc(sizeof(Node));	 
	p->data = x;						 
	p->next = L->next;					 
	L->next = p; 
 
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
	LinkedList list,start;
	Node *L;
	L = (Node *)malloc(sizeof(Node));	
	if(L == NULL)					
		printf("fail to malloc\n");
	L->next = NULL;
	Linsert(L, 1);
	Linsert(L, 4);
	Linsert(L, 3);
	for(start = L->next; start != NULL; start = start->next)
		printf("%d ",start->data);
	printf("\n");
	LRemove(L,4); 
	for(start = L->next; start != NULL; start = start->next)
		printf("%d ",start->data);
	printf("\n");
	
	return 0;
}