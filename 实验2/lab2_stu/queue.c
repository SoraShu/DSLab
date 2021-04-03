#include "queue.h"

/** ！！要求使用栈实现队列，因此只能使用stack.h中的函数。不允许直接访问stack的底层实现！！*/

/**
 * 初始化队列
 * @param Q 操作队列
 */
void InitQueue(Queue *Q)
{
    InitStack(&Q->stack1);
    InitStack(&Q->stack2);
}

/**
 * 清空队列 操作队列
 * @param Q
 */
void ClearQueue(Queue *Q)
{
    InitStack(&Q->stack1);
    InitStack(&Q->stack2);
}

/**
 *
 * @param Q 操作队列
 * @return 返回队列已使用长度
 */
int QueueLength(Queue Q)
{
    return StackLength(Q.stack1) + StackLength(Q.stack2);
}

/**
 * 判断队列是否为空
 * @param Q 操作队列
 * @return 如果为空返回1，否则返回0
 */
int QueueEmpty(Queue Q)
{
    //TODO
    if(StackLength(Q.stack1)+StackLength(Q.stack2))
        return 0;
    else
        return 1;
}

/**
 * 入队操作，将元素插入队列，需要处理队列满的情况（队列元素数目最多为 MaxSize）
 * @param Q 操作队列
 * @param e 插入的元素
 * @return 如果插入成功返回1，否则返回0
 */
int EnQueue(Queue *Q, DataType e)//设计向stack1压入元素，从stack2弹出元素
{
    /*
        认真思考，从哪个栈Push元素，时间复杂度如何？能否降低
    */
    //TODO
    //设计向stack1压入元素，从stack2弹出元素
    //时间复杂度为O(1)
    int L=QueueLength(*Q);
    if(L==MaxSize)
        return 0;
    else//不会出现stack1满的情况，stack1满时queue也满
    {
        Push(&(Q->stack1),e);
        return 1;
    }
}

/**
 * 出队操作，从队列中取出一个元素
 * @param Q 操作队列
 * @param e 接受出队元素
 * @return 如果成功取出返回1，否则返回0
 */
int DeQueue(Queue *Q, DataType *e)
{
    /*
        认真思考，从哪个栈Pop元素，时间复杂度如何？能否降低
    */
    //TODO
    //设计向stack1压入元素，从stack2弹出元素
    //时间复杂度为O(n)
    if(QueueLength(*Q)==0)
        return 0;
    else//可能出现stack2为空的情况
    {
        if(StackLength(Q->stack2))
        {
            Pop(&(Q->stack2),e);
            return 1;
        }
        else//stack2为空
        {
            DataType temp[MaxSize];
            StackToArray(Q->stack1,temp);
            int i=StackLength(Q->stack1);
            InitStack(&(Q->stack1));//获取stack1的数组拷贝并清空stack1
            for(i=i-1; i>=0; i--)
                Push(&(Q->stack2),temp[i]);//将数组拷贝逐项压入stack2
            Pop(&(Q->stack2),e);
            return 1;
        }
    }
}

/**
 * 获取队列头（不删除元素）
 * @param Q 操作队列
 * @param e 接受队列头元素
 * @return 如果成功获取返回1，否则返回0
 */
int GetHead(Queue Q, DataType *e)
{
    //TODO
    if(QueueLength(Q)==0)
        return 0;
    else
    {
        if(StackLength(Q.stack2))
        {
            GetTop(Q.stack2,e);
            return 1;
        }
        else
        {
            DataType temp[MaxSize];
            StackToArray(Q.stack1,temp);//获取stack1的数组拷贝
            *e=temp[0];//e接受队列头元素
            return 1;
        }
    }
}

/**
 * 获取队列的一个数组拷贝，顺序为从队列头到队列尾
 * @param Q 操作队列
 * @param seq 栈中元素的一个拷贝
 */
void QueueToArray(Queue Q, DataType *seq)
{
    /*
        取决于你的栈如何设计，元素存在哪个队列里。
    */
    //TODO
    DataType temp[MaxSize];
    StackToArray(Q.stack2,temp);
    for(int i=StackLength(Q.stack2)-1;i>=0;i--)//倒序将数组拷贝赋值给seq各元素
    {
        *seq=temp[i];
        seq++;
    }//指针已前移
    StackToArray(Q.stack1,seq);
}
