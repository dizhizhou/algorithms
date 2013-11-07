
Node! GetLeftMost (Node* node)
{
  if (node == NULL)
    return NULL;

  while (node->left != NULL)
    node = node->left;

  return node;
}


Node* FindInOrderSuccessor (Node* root, Node* node)
{
  // special cases
  if (root == NULL || node == NULL)
    return NULL;

  /*
    case 1: node has right child or node is the root
    node
       \
      right
    sucessor is the left most node of the node->right subtree
  */
  if (node->right != NULL || node == root)
    return GetLeftMost (node->right);
 
  /*
    case 2: node's parant has left child
        p
       /
     node
  */
  if (node->p->left == node)
    return node->p;


  /*
    case 3: find node's parant until this parant has right paranet
        p'
       /
    p_n
      \
      ...
       \
        p
         \
        node
  */
  Node* n = node->p;
  while (n != NULL)
    {
      if (n->p->left == n)
        return n->p;
      n = n->p;
    }

  return NULL;
}
