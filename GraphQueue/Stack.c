#include "stack.h"
#include <stdlib.h>

// Make stack empty.
void InitStack(Stack *pstack)
{
	pstack->top = -1;
}

// Check whether stack is full.
bool IsSFull(Stack *pstack)
{
	return pstack->top == MAX_STACK - 1;
}

// check whether stack is empty
bool IsSEmpty(Stack *pstack)
{
	return pstack->top == -1;
}

// Read the item at the top.
Data SPeek(Stack *pstack)
{
	if (IsSEmpty(pstack))
		exit(1); //error: empty stack
	return pstack->items[pstack->top];
}

// Insert an item at the top.
void Push(Stack *pstack, Data item)
{
	if (IsSFull(pstack))
		exit(1); //error: stack full
	pstack->items[++(pstack->top)] = item;
}


// Remove the item at the top.
void Pop(Stack *pstack)
{
	if (IsSEmpty(pstack))
		exit(1); //error: empty stack
	--(pstack->top);
}