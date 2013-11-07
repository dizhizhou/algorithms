/*

 0, define the interfaces:

    bool CheckTreeBalance (Node* node)

 1, special cases:

    if ( node == null )
      return true;

 2, bruce force:
  
    int height_left = GetHeight (node->left);
    int height_right = GetHeight (node->right);
    if (abs (height_left - height_right) > 1)
      return false;
    else
      return CheckTreeBalance (node->left) && CheckTreeBalance (node->right); 
  
3, subroutes

    int GetHeight (Node* node)
      {
        if (node == NULL) 
          return 0;

        return max ( GetHeight (node->left), GetHeight (node->right) ) + 1;
      }

 


*/
