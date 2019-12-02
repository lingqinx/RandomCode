#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
 
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

 
void printSecondMSTWeight(int parent1[],int **graph)
{
   
    int g[V][V]; //local copy of graph
    long secondCost = LONG_MAX;
    
    for (int i = 1; i < V; i++){
        for(int i=0;i<V;i++){
            for(int j=0;j<V;j++){
                g[i][j]=graph[i][j];
            }
        }
        g[i][parent1[i]] = 0;
        g[parent1[i]][i] = 0;
              
        
        int parent[V]; // Array to store constructed MST
        int key[V];   // Key values used to pick minimum weight edge in cut
        int mstSet[V]; 
        for (int i = 0; i < V; i++)
            key[i] = INT_MAX, mstSet[i] = 0,parent[i]=-1;
 
        key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
        parent[0] = -1; // First node is always root of MST 
 
         for (int count = 0; count < V-1; count++){
            // Pick thd minimum key vertex from the set of vertices
            // not yet included in MST
            int u = minKey(key, mstSet);
 
            // Add the picked vertex to the MST Set
            mstSet[u] = 1;
            for (int v = 0; v < V; v++)
                if (g[u][v] && mstSet[v] == 0 && g[u][v] <  key[v])
                    parent[v]  = u, key[v] = g[u][v];
           }
        
        int mstPossible = 1; // 0 means not possible
        //if parent of any node is still -1 that means MST not possible without this edge, disconnected componenet.
        for(int v=1;v<V;v++){
            if(parent[v]==-1){
                mstPossible = 0;
                break;
            }
        }
        
        if(mstPossible==0) continue;
        
        long sumEdge = 0 ;
        for (int i = 1; i < V; i++)
            sumEdge = sumEdge + (long)g[i][parent[i]]; 
            
        if(sumEdge < secondCost)
            secondCost = sumEdge;
            
        
      
   }  

    if(secondCost == LONG_MAX) //no 2nd mst possible at all.
        printf("-1");
    else
        printf("%ld\n",secondCost);
        
        
}
void primMST(int **graph)
{
     int parent[V]; // Array to store constructed MST
     int key[V];   // Key values used to pick minimum weight edge in cut
     int mstSet[V]; 
     long Cost = LONG_MAX; 
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
        long sumEdge = 0 ;
        for (int i = 1; i < V; i++)
            sumEdge = sumEdge + (long)graph[i][parent[i]]; 
            
        if(sumEdge < Cost)
            Cost = sumEdge;
     }
    if(Cost == LONG_MAX) //no 2nd mst possible at all.
        printf("-1");
    else
        printf("%ld\n",Cost);
     printSecondMSTWeight(parent, graph);
}
 
int main()
{   
    int countVertices,countEdges;
    
    
    scanf("%d",&countVertices);
    V= countVertices;
    if (V<=2){
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        printf("%d\n",c);
        printf("-1");
    }else{
        countEdges = (countVertices*(countVertices-1))/2;
        int *arr[countEdges];
        for (int i=0; i<countEdges; i++)
            arr[i] = (int *)malloc(countEdges * sizeof(int));

        for (int i = 0; i <  countEdges; i++)
         for (int j = 0; j < countEdges; j++)
            arr[i][j] = 0;

        for(int i=0;i<countEdges;i++){
            int a,b,c;
            scanf("%d %d %d",&a,&b,&c);
            
            arr[a][b] = c;
            arr[b][a] = c;
        }

        // Print the solution
        primMST(arr);
    }
    
  
    return 0;
}