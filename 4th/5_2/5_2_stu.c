#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

int *solve2(int *arr, int N, int k);
void HeapAdjust(int *H, int s, int m);
void ArrtoHeap(int *arr, int N);
void test2();

//Todo
//需要返回一个数组，数组元素是原始数组里最大的k个数
//注意按照从小到大的顺序排序
//可以自行添加其他辅助函数,可以根据实际需要修改函数参数

int *solve2(int *arr, int N, int k)
{
    int *a = (int *)malloc(sizeof(int) * k);
    ArrtoHeap(arr, N);
    for (int i = k - 1; i >= 0; i--)
    {
        a[i] = arr[0];
        arr[0] = arr[N - 1];
        N--;
        HeapAdjust(arr, 0, N);
    }
    return a;
}

//堆的调整
void HeapAdjust(int *H, int s, int m)
{
    int temp = H[s];
    for (int j = 2 * s + 1; j < m; s = j, j = 2 * s + 1)
    {
        if (j + 1 < m && H[j] < H[j + 1])
            j++;
        if (temp > H[j])
            break;
        else
            H[s] = H[j];
    }
    H[s] = temp;
}

//将数组转换为堆
void ArrtoHeap(int *arr, int N)
{
    for (int i = N / 2 - 1; i >= 0; i--) //从标号大的开始调整每个非叶子节点
    {
        HeapAdjust(arr, i, N);
    }
}

void test2()
{
    int caseNum; //表示测试轮数
    if (freopen("5_2_input_5.in", "r", stdin) == NULL)
    {
        printf("There is an error in reading file 5_2_input_5.in");
    }
    scanf("%d", &caseNum);
    int case1 = 0;
    for (; case1 < caseNum; case1++)
    {
        int k, N;
        scanf("%d%d", &k, &N);
        int arr[MAX];
        int i = 0;
        for (; i < N; i++)
        {
            scanf("%d", &arr[i]);
        }
        int *res;
        res = solve2(arr, N, k);
        printf("==== Case %d ====\nres : ", case1 + 1);
        for (i = 0; i < k; i++)
        {
            printf("%d ", res[i]);
        }
        printf("\n");
    }
    fclose(stdin);
}

int main(void)
{
    test2();
    return 0;
}