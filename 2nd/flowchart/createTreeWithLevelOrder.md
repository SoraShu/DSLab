---

export_on_save:
    puppeteer: ["png"] # 保存文件时导出 PNG
---

```flow
st=>start: createTreeWithLevelOrder
e=>end: end
in=>inputoutput: int[] data,int size
outN=>inputoutput: NULL
outH=>inputoutput: Thead
cd1=>condition: data[0]是否为-1
cd2=>condition: 队列Q为空
cd3=>condition: T为空
cd4=>condition: ++i>=size
cd5=>condition: data[i]!=-1
cd6=>condition: ++i>=size
cd7=>condition: data[i]!=-1
op1=>operation: 初始化队列Q
树节点指针T=NULL
整数i=0
op2=>operation: 创建节点Thead
初始化其val域为data[0],
两个指针域为NULL
op3=>operation: 根节点入队
op4=>operation: 用指针T获取队列头元素
队列头元素出队
op5=>operation: i自增两次
两个NULL连续入队
op6=>operation: 在T的左孩子处创建节点
val域初始化为data[i]，
两个指针域初始化为NULL
op7=>operation: T的左孩子入队
op8=>operation: 在T的右孩子处创建节点
val域初始化为data[i]，
两个指针域初始化为NULL
op9=>operation: T的右孩子入队
cd8=>condition: 队列Q为不为空
op10=>operation: 队列Q头元素出队
st->in->cd1(yes,right)->outN->e
cd1(no)->op1->op2->op3->cd2(yes)->op4->cd3
cd3(yes)->op5(top)->cd2
cd3(no,bottom)->cd4(yes,right)->cd8
cd4(no)->cd5(yes,right)->op6->op7
cd5(no)->op7->cd6(yes,right)->cd8
cd6(no)->cd7(yes,right)->op8->op9
cd7(no)->op9(left)->cd2
cd8(yes,right)->op10(top)->cd8
cd8(no)->outH->e
```

