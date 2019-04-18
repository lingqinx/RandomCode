#ifndef _QUEUE_H
#define _QUEUE_H

#define MAX_QUEUE	100

#include "Graph.h"

typedef struct {
	int front, rear;
	Data items[MAX_QUEUE];
} Queue;

// Make queue empty.
void InitQueue(Queue *pqueue);
// Check whether queue is full.
bool IsQFull(Queue *pqueue);
// Check whether queue is empty.
bool IsQEmpty(Queue *pqueue);

// Read the item at the front.
Data QPeek(Queue *pqueue);
// Insert an item at the rear.
void EnQueue(Queue *pqueue, Data item);
// Delete an item at the front.
void DeQueue(Queue *pqueue);

#endif _QUEUE_H