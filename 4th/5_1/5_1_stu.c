#include <stdio.h>
#include <stdlib.h>
#define N 10000

int a[N]; // 用于存储奶牛产奶量
int solve1(int *a, int n);
void QSort(int *a, int low, int high);
void QuckSort(int *a, int n);
int Partion(int *a, int low, int high);

//Todo
//需要返回中位数奶牛产奶量。
//可以自行添加其他辅助函数,可以修改传参的数量

/**
 * @brief 求中位数
 * 
 * @param a 数组
 * @param n 数组长度
 * @return int 中位数
 */
int solve1(int *a, int n)
{
    QuckSort(a, n); //排序
    return a[(n - 1) / 2];
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

//划分，快排子过程
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

void test1()
{
    int caseNum; //表示测试轮数
    int n;
    int ans[N];
    if (freopen("5_1_input_5.in", "r", stdin) == NULL)
    {
        printf("There is an error in reading file 5_1_input_5.in");
    }
    scanf("%d", &caseNum);
    for (int case1 = 0; case1 < caseNum; case1++)
    {
        printf("==== Case %d ====\n", case1 + 1);
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &a[i]);
        }
        ans[case1] = solve1(a, n);
        printf("ans is:%d\n", ans[case1]);
        printf("\n");
    }
    fclose(stdin);
}

int main()
{
    test1();
    return 0;
}
