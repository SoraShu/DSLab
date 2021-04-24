```flow
st=>start: sumOfLeftLeaves
e=>end: end
in=>inputoutput: 根节点root
out0=>inputoutput: 0
cd1=>condition: root为空
cd2=>condition: root的左孩子不为空且
root的左孩子为叶子节点
out1=>inputoutput: root->left->val+sumOfLeftLeaves(root->right)
out2=>inputoutput: sumOfLeftLeaves(root->left)+sumOfLeftLeaves(root->right)e
st->in->cd1(yes)->out0->e
cd1(no)->cd2(yes)->out1->e
cd2(no)->out2->e
```

