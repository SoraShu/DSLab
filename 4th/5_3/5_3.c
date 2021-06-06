#include <stdio.h>
#include <stdlib.h>

//结构体，记录事件
typedef struct PERIOD
{
    int time; //开始时间，结束时间用后继time-1表示
    int nstu;
} PERIOD;

void sort(int *start, int *end, int M);
void QSort(int *a, int low, int high);
void QuckSort(int *a, int n);
int Partion(int *a, int low, int high);
void findPeriod(int *start, int *end, int M, int N);

//对起始时间与终止时间进行排序，参数可自行填写

//排序&&调整end数组
void sort(int *start, int *end, int M)
{
    QuckSort(start, M);
    QuckSort(end, M);
    //调整end数组以满足退出时间与元素值相等
    for (int i = 0; i < M; i++)
    {
        end[i]++;
    }
}

void QSort(int *a, int low, int high)
{
    if (low >= high)
        return;
    int pivotval = Partion(a, low, high);
    QSort(a, low, pivotval - 1);
    QSort(a, pivotval + 1, high);
}

//封装的快排
void QuckSort(int *a, int n)
{
    QSort(a, 0, n - 1);
}

int Partion(int *a, int low, int high)
{
    int pivotval = a[low];
    while (low < high)
    {
        while (low < high && a[high] >= pivotval)
            high--;
        a[low] = a[high];
        while (low < high && a[low] <= pivotval)
            low++;
        a[high] = a[low];
    }
    a[low] = pivotval;
    return low;
}

//计算空闲人数最多的起始时间和终止时间，参数可自行填写
void findPeriod(int *start, int *end, int M, int N)
{
    PERIOD *period = (PERIOD *)malloc(sizeof(PERIOD) * M * 2);
    int time, delta;
    int max = 0;
    int flag = 0;
    int i = 0, j = 0, k = 0; //指针

    //处理数据并记录在period数组中
    while (i < M || j < M)
    {
        delta = 0;
        if (i < M && start[i] <= end[j]) //优先读取start数组
            time = start[i];
        else
            time = end[j];
        //分别循环读取start与end数组求取delta值
        while (start[i] == time)
        {
            i++;
            delta++;
        }
        while (end[j] == time)
        {
            j++;
            delta--;
        }

        period[k].time = time;
        if (k == 0)
            period[k].nstu = delta;
        else
            period[k].nstu = period[k - 1].nstu + delta;
        k++;
    }

    //遍历求取最大值
    for (int i = 0; i < k; i++)
    {
        if (period[i].nstu > max)
        {
            max = period[i].nstu;
        }
    }
    //输出所有最大值所在时间段
    for (int i = 0; i < k; i++)
    {

        if (period[i].nstu == max)
        {
            if (flag)
                printf(",");
            printf("%d %d", period[i].time, period[i + 1].time - 1);
            flag = 1;
        }
    }
}

int main()
{
    int N, M; //分别存储时间的段数和学生的个数
    int caseNum = 0;
    int start[1002];
    int end[1002];

    if (freopen("5_3_input.in", "r", stdin) == NULL)
    {
        printf("There is an error in reading file 5_3_input.in");
    }

    while (scanf("%d %d", &N, &M) != EOF)
    {
        caseNum++;
        printf("==== Case %d ====\n", caseNum);
        for (int i = 0; i < M; i++)
        {
            scanf("%d %d", &start[i], &end[i]);
        }
        sort(start, end, M);
        findPeriod(start, end, M, N);
        printf("\n");
    }
    fclose(stdin);

    /* 终端输入
   while(scanf("%d %d",&N,&M)!=EOF){
       caseNum++;
       printf("==== Case %d ====\n",caseNum);
       for(int i = 0; i < M;i++){
           scanf("%d %d",&start[i],&end[i]);
       }
       sort(start, end, M);
       findPeriod(start, end, M, N);
   }
   */
}
