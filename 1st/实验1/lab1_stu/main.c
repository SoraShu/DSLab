#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node
{
    char StuID[11];
    int Grade;
    struct node *next;
} StudentLinkedListNode;


/* �����ཻ���� */
void createCrossLink(StudentLinkedListNode* a, StudentLinkedListNode* b, int beforeCross1, int beforeCross2)
{
    // a��b�������ɽ��ֵ��ͬ
    // beforeCross1Ϊ������a�еĸ������ӵ�beforeCross1 + 1����㿪ʼ�ཻ
    // beforeCross2Ϊ������b�еĸ������ӵ�beforeCross2 + 1����㿪ʼ�ཻ
    // �ཻ�����ǽ�b�е�ǰһ���ָ��a�е��׸��ཻ���
    StudentLinkedListNode *p, *q;
    while(beforeCross1--)a=a->next;
    while(--beforeCross2)b=b->next;
    p = b->next;
    b->next = a;
    //����Ұָ����
    while(p)
    {
        q = p->next;
        free(p);
        p = q;
    }
}

void destroyCrossLink(StudentLinkedListNode* a, StudentLinkedListNode* b, StudentLinkedListNode* crossNode)
{
    StudentLinkedListNode* p = crossNode->next, *q;
    while(p)
    {
        q = p->next;
        free(p);
        p = q;
    }
    while(a != crossNode)
    {
        q = a->next;
        free(a);
        a = q;
    }
    while(b != crossNode)
    {
        q = b->next;
        free(b);
        b = q;
    }
    free(crossNode);
}

/* ��ӡ�����ڵ� */
void printLinkedListNode(StudentLinkedListNode * node)
{
    printf("{ID:%s, Grade:%d}", node->StuID, node->Grade);
    if(node->next!=NULL)
    {
        printf("->");
    }
    else
    {
        printf("\n");
    }

}

/** ����ñ�ĳɼ���� */
void outputStudentLinkedList(StudentLinkedListNode* head)
{
    // ���ڵ����ڵ�����ĺ���printLinkedListNode���ṩ
    //����ʵ�ֱ���������߼�
    //TODO
    StudentLinkedListNode* p=head;
    while(p)//ͨ��ѭ������������pָ���ʱ����ѭ��
    {
        printLinkedListNode(p);
        p=p->next;
    }
}


/** �½�һ������node������ */
StudentLinkedListNode* studentLinkedListCreate(char student_id[], int grade)
{
    //tips:malloc��ʱ��ǵ�Ϊת��Ϊ�ṹ��ָ��
    //TODO
    StudentLinkedListNode* p=NULL;
    p=(StudentLinkedListNode*)malloc(sizeof(StudentLinkedListNode));
    strcpy(p->StuID,student_id);//�ַ����ĸ�ֵ�����strcpy
    p->Grade=grade;
    return p;
}


/** ���ս������ѧ���ĳɼ����,����������ͷָ�� */
StudentLinkedListNode* studentLinkedListAdd(StudentLinkedListNode* head, StudentLinkedListNode* node)
{
    //TODO
    node->next=head;//���½ڵ��nextָ��ָ��ͷ�ڵ�
    return node;

}


/** ��ת���� */
StudentLinkedListNode* reverseLinkedList(StudentLinkedListNode*head)
{
    //TODO
    StudentLinkedListNode *p=NULL,*q=NULL;
    p=head;
    while(p->next)//ÿ��ѭ����δ��ת�ĵ�һ���ڵ�ժ�²���ͷ�巨��������
    {
        q=p->next;
        p->next=q->next;
        q->next=head;
        head=q;
    }
    return head;
}

/** �ҵ��ཻ�ĵ�һ����� */
StudentLinkedListNode* findCrossBeginNode(StudentLinkedListNode* class1, StudentLinkedListNode* class2)
{
    //class1��class2�ں�һ������ȫ�غϣ������ڴ��ַ��ͬ�������ҳ������ؿ�ʼ�ཻ�ĵ�һ����㡣
    //�벻Ҫ�򵥵�ͨ�����ṹ��ĳ�Ա���жϡ�
    //TODO
    int Length_1=0,Length_2=0;
    StudentLinkedListNode *p1=class1,*p2=class2;
    while(p1)//ѭ����class1��������
    {
        Length_1++;
        p1=p1->next;
    }
    while(p2)//ѭ����class2��������
    {
        Length_2++;
        p2=p2->next;
    }
    if(Length_1>Length_2)//���ָ��ǰ��
    {
        for(int i=1; i<=Length_1-Length_2; i++)
        {
            class1=class1->next;
        }
    }
    else
    {
        for(int i=1; i<=Length_2-Length_1; i++)
        {
            class2=class2->next;
        }
    }
    while(class1&&class2&&class1!=class2)//��ָ��ǰ������ͬ��ַʱ�ҵ�����
    {
        class1=class1->next;
        class2=class2->next;
    }
    return class1;
}

int main()
{
    freopen("./gradeImport.in","r",stdin);

    StudentLinkedListNode *class1=NULL, *class2=NULL;
    int num1, num2, i;
    char student_id[11];
    int grade;
    int beforeCross1, beforeCross2;
    StudentLinkedListNode *node;

    while(~scanf("%d%d", &num1, &num2))
    {
        class1 = class2 = NULL;
        // �洢���ݵ�����
        for(i = 0; i < num1; i++)
        {
            scanf("%s%d", student_id, &grade);
            node = studentLinkedListCreate(student_id, grade);
            class1 = studentLinkedListAdd(class1, node);
        }
        for(i = 0; i < num2; i++)
        {
            scanf("%s%d", student_id, &grade);
            node = studentLinkedListCreate(student_id, grade);
            class2 = studentLinkedListAdd(class2, node);
        }
        printf("* part1:\nclass1:\n");
        outputStudentLinkedList(class1);
        printf("class2:\n");
        outputStudentLinkedList(class2);

        // ��ת����
        class1 = reverseLinkedList(class1);
        class2 = reverseLinkedList(class2);
        printf("* part2:\nclass1:\n");
        outputStudentLinkedList(class1);
        printf("class2:\n");
        outputStudentLinkedList(class2);

        // �����ཻ����
        scanf("%d%d",&beforeCross1,&beforeCross2);
        createCrossLink(class1, class2, beforeCross1, beforeCross2);

        // ��ӡ�ཻ���
        node = findCrossBeginNode(class1, class2);
        printf("* part3:\n");
        printf("{ID:%s, Grade:%d}\n", node->StuID, node->Grade);

        //�����ཻ����
        destroyCrossLink(class1, class2, node);

        printf("\n");
    }
    return 0;
}
