#include "Graph.h"

/**
 * @brief 初始化图
 *
 * @param n 顶点数
 * @return Graph 图
 */
Graph createGraph(int n)
{
    int i, j;
    Graph g;
    g.N = n;
    g.matrix = (int **)malloc(sizeof(int *) * g.N);
    g.num = (int *)malloc(sizeof(int) * g.N);
    for (i = 0; i < n; i++)
    {
        g.matrix[i] = (int *)malloc(sizeof(int) * g.N);
        g.num[i] = 0;
    }
    for (i = 0; i < g.N; i++)
    {
        for (j = 0; j < g.N; j++)
        {
            g.matrix[i][j] = max_dis;
        }
    }
    for (i = 0; i < g.N; i++)
    {
        g.matrix[i][i] = 0;
    }
    g.vertex = (vextype *)malloc(sizeof(vextype) * g.N);
    g.ID = (int *)malloc(sizeof(int) * g.N);
    return g;
}

/**
 * @brief 删除图
 *
 * @param g 图
 */
void DestoryGraph(Graph g)
{
    for (int i = 0; i < g.N; i++)
    {
        free(g.matrix[i]);
    }
    free(g.matrix);
    free(g.vertex);
    free(g.ID);
    free(g.num);
}

/**
 * 判断图是否连通
 * @param g 图
 * @return 连通返回1，否则返回0
 */
int isConnected(Graph g)
{
    int *visited = (int *)calloc(g.N, sizeof(int)); //初始化
    int flag = 1;
    DFS(g, 0, visited);
    for (int i = 0; i < g.N; i++)
    {
        if (!visited[i])
        {
            flag = 0;
            break;
        }
    }
    return flag;
}

/**
 * 深度优先搜索(辅助)
 * @param g 图
 * @param v 节点的下标
 * @param visited 标志数组
 */
void DFS(Graph g, int v, int visited[])
{
    visited[v] = 1;
    for (int w = 0; w < g.N; w++)
    {
        if (!visited[w] && w != v && g.matrix[v][w] != max_dis)
            DFS(g, w, visited);
    }
}

/**
 * 计算图的直径和半径，提示: Floyd算法
 * @param g 图
 * @param diameter 指向直径变量的指针
 * @param radius 指向半径变量的指针
 * @return void
 */
void computeEcc(Graph g, int *diameter, int *radius)
{
    int **M = (int **)malloc(sizeof(int *) * g.N);
    int *Eccentricity = (int *)malloc(sizeof(int) * g.N);
    for (int i = 0; i < g.N; i++)
    {
        M[i] = (int *)malloc(sizeof(int) * g.N);
        Eccentricity[i] = 0;
    }
    for (int i = 0; i < g.N; i++)
    {
        for (int j = 0; j < g.N; j++)
        {
            M[i][j] = g.matrix[i][j];
        }
    }
    for (int k = 0; k < g.N; k++)
    {
        for (int i = 0; i < g.N; i++)
        {
            for (int j = 0; j < g.N; j++)
            {
                if (M[i][j] > M[i][k] + M[k][j])
                    M[i][j] = M[i][k] + M[k][j];
            }
        }
    }
    for (int i = 0; i < g.N; i++)
        Eccentricity[i] = FindMax(M[i], g.N);
    *diameter = FindMax(Eccentricity, g.N);
    *radius = FindMin(Eccentricity, g.N);
}

/**
 * 使用dijkstra算法计算单源最短路径
 * @param g 图
 * @param start 起点
 * @param end 终点
 * @param path 从start到end的路径, [start,...,end]
 * @return 路径长度
 */
int dijkstra(Graph g, int start, int end, int *path)
{
    //为了输出方便，可从end出发寻找start，用pre记录前驱元，逆序输出即为从start到end的正序路径
    int *pre = (int *)malloc(sizeof(int) * g.N);    //用pre数组记录前驱元
    int *length = (int *)malloc(sizeof(int) * g.N); //用length数组记录路径长度
    int *flag = (int *)malloc(sizeof(int) * g.N);   //用flag数组记录是否在U集合中
    for (int i = 0; i < g.N; i++)
    {
        pre[i] = end;                 //从end出发
        length[i] = g.matrix[end][i]; //初值为从i直接到达
        flag[i] = 0;                  //先将U集合置为空
    }
    flag[end] = 1; //将end包含进U集
    while (1)      //找到start前一直循环
    {
        int min = max_dis;
        int v;
        //寻找E-U集里距离end最近的点v
        for (int w = 0; w < g.N; w++)
        {
            if (!flag[w] && length[w] < min)
            {
                v = w;
                min = length[v];
            }
        }
        flag[v] = 1;    //将v包含进U中
        if (v == start) //找到start结束循环
            break;
        for (int w = 0; w < g.N; w++) //调整E-U中所有顶点到end的最短距离
        {
            if ((!flag[w]) && (min + g.matrix[v][w] < length[w]))
            {
                length[w] = min + g.matrix[v][w];
                pre[w] = v;
            }
        }
    }
    int i = 0;
    for (int v = start; v != end; v = pre[v])
    {
        path[i++] = v;
    }
    path[i] = end;
    return length[start];
}

/**
 * 根据距离d和路径数组path输出路径，这样就不需要路径的节点数也能正确输出路径
 * @param d 路径长度
 * @param path 储存路径的数组
 * @param g 图
 */
void printPath(int d, int *path, Graph g)
{
    int k = 0;
    int path_length = 0;
    printf("路径(格式为站号_站名): \n");
    do
    {
        printf("%d_%s -> ", g.ID[path[k]], g.vertex[path[k]]);
        path_length += g.matrix[path[k]][path[k + 1]];
        k++;
    } while (path_length < d);
    printf("%d_%s\n\n", g.ID[path[k]], g.vertex[path[k]]);
}

//计算数组的最大值
int FindMax(int arr[], int n)
{
    int max = 0;
    for (int i = 0; i < n; i++)
        if (max < arr[i])
            max = arr[i];
    return max;
}

//计算数组的最小值
int FindMin(int arr[], int n)
{
    int min = max_dis;
    for (int i = 0; i < n; i++)
        if (min > arr[i])
            min = arr[i];
    return min;
}
