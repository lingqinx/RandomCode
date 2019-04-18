#include "Graph.h"
#include "Stack.h"
#include "Queue.h"
#include <stdlib.h>
#include <stdio.h>

// Create a graph.
void CreateGraph(Graph* pgraph, int num)
{
	pgraph->num = num;
	pgraph->heads = (GNode **)malloc(sizeof(GNode*)* num);
	for (int i = 0; i < num; i++) {
		// Make a dummy node.
		pgraph->heads[i] = (GNode *)malloc(sizeof(GNode));
		pgraph->heads[i]->next = NULL;
	}
}

// Destroy a graph.
void DestroyGraph(Graph* pgraph)
{
	GNode* cur, * temp;
	for (int i = 0; i < pgraph->num; i++) {
		cur = pgraph->heads[i];
		while (cur != NULL) {
			temp = cur;
			cur = cur->next;
			free(temp);
		}
	}

	free(pgraph->heads);
}

// Add an undirected edge from src to dest.
void AddEdge(Graph* pgraph, int src, int dest)
{
	GNode* newNode1, *newNode2, *cur;
	
	newNode1 = (GNode *)malloc(sizeof(GNode));
	newNode1->id = dest;
	newNode1->next = NULL;

	// Create a node for dest in src.
	cur = pgraph->heads[src];
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = newNode1;

	// Create a node for src in dest.
	newNode2 = (GNode *)malloc(sizeof(GNode));
	newNode2->id = src;
	newNode2->next = NULL;

	cur = pgraph->heads[dest];
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = newNode2;
}

// Print a graph for each vertex.
void PrintGraph(Graph* pgraph)
{
	GNode* cur;
	for (int i = 0; i < pgraph->num; i++)
	{
		printf("%d: ", i);
		cur = pgraph->heads[i]->next;
		while (cur != NULL)
		{
			printf("%d ", cur->id);
			cur = cur->next;
		}
		printf("\n");
	}
}

// Depth first search
void DFS(Graph* pgraph)
{
	Stack stack;
	bool* visited = (bool *)malloc(sizeof(bool)* pgraph->num);
	for (int i = 0; i < pgraph->num; i++)
		visited[i] = false;	// Make all vertices unvisited.

	InitStack(&stack);
	Push(&stack, 0);	// Push the initial vertex.
	while (!IsSEmpty(&stack)) {
		GNode* cur;
		int vtx = SPeek(&stack);
		Pop(&stack);
		
		// Skip if the vertex has been visited.
		if (visited[vtx]) continue;
		else {
			visited[vtx] = true;
			printf("%d ", vtx);
		}

		// Push the vertex if it has been unvisited.
		cur = pgraph->heads[vtx]->next;
		while (cur != NULL)  {
			if (!visited[cur->id])
				Push(&stack, cur->id);
			cur = cur->next;
		}
	}
}

// Breadth first search
void BFS(Graph* pgraph)
{
	Queue queue;
	bool* visited = (bool *)malloc(sizeof(bool)* pgraph->num);
	for (int i = 0; i < pgraph->num; i++)
		visited[i] = false;	// Make all vertices unvisited.

	InitQueue(&queue);
	EnQueue(&queue, 0);	// Enqueue the initial vertex.
	while (!IsQEmpty(&queue)) {
		GNode* cur;
		int vtx = QPeek(&queue);
		DeQueue(&queue);

		// Skip if the vertex has been visited.
		if (visited[vtx]) continue;
		else {
			visited[vtx] = true;
			printf("%d ", vtx);
		}

		// Enqueue the vertex if it has been unvisited.
		cur = pgraph->heads[vtx]->next;
		while (cur != NULL)  {
			if (!visited[cur->id])
				EnQueue(&queue, cur->id);
			cur = cur->next;
		}
	}
}