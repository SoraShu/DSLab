```flow
st=>start: inOrderTraverse
e=>end: end
in=>inputoutput: 根节点root
cd=>condition: root为空
op1=>operation: 打印root->val+" "
op2=>operation: inOrderTraverse(root->left)
op3=>operation: inOrderTraverse(root->right)
st->in->cd(yes)->e
cd(no)->op2(right)->op1->op3(left)->e
```

