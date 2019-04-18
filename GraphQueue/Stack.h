#ifndef _STACK_H
#define _STACK_H

#define MAX_STACK	100

#include "Graph.h"

typedef struct {
	Data items[MAX_STACK];
	int top;
} Stack;

// Make stack empty.
void InitStack(Stack *pstack);

// Check whether stack is full.
bool IsSFull(Stack *pstack);

// check whether stack is empty
bool IsSEmpty(Stack *pstack);

// Read the item at the top.
Data SPeek(Stack *pstack);

// Insert an item at the top.
void Push(Stack *pstack, Data item);

// Remove the item at the top.
void Pop(Stack *pstack);

#endif