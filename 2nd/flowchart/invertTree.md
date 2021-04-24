```flow
st=>start: invertTree
e=>end: end
in=>inputoutput: 根节点root
out0=>inputoutput: NULL
out1=>inputoutput: createTreeNode(root->val,invertTree(root->right),invertTree(root->left))
cd=>condition: root为空
st->in->cd(yes,right)->out0->e
cd(no)->out1->e
```

