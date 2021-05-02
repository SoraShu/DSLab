#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

int FindMax(int arr[],int n);
int FindMin(int arr[],int n);

int main()
{
    //文件读取-----------------------------------------------------
    int node_num,edge_num,line_num;
    edge_num=0;
    if (freopen("no2metro.txt", "r", stdin) == NULL)
    {
        printf("There is an error in reading file no2metro.txt");
        exit(0);
    }
    scanf("%d\n",&node_num);
    Graph g=createGraph(node_num);
    for(int i=0; i<node_num; i++)
    {
        scanf("%d\t%s\n",&(g.ID[i]),g.vertex[i]);//?
    }
    fclose(stdin);
    if (freopen("metro.txt", "r", stdin) == NULL)
    {
        printf("There is an error in reading file metro.txt");
        exit(0);
    }
    scanf("%d\n%d\n",&node_num,&line_num);
    for(int i=0; i<line_num; i++)
    {
        int station_num;
        int pre,now,dis;
        scanf("%d\n",&station_num);
        scanf("%d\t%d\n",&pre,&dis);
        g.num[pre]++;
        for(int j=1; j<station_num; j++)
        {
            scanf("%d\t%d\n",&now,&dis);
            g.matrix[now][pre]=g.matrix[pre][now]=dis;
            edge_num++;
            g.num[now]++;
            pre=now;
        }
    }
    g.E=edge_num;
    g.N=node_num;
    g.L=line_num;
    fclose(stdin);
    //-------------------------------------------------------------
    //文件读取结束



    //问题1
    printf("问题1：\n");
    if(isConnected(g))
    {
        printf("该线路图是连通的。\n\n");
    }
    else
    {
        printf("该路线图不是连通的。\n\n");
    }


    //问题2
    int max=0;
    int v;
    for(int i=0; i<g.N; i++)
    {
        if(max<g.num[i])
        {
            max=g.num[i];
            v=i;
        }
    }
    printf("问题2：\n");
    printf("换乘线路最多的站点编号为%d，站名为%s。\n",g.ID[v],g.vertex[v]);
    printf("共有%d条线路通过。\n\n",g.num[v]);

    //若该图连通，继续完成问题3和问题4
    if(isConnected(g))
    {
        //问题3
        printf("问题3：\n");
        int *short_path = (int *)malloc(sizeof(int) * g.N);
        int dis = dijkstra(g, 82, 1, short_path);
        printf("从大学城站到机场站最少需要%d分钟。\n", dis);
        printPath(dis, short_path, g);
        free(short_path);

        //问题4
        printf("问题4：\n");
        int diameter, radius;
        computeEcc(g, &diameter, &radius);
        printf("该图的直径和半径分别为：\n");
        printf("直径:%d\n", diameter);
        printf("半径:%d\n", radius);
    }

    return 0;
}

//计算数组的最大值
int FindMax(int arr[],int n)
{
    int max=0;
    for(int i=0; i<n; i++)
        if(max<arr[i])
            max=arr[i];
    return max;
}

//计算数组的最小值
int FindMin(int arr[],int n)
{
    int min=max_dis;
    for(int i=0; i<n; i++)
        if(min>arr[i])
            min=arr[i];
    return min;
}
