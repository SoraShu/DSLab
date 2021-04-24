```flow
st=>start: start
e=>end: end
in=>inputoutput: int size,int[] data
op1=>operation: getDigits(buff, data)
op2=>operation: TreeNodePtr tree_root = createTreeWithLevelOrder(data, size)
op3=>operation: printf("Answer for task 1 is: \n")
op4=>operation: printf("preOrderTraverse is:");
op5=>operation: preOrderTraverse(tree_root)
opn1=>operation: printf("\n");
opn2=>operation: printf("\n");
opn3=>operation: printf("\n");
op6=>operation: printf("inOrderTraverse is:")
op7=>operation: inOrderTraverse(tree_root)
op8=>operation: printf("postOrderTraverse is:")
op9=>operation: postOrderTraverse(tree_root)
op10=>operation: int max_path_sum = maxPathSum(tree_root, 0)
op11=>operation: printf("Answer for task 2 is : %d \n", max_path_sum)
op12=>operation: int weight_sum = sumOfLeftLeaves(tree_root)
op13=>operation: printf("Answer for task 3 is : %d \n", weight_sum)
op14=>operation: TreeNodePtr invert_tree_root = invertTree(tree_root)
op15=>operation: printf("inOrderTraverse for task 4 is:")
op16=>operation: inOrderTraverse(invert_tree_root)
op17=>operation: printf("\n\n")
st->in->op1->op2->op3->op4->op5->opn1->op6->op7->opn2->op8->op9->opn3->op10->op11->op12->op13->op14->op15->op16->op17->e
```
