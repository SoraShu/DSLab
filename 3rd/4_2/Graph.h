#include <stdio.h>
#include <stdlib.h>
#define max_dis 100000

typedef char vextype[20];
typedef struct
{
    int N,E,L;//顶点数，边数
    int **matrix;//邻接矩阵
    vextype *vertex;//节点名字
    int *ID;
    int *num;
}Graph;

Graph createGraph(int n);
void DestoryGraph(Graph g);
int isConnected(Graph g);
void DFS(Graph g,int v,int visited[]);
void computeEcc(Graph g, int *diameter, int *radius);
int dijkstra(Graph g, int start, int end, int *path);
void printPath(int d, int *diameter_path, Graph g);
