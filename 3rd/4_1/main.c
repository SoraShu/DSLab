#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define max_dis 100000

typedef char vextype[20];
typedef struct
{
    int N, E;//N是顶点数，E是边数
    int **matrix;//储存邻接矩阵
    vextype *vertex;//存储节点的名字
} Graph;


Graph createGraph(int n);
int isConnected(Graph g);
void nodeDegree(Graph g, int *node_degree);
double clusteringCoefficient(Graph g);
void computeEcc(Graph g, int *diameter, int *radius);
int dijkstra(Graph g, int start, int end, int *path);
void printPath(int d, int *diameter_path, Graph g);
void DFS(Graph g,int v,int visited[]);//新增
double CSofOneNode(Graph g,int v);//新增
int FindMax(int arr[],int n);//新增
int FindMin(int arr[],int n);//新增
/**
 * 创建一个节点数为n的图
 * @param n 节点个数
 * @return 返回这个图
 */
Graph createGraph(int n)
{
    int i, j;
    Graph g;
    g.N = n;
    g.matrix = (int **) malloc(sizeof(int *) * g.N);
    for (i = 0; i < n; i++)
    {
        g.matrix[i] = (int *) malloc(sizeof(int) * g.N);
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
    g.vertex = (vextype *) malloc(sizeof(vextype) * g.N);
    return g;
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
    printf("Path: ");
    do
    {
        printf("%s ", g.vertex[path[k]]);
        path_length += g.matrix[path[k]][path[k + 1]];
        k++;
    }
    while (path_length < d);
    printf("%s\n", g.vertex[path[k]]);
}

/**
 * 判断图是否连通
 * @param g 图
 * @return 连通返回1，否则返回0
 */
int isConnected(Graph g)
{
    //TODO
    int *visited=(int *)calloc(g.N,sizeof(int));//初始化
    /*for(int i=0;i<g.N;i++)
    {
        visited[i]=0;
    }*/
    int flag=1;
    DFS(g,0,visited);
    for(int i=0; i<g.N; i++)
    {
        if(!visited[i])
        {
            flag=0;
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
void DFS(Graph g,int v,int visited[])
{
    visited[v]=1;
    for(int w=0; w<g.N; w++)
    {
        if(!visited[w]&&w!=v&&g.matrix[v][w]!=max_dis)
            DFS(g,w,visited);
    }
}


/**
 * 计算每个点的度
 * @param g 图
 * @param node_degree 将每个点的度写到这个数组中
 */
void nodeDegree(Graph g, int *node_degree)
{
    //TODO
    for(int i=0; i<g.N; i++)
    {
        node_degree[i]=0;
        for(int j=0; j<g.N; j++)
        {
            if(j!=i&&g.matrix[i][j]!=max_dis)
                node_degree[i]++;
        }
    }
}

/**
 * 计算图的聚类系数
 * @param g 图
 * @return 返回聚类系数
 */
double clusteringCoefficient(Graph g)
{
    //TODO
    double sum=0;
    for(int v=0; v<g.N; v++)
        sum+=CSofOneNode(g,v);
    return sum/g.N;
}

/**
 * 计算单个节点的聚类系数
 * @param g 图
 * @param v 节点
 * @return 返回聚类系数
 */

double CSofOneNode(Graph g,int v)
{
    int *Friend=(int *)malloc(sizeof(int)*(g.N));
    int top=0;
    int nFriends=0;
    for(int w=0; w<g.N; w++)
    {
        if(w!=v&&g.matrix[v][w]!=max_dis)
            Friend[top++]=w;
    }
    for(int i=0; i<top; i++)
    {
        for(int j=i+1; j<top; j++)
        {
            if(g.matrix[Friend[i]][Friend[j]]!=max_dis)
                nFriends++;
        }
    }
    if(nFriends==0)
        return 0;
    else
        return 2.0*nFriends/(top*(top-1));
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
    //TODO
    //为了输出方便，可从end出发寻找start，用pre记录前驱元，逆序输出即为从start到end的正序路径
    int *pre=(int *)malloc(sizeof(int)*g.N);//用pre数组记录前驱元
    int *length=(int *)malloc(sizeof(int)*g.N);//用length数组记录路径长度
    int *flag=(int *)malloc(sizeof(int)*g.N);//用flag数组记录是否在U集合中
    for(int i=0; i<g.N; i++)
    {
        pre[i]=end;//从end出发
        length[i]=g.matrix[end][i];//初值为从i直接到达
        flag[i]=0;//先将U集合置为空
    }
    flag[end]=1;//将end包含进U集
    while(1)//找到start前一直循环
    {
        int min=max_dis;
        int v;
        //寻找E-U集里距离end最近的点v
        for(int w=0; w<g.N; w++)
        {
            if(!flag[w]&&length[w]<min)
            {
                v=w;
                min=length[v];
            }
        }
        flag[v]=1;//将v包含进U中
        if(v==start)//找到start结束循环
            break;
        for(int w=0; w<g.N; w++)//调整E-U中所有顶点到end的最短距离
        {
            if((!flag[w])&&(min+g.matrix[v][w]<length[w]))
            {
                length[w]=min+g.matrix[v][w];
                pre[w]=v;
            }
        }
    }
    int i=0;
    for(int v=start; v!=end; v=pre[v])
    {
        path[i++]=v;
    }
    path[i]=end;
    return length[start];
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
    //TODO
    int **M=(int **) malloc(sizeof(int *) * g.N);
    int *Eccentricity=(int *)malloc(sizeof(int)*g.N);
    for (int i = 0; i < g.N; i++)
    {
        M[i] = (int *) malloc(sizeof(int) * g.N);
        Eccentricity[i]=0;
    }
    for (int i = 0; i < g.N; i++)
    {
        for (int j = 0; j < g.N; j++)
        {
            M[i][j] = g.matrix[i][j];
        }
    }
    for(int k=0; k<g.N; k++)
    {
        for(int i=0; i<g.N; i++)
        {
            for(int j=0; j<g.N; j++)
            {
                if(M[i][j]>M[i][k]+M[k][j])
                    M[i][j]=M[i][k]+M[k][j];
            }
        }
    }
    for(int i=0; i<g.N; i++)
        Eccentricity[i]=FindMax(M[i],g.N);
    *diameter=FindMax(Eccentricity,g.N);
    *radius=FindMin(Eccentricity,g.N);
}

/**
 * 计算数组的最大值(辅助)
 * @param arr 整形数组
 * @param n 数组长度
 * @return 数组最大值
 */
int FindMax(int arr[],int n)
{
    int max=0;
    for(int i=0; i<n; i++)
        if(max<arr[i])
            max=arr[i];
    return max;
}

/**
 * 计算数组的最小值(辅助)
 * @param arr 整形数组
 * @param n 数组长度
 * @return 数组最小值
 */
int FindMin(int arr[],int n)
{
    int min=max_dis;
    for(int i=0; i<n; i++)
        if(min>arr[i])
            min=arr[i];
    return min;
}

int main()
{
    int node_num;
    int edge_num;
    int ca = 1;
    if (freopen("stu.in", "r", stdin) == NULL)
    {
        printf("There is an error in reading file stu.in");
    }
    while (scanf("%d %d\n", &node_num, &edge_num) != EOF)
    {
        printf("\ncase %d:\n", ca++);
        int start_idx, end_idx, weight;
        Graph g = createGraph(node_num);
        for(int i = 0; i < node_num; i++)
        {
            sprintf(g.vertex[i], "%d", i);
        }
        for (int i = 0; i < edge_num; i++)
        {
            scanf("%d %d %d\n", &start_idx, &end_idx, &weight);
            g.matrix[start_idx][end_idx] = weight;
            g.matrix[end_idx][start_idx] = weight;
        }

        printf("connected: %d\n", isConnected(g));

        int *degree = (int *)malloc(sizeof(int) * g.N);
        nodeDegree(g, degree);
        printf("degree distribution:\n");
        for(int i=0; i<g.N; i++)
        {
            printf("node%s:%d,", g.vertex[i], degree[i]);
        }
        printf("\n");
        free(degree);

        double c = clusteringCoefficient(g);
        printf("clustering coefficient:%f\n", c);

        if(isConnected(g))
        {
            int *short_path = (int *)malloc(sizeof(int) * g.N);
            int dis = dijkstra(g, 1, 3, short_path);
            printf("the shortest path between 1 and 3: %d\n", dis);
            printPath(dis, short_path, g);
            free(short_path);

            int diameter, radius;
            computeEcc(g, &diameter, &radius);
            printf("diameter:%d\n", diameter);
            printf("radius:%d\n", radius);
        }
    }

    return 0;
}
