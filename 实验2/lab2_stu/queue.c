#include "queue.h"

/** ����Ҫ��ʹ��ջʵ�ֶ��У����ֻ��ʹ��stack.h�еĺ�����������ֱ�ӷ���stack�ĵײ�ʵ�֣���*/

/**
 * ��ʼ������
 * @param Q ��������
 */
void InitQueue(Queue *Q)
{
    InitStack(&Q->stack1);
    InitStack(&Q->stack2);
}

/**
 * ��ն��� ��������
 * @param Q
 */
void ClearQueue(Queue *Q)
{
    InitStack(&Q->stack1);
    InitStack(&Q->stack2);
}

/**
 *
 * @param Q ��������
 * @return ���ض�����ʹ�ó���
 */
int QueueLength(Queue Q)
{
    return StackLength(Q.stack1) + StackLength(Q.stack2);
}

/**
 * �ж϶����Ƿ�Ϊ��
 * @param Q ��������
 * @return ���Ϊ�շ���1�����򷵻�0
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
 * ��Ӳ�������Ԫ�ز�����У���Ҫ��������������������Ԫ����Ŀ���Ϊ MaxSize��
 * @param Q ��������
 * @param e �����Ԫ��
 * @return �������ɹ�����1�����򷵻�0
 */
int EnQueue(Queue *Q, DataType e)
{
    /*
        ����˼�������ĸ�ջPushԪ�أ�ʱ�临�Ӷ���Σ��ܷ񽵵�
    */
    //TODO
    int L=QueueLength(*Q);
    if(L==MaxSize)
        return 0;
    else
    {
        Push(&(Q->stack1),e);
        return 1;
        /*
        if(StackLength(Q->stack1)==MaxSize)
            Push(Q->stack1,e);
        else
        {
            DataType temp[MaxSize];
            StackToArray(Q->stack2,temp);
            DataType *temp1=temp+StackLength(Q->stack2);
            StackToArray(Q->stack1,temp1);
            if(StackEmpty(Q->stack1)==0)    return 0;
            if(StackEmpty(Q->stack2)==0)    return 0;
            for(L=L-1; L>=0; L--)
            {
                (Push(Q->stack2,temp[L])==0);
            }
            Push(Q->stack1,e);
            return 1;
        }
        */
    }
}

/**
 * ���Ӳ������Ӷ�����ȡ��һ��Ԫ��
 * @param Q ��������
 * @param e ���ܳ���Ԫ��
 * @return ����ɹ�ȡ������1�����򷵻�0
 */
int DeQueue(Queue *Q, DataType *e)
{
    /*
        ����˼�������ĸ�ջPopԪ�أ�ʱ�临�Ӷ���Σ��ܷ񽵵�
    */
    //TODO
    if(QueueLength(*Q)==0)
        return 0;
    else
    {
        if(StackLength(Q->stack2))
        {
            Pop(&(Q->stack2),e);
            return 1;
        }
        else
        {
            DataType temp[MaxSize];
            StackToArray(Q->stack1,temp);
            int i=StackLength(Q->stack1);
            StackEmpty(Q->stack1);
            for(i=i-1; i>=0; i--)
                Push(&(Q->stack2),temp[i]);
            Pop(&(Q->stack2),e);
            return 1;
        }
    }
}

/**
 * ��ȡ����ͷ����ɾ��Ԫ�أ�
 * @param Q ��������
 * @param e ���ܶ���ͷԪ��
 * @return ����ɹ���ȡ����1�����򷵻�0
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
            StackToArray(Q.stack1,temp);
            *e=temp[0];
            return 1;
        }
    }
}

/**
 * ��ȡ���е�һ�����鿽����˳��Ϊ�Ӷ���ͷ������β
 * @param Q ��������
 * @param seq ջ��Ԫ�ص�һ������
 */
void QueueToArray(Queue Q, DataType *seq)
{
    /*
        ȡ�������ջ�����ƣ�Ԫ�ش����ĸ������
    */
    //TODO
    DataType temp[MaxSize];
    StackToArray(Q.stack2,temp);
    for(int i=StackLength(Q.stack2)-1;i>=0;i--)
    {
        *seq=temp[i];
        seq++;
    }
    StackToArray(Q.stack1,seq);
}
