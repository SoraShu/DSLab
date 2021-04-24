```flow
st=>start: postOrderTraverse
e=>end: end
in=>inputoutput: 根节点root
cd=>condition: root为空
op1=>operation: 打印root->val+" "
op2=>operation: postOrderTraverse(root->left)
op3=>operation: postOrderTraverse(root->right)
st->in->cd(yes)->e
cd(no)->op2(right)->op3->op1(left)->e
```

