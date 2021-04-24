```flow
st=>start: maxPathSum
e=>end: end
in=>inputoutput: 节点root，整数sum
out0=>inputoutput: sum
out=>inputoutput: max(Ls,Rs)
cd=>condition: root为空
op1=>operation: sum增加root->val
op2=>operation: int Ls=maxPathSum(root->left,sum)
op3=>operation: int Rs=maxPathSum(root->right,sum)
st->in->cd(yes,right)->out0->e
cd(no)->op1->op2->op3->out->e
```

