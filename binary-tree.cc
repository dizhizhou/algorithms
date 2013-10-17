/*Name: Binary tree
 *Operations: pre-order traversal, in-order traversal, post-order traversal, print level order(BFS + watcher)
 *            in both cursive and non-cursive version
 *Skills: queue, map class in C++
 */

#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <stack>

using namespace std;

template<typename T>
struct Node
{
  T key;
  struct Node<T>* left;
  struct Node<T>* right;
  bool visit;
};

template<typename T>
class Tree 
{
public:
  Tree () 
      : m_root (0)
    {
    }
  
  virtual ~Tree ()
    {
    }

  /*APIs*/

  // init a fixed binary tree       
  //         1
  //       3   5
  //      4 7 6 
  //     2     8
  struct Node<T>* Init ();


  // Tree traversal: all operations have the O(N) time complexity

  //   depth first search (recur): end condition + recursive sequence of (Xorder of left and Xorder of right)
  void PreorderTraversal (struct Node<T> *node);
  void InorderTraversal (struct Node<T> *node);
  void PostorderTraversal (struct Node<T> *node);

  //   depth first search (non recur): single stack
  void NonrecurPreorderTraversal (struct Node<T> *node); // + anti recursive sequence of (Xorder of left and Xorder of right)
  void NonrecurInorderTraversal (struct Node<T> *node); // + continue to traversal left until it faces the leaf node, then visit, pop and go to right
  void NonrecurPostorderTraversal (struct Node<T> *node);
  //  http://crackprogramming.blogspot.ca/2012/11/non-recursive-binary-tree-traversal.html

  //   breadth first search (print by level): single queue +  watcher pointer/count numbers
  void PrintBFS ();  // NOTE: this can also be used to find the heigth and depth of a tree


private:
  bool IsEmpty ();
  struct Node<T>* GetNode (T &key);

private:
  struct Node<T>* m_root;
};

template<typename T>
bool Tree<T>::IsEmpty ()
{
  if (m_root == 0)
    return true;
  else
    return false;
}

template<typename T>
struct Node<T>* Tree<T>::GetNode(T &key)
{
  struct Node<T>* node = new struct Node<T>;
  node->key = key;
  node->left = 0;
  node->right = 0;
  node->visit = false; 

  return node;
}

template<typename T>
struct Node<T>* Tree<T>::Init ()
{
  if (IsEmpty() == false)
    return m_root;

  int key = 1;
  struct Node<T>* node1 = GetNode (key);
  key = 3;
  struct Node<T>* node2 = GetNode (key);
  key = 5;
  struct Node<T>* node3 = GetNode (key);
  key = 4;
  struct Node<T>* node4 = GetNode (key);
  key = 7;
  struct Node<T>* node5 = GetNode (key);
  key = 6;
  struct Node<T>* node6 = GetNode (key);
  key = 2;
  struct Node<T>* node7 = GetNode (key);
  key = 8;
  struct Node<T>* node8 = GetNode (key);

  node1->left = node2;
  node1->right = node3;
  node2->left = node4;
  node2->right = node5;
  node4->left = node7;
  node3->left = node6;
  node6->right = node8;

  m_root = node1;

  return m_root;
}

template<typename T>
void Tree<T>::PrintBFS ()
{
  if (IsEmpty () == true)
    {
      cout << "empty tree" << endl;
      return;
    }

  queue<struct Node<T>* > queueNodes; 
  int nextLevelNodesNum = 0;  // another way to do level by level
  int curLevelNodesNum = 0;

  struct Node<T>* cur = m_root;
  cout << cur->key << endl; // visit cur

  queueNodes.push (cur);
  curLevelNodesNum++;

  while (!queueNodes.empty ())
   {
     cur = queueNodes.front ();

     queueNodes.pop ();
     curLevelNodesNum--;

     if (cur->left != 0)
       {
         cout << cur->left->key << " ";
         queueNodes.push (cur->left);

         nextLevelNodesNum++;
       }

     if (cur->right != 0)
       {
         cout << cur->right->key << " ";
         queueNodes.push (cur->right);

         nextLevelNodesNum++;
       }

     if (curLevelNodesNum == 0)
       {
         // this is the end of level
         cout << endl;
         
         // update current level to the next level
         curLevelNodesNum = nextLevelNodesNum;
         // reset the next level node number to zero
         nextLevelNodesNum = 0;
       }
 
   }// while ()

}

template<typename T>
void Tree<T>::PreorderTraversal (struct Node<T> *node)
{
  if (node == 0)
      return;
 
  // visit node
  cout << node->key << " ";
  node->visit = true;

  PreorderTraversal(node->left);
  PreorderTraversal(node->right);
}

template<typename T>
void Tree<T>::InorderTraversal (struct Node<T> *node)
{
  if (node == 0)
      return;
 
  InorderTraversal(node->left);

  // visit node
  cout << node->key << " "; 
  node->visit = true;

  InorderTraversal(node->right);
}

template<typename T>
void Tree<T>::PostorderTraversal (struct Node<T> *node)
{
  if (node == 0)
      return;
 
  PostorderTraversal(node->left);
  PostorderTraversal(node->right);

  // visit node
  cout << node->key << " "; 
  node->visit = true;
}

template<typename T>
void Tree<T>::NonrecurPreorderTraversal (struct Node<T> *node)
{
  if (node == 0)
    return;

  stack<struct Node<T>* > stackNodes; 

  // push root into stack
  stackNodes.push (node);

  while (!stackNodes.empty ()) // stackNodes.size != 0
    {
      struct Node<T>* top = stackNodes.top ();
      // visit node
      cout << top->key << " ";

      stackNodes.pop ();

      if ( top->right != 0 )
        stackNodes.push (top->right);
      if ( top->left !=0 )
        stackNodes.push (top->left);
    }

}

template<typename T>
void Tree<T>::NonrecurInorderTraversal (struct Node<T> *node)
{
  if (node == 0)
    return;

  stack<struct Node<T>* > stackNodes; 
  struct Node<T>* cur = node;

  while ( !stackNodes.empty () || cur ) // stackNodes.size != 0
    {      
 
      // If this is a empty node, it means that we face the left empty child of leaf node;
      // Operations: visit node, pop top node and then go to its right
      if ( cur == 0 )
        {
          struct Node<T>* top = stackNodes.top ();
          cout << top->key << " ";
          stackNodes.pop ();
          cur = top-> right;
        }
      else
        { // if this is not an empty node, we just keep traversal the left node until we face the leaf node
          stackNodes.push (cur);
          cur = cur->left;
        }
    } // while
}

template<typename T>
void Tree<T>::NonrecurPostorderTraversal (struct Node<T> *node)
{
  if (node == 0)
    return;

  stack<struct Node<T>* > stackNodes;
  struct Node<T>* cur = node;
  struct Node<T>* pre = 0; // always equal to the previous visited node
  
  stackNodes.push (cur);

  // once the node is visited, pop it
  while (!stackNodes.empty ())
    {
      cur = stackNodes.top ();

      // in following cases: visit node when cur is the leaf node
      //       (1)        (2)     (3)
      //   pre ->  0
      //   cur -> root     pre    pre
      //                   /       \
      //                 cur       cur
      //  (1): this case happens in the beginning 
      //  (2): this case happens when the cur goes down along the left path
      //  (3): this case happens when left child is visited and the parent has the right child
      if (!pre || pre->left == cur || pre->right == cur)
        {
          if (cur->left)
            stackNodes.push (cur->left);
          else if (cur->right)
            stackNodes.push (cur->right);
          else
            {
              cout << cur->key << " ";
              stackNodes.pop ();
            }
        }
      // in following cases: this case only happens after the left child (pre) being visited
      //                     when cur does not have right child, visit node
      //   cur
      //   /
      //  pre
      //
      else if ( cur->left == pre )
        {
          if (cur->right)
            stackNodes.push (cur->right);  
          else
            {
              cout << cur->key << " ";
              stackNodes.pop ();
            }
        }
       // in following cases: this case only happens after the right child (pre) being visited
       //                     in this case,  both left and right childs are visited, then, the
       //                     root node should be visited now
       //   cur 
       //    \
       //    pre
       //
       else if ( cur->right == pre )
        {
          cout << cur->key << " ";
          stackNodes.pop ();
        }
    
      pre = cur;

    } // while
}

/*  use wactch pointer
template<typename T>
void Tree<T>::PrintBFS ()
{
  if (IsEmpty () == true)
    {
      cout << "empty tree" << endl;
      return;
    }

  queue<struct Node<T>* > queueNodes; 

  struct Node<T>* cur = m_root;
  cout << cur->key << endl; // visit cur

  queueNodes.push (cur);

  // set a watcher to always keep the last node in a level
  struct Node<T>* watcher = 0;
  if (cur->right != 0)
     watcher = cur->right;
  else if (cur->left != 0)
     watcher = cur->left;
  else
     return;
 
  while (!queueNodes.empty ())
   {
     cur = queueNodes.front ();

     if (cur == watcher)
       cout << endl;

     queueNodes.pop ();

     if (cur->left != 0)
       {
         cout << cur->left->key << " ";
         queueNodes.push (cur->left);

         if (cur->left == watcher)
         {
           cout << endl;              
          
           // update watcher
           struct Node<T>* node = cur->left;
           if (node->right != 0)
             watcher = node->right;
           else if (node->left != 0)
             watcher = node->left;
         }
       }

     if (cur->right != 0)
       {
         cout << cur->right->key << " ";
         queueNodes.push (cur->right);

         if (cur->right == watcher)
         {
           cout << endl;              
          
           // update watcher
           struct Node<T>* node = cur->right;
           if (node->right != 0)
             watcher = node->right;
           else if (node->left != 0)
             watcher = node->left;
         }
       }
   }// while ()

}
*/

int main (int argc, char *argv[])
{
  typedef int type;

  Tree<type> tree;
  struct Node<type>* root;

  root = tree.Init ();

  cout << "BFS: " << endl;
  tree.PrintBFS ();
  cout << endl;
  
  cout << "pre-order: " << endl;
  tree.PreorderTraversal (root);
  cout << endl;
  cout << "pre-order (non-recur): " << endl;
  tree.NonrecurPreorderTraversal (root);
  cout << endl;

  cout << endl;
  cout << "in-order: " << endl;
  tree.InorderTraversal (root);
  cout << endl;
  cout << "in-order (non-recur): " << endl;
  tree.NonrecurInorderTraversal (root);
  cout << endl;

  cout << endl;
  cout << "post-order: " << endl;
  tree.PostorderTraversal (root);
  cout << endl;
  cout << "post-order (non-recur): " << endl;
  tree.NonrecurPostorderTraversal (root);

  cout << endl;

  return 0;
}
