/*Name: Binary tree
 *Operations: pre-order traversal, in-order traversal, post-order traversal, print level order(BFS + watcher)
 *Skills: queue, map class in C++
 *TBD:  pre/in/post order un-recur
 *      maximum heigth/depth
 */

#include <iostream>
#include <string>
#include <queue>
#include <map>

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


  // Tree traversal:
  //   depth first search: end condition + sequence of (Xorder of root, Xorder of left and Xorder of right)
  void PreorderTraversal (struct Node<T> *node);
  void InorderTraversal (struct Node<T> *node);
  void PostorderTraversal (struct Node<T> *node);


  //   breadth first search (print by level): single queue +  watcher pointer/count numbers
  void PrintBFS ();

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

  bool usingPointer = false; // watch pointer
  bool usingCounter = true;  // counter

  queue<struct Node<T>* > queueNodes; 
  int nextLevelNodesNum = 0;  // another way to do level by level
  int curLevelNodesNum = 0;

  struct Node<T>* cur = m_root;
  cout << cur->key << endl; // visit cur
  cur->visit = true;
  queueNodes.push (cur);
  curLevelNodesNum++;

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

     if (cur == watcher && usingPointer)
       cout << endl;

     queueNodes.pop ();
     curLevelNodesNum--;

     if (cur->left != 0)
       {
         if (cur->left->visit == false)
           {
             cout << cur->left->key << " ";
             cur->visit = true;
             queueNodes.push (cur->left);

             nextLevelNodesNum++;

             if (cur->left == watcher && usingPointer)
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
       }

     if (cur->right != 0)
       {
         if (cur->right->visit == false)
           {
             cout << cur->right->key << " ";
             cur->visit = true;
             queueNodes.push (cur->right);

             nextLevelNodesNum++;

             if (cur->right == watcher && usingPointer)
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
       }

     if (curLevelNodesNum == 0 && usingCounter)
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



int main (int argc, char *argv[])
{
  typedef int type;

  Tree<type> tree;
  struct Node<type>* root;

  root = tree.Init ();

  cout << "BFS: " << endl;
  tree.PrintBFS ();
   
  cout << "pre-order: " << endl;
  //tree.PreorderTraversal (root);

  cout << endl;
  cout << "in-order: " << endl;
  //tree.InorderTraversal (root);

  cout << endl;
  cout << "post-order: " << endl;
  //tree.PostorderTraversal (root);

  cout << endl;

  return 0;
}
