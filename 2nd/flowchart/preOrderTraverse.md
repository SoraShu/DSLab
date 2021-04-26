---
export_on_save:
    puppeteer: ["png"] # 保存文件时导出 PNG
---

```flow
st=>start: preOrderTraverse
e=>end: end
in=>inputoutput: 根节点root
cd=>condition: root为空
op1=>operation: 打印root->val+" "
op2=>operation: preOrderTraverse(root->left)
op3=>operation: preOrderTraverse(root->right)
st->in->cd(yes)->e
cd(no)->op1(right)->op2->op3(left)->e
```

