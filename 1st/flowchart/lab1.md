```flow
st=>start: outputStudentLinkedList
in=>inputoutput: 链表头指针head
op1=>operation: StudentLinkedListNode* p=head
cd=>condition: p不指向NULL
op2=>operation: printLinkedListNode(p)
op3=>operation: p=p->next
e=>end: end
st->in->op1->cd(yes,right)->op2(right)->op3(top)->cd
cd(no)->e
```

```flow
st=>start: studentLinkedListCreate
e=>end: end
in=>inputoutput: 字符串student_id, 整数grtade
out=>inputoutput: p
op1=>operation: StudentLinkedListNode* p=NULL
op2=>operation: p=(StudentLinkedListNode*)malloc(sizeof(StudentLinkedListNode))
op3=>operation: strcpy(p->StuID,student_id
op4=>operation: p->Grade=grade
st->in->op1->op2->op3->op4->out->e
```



```flow
st=>start: studentLinkedListAdd
io1=>inputoutput: 输入节点指针 head, node
op=>operation: node->next=head
io2=>inputoutput: 输出node
ed=>end: 结束
st->io1->op->io2->ed
```



```flow
start=>start: reverseLinkedList
io1=>inputoutput: 输入头节点head
op1=>operation: 定义节点指针
op2=>operation: p=head
cd=>condition: p->next不为空
op3=>operation: 将p->next指向的节点摘下
op4=>operation: 将该节点用头插法插入链表
io2=>inputoutput: 输出head
e=>end: 结束

start->io1->op1->op2->cd
cd(no,bottom)->io2->e
cd(yes,right)->op3(right)->op4(top)->cd
```

```flow
st=>start: findCrossBeginNode
in=>inputoutput: 链表头指针class1, class2
op1=>operation: 获取两链表的长度L1,L2
cd1=>condition: L1>L2 ?
op2=>operation: L1向前前进(L1-L2)步
op3=>operation: L2向前前进(L2-L1)步
cd2=>condition: class1==class2 ?
op4=>operation: class1=class1->next
op5=>operation: class2=class2->next
ot=>inputoutput: class1
e=>end: 结束
st->in->op1->cd1
cd1(yes)->op2->cd2
cd1(no)->op3->cd2
cd2(yes)->op4->op5(left)->cd2
cd2(no)->ot->e
```



