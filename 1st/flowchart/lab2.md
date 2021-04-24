```flow
st=>start: StackEmpty
in=>inputoutput: Stack S
cd=>condition: S.top==-1 ?
out1=>inputoutput: 1
out2=>inputoutput: 0
e=>end: end
st->in->cd
cd(yes)->out1->e
cd(no)->out2->e
```

```flow
st=>start: Push
in=>inputoutput: 栈指针s,数据e
cd1=>condition: 栈满 ？
out1=>inputoutput: 0
op1=>operation: s->top++
op2=>operation: s->data[s->top]=e
out2=>inputoutput: 1
e=>end: end
st->in->cd1
cd1(no)->op1->op2->out2->e
cd1(yes,right)->out1->e
```

```flow
st=>start: Pop
in=>inputoutput: 栈指针S,数据指针e
cd=>condition: 栈为空 ?
out1=>inputoutput: 0
op1=>operation: *e=S->data[S->top]
op2=>operation: S->top--
out2=>inputoutput: 1
e=>end: end
st->in->cd
cd(yes,right)->out1->e
cd(no)->op1->op2->out2->e
```

```flow
st=>start: GetTop
in=>inputoutput: 栈S，元素e
cd=>condition: 栈S为空
out1=>inputoutput: 0
op=>inputoutput: *e=S.data[S.top]
out2=>inputoutput: 1
e=>end: end
st->in->cd
cd(yes,right)->out1->e
cd(no)->op->out2->e
```

```flow
st=>start: QueueEmpty
in=>inputoutput: 队列Q
cd=>condition: 队列包含两栈
	长度和为0
out0=>inputoutput: 0
out1=>inputoutput: 1
e=>end: end
st->in->cd
cd(yes)->out0->e
cd(no)->out1->e
```

```flow
st=>start: EnQueue
in=>inputoutput: 队列指针Q,数据e
cd=>condition: 队列Q满 ?
out0=>inputoutput: 0
op=>operation: 向Q的stack1域压入e
out1=>inputoutput: 1
e=>end: end
st->in->cd(yes,right)->out0->e
cd(no)->out1->e
```

```flow
st=>start: Dequeue
e=>end: end
in=>inputoutput: 队列指针Q,数据指针e
cd1=>condition: 队列为空 ?
out0=>inputoutput: 0
cd2=>condition: Q的stack2
		不为空 ？
op1=>operation: 从Q的stack2弹出元素
out1=>inputoutput: 1
op2=>operation: 获取Q的stack1的数组拷贝
op3=>operation: 数组元素逆序
依次压入stack2

st->in->cd1(yes,right)->out0->e
cd1(no)->cd2(yes,right)->op1->out1->e
cd2(no)->op2->op3->op1
```

```flow
st=>start: GetHead
in=>inputoutput: 队列Q,数据指针e
out0=>inputoutput: 0
out1=>inputoutput: 1
e=>end: end
cd1=>condition: Q为空 ?
cd2=>condition: Q的stack2
	不为空
op1=>operation: 获取stack2的栈顶元素
op2=>operation: 获取stack1的数组拷贝
op3=>operation: e接受数组的第一个元素
st->in->cd1(yes,right)->out0->e
cd1(no)->cd2(yes,right)->op1->out1->e
cd2(no)->op2->op3->out1->e
```

```flow
st=>start: QueueToArray
e=>end: end
in=>inputoutput: 队列Q,数组seq
op1=>operation: DataType temp[MaxSize]
op2=>operation: StackToArray(Q.stack2,temp)
op3=>operation: *seq=temp[i]
op4=>operation: seq++
op5=>operation: StackToArray(Q.stack1,seq)
op0=>operation: int i=StackLength(Q.stack2)-1
opfor=>operation: i--
cd=>condition: i>=0
st->in->op1->op2->op0->cd
cd(yes,right)->op3(right)->op4(right)->opfor(top)->cd
cd(no)->op5->e
```

