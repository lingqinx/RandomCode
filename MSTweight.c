#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>
int V;
 
int minKey(int key[], int mstSet[])
{
   // Initialize min value
   int min = INT_MAX, min_index;
 
   for (int v = 0; v < V; v++)
     if (mstSet[v] == 0 && key[v] < min)
         min = key[v], min_index = v;
 
   return min_index;
}
void primMST(double **graph)
{
     int parent[V]; // Array to store constructed MST
     int key[V];   // Key values used to pick minimum weight edge in cut
     int mstSet[V]; 
     double Cost = LONG_MAX; 
     for (int i = 0; i < V; i++){
        key[i] = INT_MAX, mstSet[i] = 0;
     }
        
     key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
     parent[0] = -1; 
     for (int count = 0; count < V-1; count++)
     {
        int u = minKey(key, mstSet);
 
        // Add the picked vertex to the MST Set
        mstSet[u] = 1;
        for (int v = 0; v < V; v++){
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] <  key[v])
                parent[v]  = u, key[v] = graph[u][v];

        } 
        
     }
    double sumEdge = 0 ;
    for (int i = 0; i < V; i++)
        sumEdge = sumEdge + (double)graph[i][parent[i]]; 
        
    if(sumEdge < Cost)
        Cost = sumEdge;
    if(Cost == LONG_MAX) //no 2nd mst possible at all.
        printf("-1");
    else{
        Cost = (int)(Cost*100+0.5)/100.0;
        printf("%.2lf\n",Cost);
    }
}
int main()
{   
    int countVertices,countEdges;
    
    
    scanf("%d",&countVertices);
    V= countVertices;
    int vertex[V][2];
    for( int i=0; i<V;i++){
        int a,b;
        scanf("%d %d",&a,&b);
        vertex[i][0] = a;
        vertex[i][1] = b;
    }
    countEdges = (countVertices*(countVertices-1))/2;
    double *arr[countEdges];
    for (int i=0; i<countEdges; i++)
        arr[i] = (double *)malloc(countEdges * sizeof(double));

    for (int i = 0; i <  countEdges; i++)
     for (int j = 0; j < countEdges; j++)
        arr[i][j] = 0;

    for(int i=0;i<V;i++)
        for(int j=i+1; j<V;j++){
            arr[i][j] = sqrt((vertex[i][0]-vertex[j][0])*(vertex[i][0]-vertex[j][0])+(vertex[i][1]-vertex[j][1])*(vertex[i][1]-vertex[j][1]));
            arr[j][i] = arr[i][j];
        }
    primMST(arr);
    
    for(int i=0;i<countEdges;i++){
        free(arr[i]);
    }
  
    return 0;
}