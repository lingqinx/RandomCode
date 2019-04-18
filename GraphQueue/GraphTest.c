#include "Graph.h"
#include <stdio.h>

int main()
{
	Graph g;
	CreateGraph(&g, 5);

	AddEdge(&g, 0, 1);
	AddEdge(&g, 0, 2);
	AddEdge(&g, 0, 4);
	AddEdge(&g, 1, 2);
	AddEdge(&g, 2, 3);
	AddEdge(&g, 2, 4);
	AddEdge(&g, 3, 4);

	PrintGraph(&g);
	DFS(&g);
	printf("\n");
	BFS(&g);
	
	DestroyGraph(&g);

	return 0;
}
