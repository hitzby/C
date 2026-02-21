#include <stdio.h>
#include <stdlib.h>

#define MAX_V 100

typedef struct Node
{
    int dest;
    struct Node *next;
} Node;

typedef struct Graph
{
    int numV;
    Node *adjLists[MAX_V];
    int inDegree[MAX_V];
} Graph;

Node *createNode(int dest)
{
    Node *newnode = (Node *)malloc(sizeof(Node));
    newnode->dest = dest;
    newnode->next = NULL;
    return newnode;
}

Graph *createGraph(int vertices)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numV = vertices;
    for (int i = 0; i < vertices; i++)
    {
        graph->adjLists[i] = NULL;
        graph->inDegree[i] = 0;
    }
    return graph;
}

void addEdge(Graph *graph, int src, int dest)
{
    Node *newnode = createNode(dest);
    newnode->next = graph->adjLists[src];
    graph->adjLists[src] = newnode;
    graph->inDegree[dest]++;
}
// 拓扑排序
void topologicalSort(Graph *graph)
{
    int queue[MAX_V];
    int head = 0, tail = 0;
    int count = 0;
    int result[MAX_V];
    // 将入度为零的顶点入队
    for (int i = 0; i < graph->numV; i++)
    {
        if (graph->inDegree[i] == 0)
        {
            queue[tail++] = i;
        }
    }
    // 循环处理队列
    while (head < tail)
    {
        int u = queue[head++];
        result[count++] = u;
        // 遍历u的所有邻接点
        Node *temp = graph->adjLists[u];
        while (temp)
        {
            int v = temp->dest;
            graph->inDegree[v]--;
            if (graph->inDegree[v] == 0)
            {
                queue[tail++] = v;
            }
            temp = temp->next;
        }
    }
    if (count != graph->numV)
    {
        printf("Graph has a cycle, topological sort not possible.\n");
    }
    else
    {
        printf("Topological Sort: ");
        for (int i = 0; i < count; i++)
        {
            printf("%d ", result[i]);
        }
        printf("\n");
    }
}
int main(void)
{
    int V = 6;
    Graph *graph = createGraph(V);
    addEdge(graph, 5, 2);
    addEdge(graph, 5, 0);
    addEdge(graph, 4, 0);
    addEdge(graph, 4, 1);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 1);
    topologicalSort(graph);
    return 0;
}