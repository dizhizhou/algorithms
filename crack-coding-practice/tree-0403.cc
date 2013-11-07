/*
  suppose: int array[]

  input: int array [], increasing order sorted, 
         size

  output: binary search tree

  constraint: bst with min height

  analysis: min height -> balance tree -> root is in the middle of sorted array[]
*/

class Node
{
public:
  Node ()
    : key (0),
      left (NULL),
      right (NULL)
    {
    }
  
  virtual ~Node () 
    {
    }

private:
  int key;
  Node* left;
  Node* right;
};

Node* BuildTree (int array[], int low, int high)
{
  if (low < high)
    return NULL;

  // create a node whose key is array[mid]
  int mid = floor( (low+high)/2 );
  Node* node = new Node;
  node->key = array[mid];
  node->left = BuildTree (array[], low, mid-1);
  node->right = BuildTree (array[], mid + 1, high)
  return node;
}


// step 1: interfaces
Node* BuildBst (int array[], int size)
{
// step 2: special cases
  if (size <=0)
    return NULL;

  // step 3: algorithm
  return BuildTree (int array[], 0, size - 1);
}
