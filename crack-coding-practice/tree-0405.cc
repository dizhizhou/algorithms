

bool DoCheckBST (Node* root, int pre)
{
  if (root == NULL)
    return true;

  if (DoCheckBST (root->left, pre) == false) 
    return false;

  // if there is any value smaller than pre, than it is not a bst
  if (root->key < pre) 
    return false;

  // keep track of the previous visited value
  pre = root->key;

  if (DoCheckBST (root->right, pre) == false)
    return false;

  return true;
}


bool CheckBST (Node* root)
{
  if (root == NULL)
    return true;

  int pre = INT_MIN;  // set the pre visit value to the min

  return DoCheckBST (root, pre);
}
