#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

int FindMax(int arr[],int n);
int FindMin(int arr[],int n);

int main()
{
    //�ļ���ȡ-----------------------------------------------------
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
    //�ļ���ȡ����



    //����1
    printf("����1��\n");
    if(isConnected(g))
    {
        printf("����·ͼ����ͨ�ġ�\n\n");
    }
    else
    {
        printf("��·��ͼ������ͨ�ġ�\n\n");
    }


    //����2
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
    printf("����2��\n");
    printf("������·����վ����Ϊ%d��վ��Ϊ%s��\n",g.ID[v],g.vertex[v]);
    printf("����%d����·ͨ����\n\n",g.num[v]);

    //����ͼ��ͨ�������������3������4
    if(isConnected(g))
    {
        //����3
        printf("����3��\n");
        int *short_path = (int *)malloc(sizeof(int) * g.N);
        int dis = dijkstra(g, 82, 1, short_path);
        printf("�Ӵ�ѧ��վ������վ������Ҫ%d���ӡ�\n", dis);
        printPath(dis, short_path, g);
        free(short_path);

        //����4
        printf("����4��\n");
        int diameter, radius;
        computeEcc(g, &diameter, &radius);
        printf("��ͼ��ֱ���Ͱ뾶�ֱ�Ϊ��\n");
        printf("ֱ��:%d\n", diameter);
        printf("�뾶:%d\n", radius);
    }

    return 0;
}

//������������ֵ
int FindMax(int arr[],int n)
{
    int max=0;
    for(int i=0; i<n; i++)
        if(max<arr[i])
            max=arr[i];
    return max;
}

//�����������Сֵ
int FindMin(int arr[],int n)
{
    int min=max_dis;
    for(int i=0; i<n; i++)
        if(min>arr[i])
            min=arr[i];
    return min;
}
