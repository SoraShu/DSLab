#include "Graph.h"

//��ʼ��ͼ
Graph createGraph(int n)
{
    int i, j;
    Graph g;
    g.N = n;
    g.matrix = (int **) malloc(sizeof(int *) * g.N);
    g.num=(int *)malloc(sizeof(int)*g.N);
    for (i = 0; i < n; i++)
    {
        g.matrix[i] = (int *) malloc(sizeof(int) * g.N);
        g.num[i]=0;
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
    g.ID=(int *)malloc(sizeof(int)*g.N);
    return g;
}

//ɾ��ͼ
void DestoryGraph(Graph g)
{

}

/**
 * �ж�ͼ�Ƿ���ͨ
 * @param g ͼ
 * @return ��ͨ����1�����򷵻�0
 */
int isConnected(Graph g)
{
    //TODO
    int *visited=(int *)calloc(g.N,sizeof(int));//��ʼ��
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
 * �����������(����)
 * @param g ͼ
 * @param v �ڵ���±�
 * @param visited ��־����
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
 * ����ͼ��ֱ���Ͱ뾶����ʾ: Floyd�㷨
 * @param g ͼ
 * @param diameter ָ��ֱ��������ָ��
 * @param radius ָ��뾶������ָ��
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
 * ʹ��dijkstra�㷨���㵥Դ���·��
 * @param g ͼ
 * @param start ���
 * @param end �յ�
 * @param path ��start��end��·��, [start,...,end]
 * @return ·������
 */
int dijkstra(Graph g, int start, int end, int *path)
{
    //TODO
    //Ϊ��������㣬�ɴ�end����Ѱ��start����pre��¼ǰ��Ԫ�����������Ϊ��start��end������·��
    int *pre=(int *)malloc(sizeof(int)*g.N);//��pre�����¼ǰ��Ԫ
    int *length=(int *)malloc(sizeof(int)*g.N);//��length�����¼·������
    int *flag=(int *)malloc(sizeof(int)*g.N);//��flag�����¼�Ƿ���U������
    for(int i=0; i<g.N; i++)
    {
        pre[i]=end;//��end����
        length[i]=g.matrix[end][i];//��ֵΪ��iֱ�ӵ���
        flag[i]=0;//�Ƚ�U������Ϊ��
    }
    flag[end]=1;//��end������U��
    while(1)//�ҵ�startǰһֱѭ��
    {
        int min=max_dis;
        int v;
        //Ѱ��E-U�������end����ĵ�v
        for(int w=0; w<g.N; w++)
        {
            if(!flag[w]&&length[w]<min)
            {
                v=w;
                min=length[v];
            }
        }
        flag[v]=1;//��v������U��
        if(v==start)//�ҵ�start����ѭ��
            break;
        for(int w=0; w<g.N; w++)//����E-U�����ж��㵽end����̾���
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
 * ���ݾ���d��·������path���·���������Ͳ���Ҫ·���Ľڵ���Ҳ����ȷ���·��
 * @param d ·������
 * @param path ����·��������
 * @param g ͼ
 */
void printPath(int d, int *path, Graph g)
{
    int k = 0;
    int path_length = 0;
    printf("·��(��ʽΪվ��_վ��): \n");
    do
    {
        printf("%d_%s -> ",g.ID[path[k]] ,g.vertex[path[k]]);
        path_length += g.matrix[path[k]][path[k + 1]];
        k++;
    }
    while (path_length < d);
    printf("%d_%s\n\n",g.ID[path[k]] , g.vertex[path[k]]);
}
