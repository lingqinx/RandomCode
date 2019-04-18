#ifndef _GRAPH_H
#define _GRAPH_H

typedef enum { false, true } bool;
typedef int Data;

// Adjacency List Node
typedef struct _GNode
{
	int id;
	struct _GNode* next;
} GNode;

typedef struct 
{
	int num;
	GNode** heads;
} Graph;

// Create a graph.
void CreateGraph(Graph* pgraph, int num);
// Destroy a graph.
void DestroyGraph(Graph* pgraph);
// Add an undirected edge from src to dest.
void AddEdge(Graph* pgraph, int src, int dest);
// Print a graph for each vertex.
void PrintGraph(Graph* pgraph);

// Depth first search
void DFS(Graph* pgraph);
// Breadth first search
void BFS(Graph* pgraph);

#endif _GRAPH_H