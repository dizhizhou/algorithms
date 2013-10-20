/*Name: Red-Black tree with sentinel leaf node*
  Skills: constructor in struct
 */

#include <iostream>
#include <queue>

using namespace std;

template<typename T>
struct Node 
{
  Node ()
     : left (0),
       right (0),
       p (0),
       colour ("red")
    {
    }
 
  T key;                  // key value
  struct Node<T>* left;   // left child
  struct Node<T>* right;  // right child
  struct Node<T>* p;      // parant
  string colour;           // color  
};

template<typename T>
class RedBlackTree
{
public:

  RedBlackTree ()
      : m_nil (0),
        m_root (0)
    {
      // create sentinel node
      m_nil = new struct Node<T>;

      // set root to sentinel node
      m_root = m_nil; 

      // configure sentinel node
      m_nil->p = m_root;
      m_nil->left = m_root;
      m_nil->right = m_root;
      m_nil->colour = "black";
       
    }

  virtual ~RedBlackTree ()
    {
      delete m_nil;
      delete m_root;
    }
  /*APIs*/
  bool Insert (T &key);
 // bool Delete ();
  void Print ();   

  void LeftRotate (T &x);

private:
  struct Node<T>* m_nil; // sentinel node
  struct Node<T>* m_root;
};

template<typename T>
bool RedBlackTree<T>::Insert (T &key)
{
  struct Node<T> *node = new struct Node<T>;  
  struct Node<T> *cur = m_root;
  struct Node<T> *pre = m_nil;

  while (cur != m_nil)
    {
      pre = cur;
      if ( key < cur->key )
        cur = cur->left;
      else if ( key >= cur->key )
        cur = cur->right;
    }

  if (pre == m_nil)             // first node
    m_root = node;
  else if ( key < pre->key )  // add new node in the left leaf
    pre->left = node;
  else if ( key >= pre->key ) // add new node in the right leaf
    pre->right = node;

  // configure new node
  node->p = pre;
  node->key = key;
  node->left = m_nil;
  node->right = m_nil;
  node->colour = "red";

}

template<typename T>
void RedBlackTree<T>::Print ()
{
   // print level by level 
   queue<struct Node<T>* > q;
   int curLevelNum = 0;
   int nextLevelNum = 0;

   struct Node<T> *node = m_root;
   q.push (node);
   curLevelNum++;
   
   while (q.size () > 0)
     {
       struct Node<T> *cur = q.front ();
       cout << cur->key << " ";
       q.pop ();
       curLevelNum--;      

       if (cur->left != m_nil)
         {
           q.push (cur->left);
           nextLevelNum++;
         }

       if (cur->right != m_nil)
         {
           q.push (cur->right);
           nextLevelNum++;
         }

       if (curLevelNum == 0)
         {
           curLevelNum = nextLevelNum;
           nextLevelNum = 0;

           cout << endl;
         }
     }
   
}

template<typename T>
void RedBlackTree<T>::LeftRotate (T &node)
{
  // in this version, left rotate to the root node by default
  struct Node<T> *x = m_root;
  struct Node<T> *y = m_root->right;

  x->right = y->left;
  y->left->p = x;

  y->p = x->p;

  if ( x->p == m_nil)
    m_root = y;
  else if ( x == x->left)
    x->p->left = y;
  else
    x->p->right = y;

  y->left = x;
  x->p = y;

}

int main (int argc, char *argv[])
{
  typedef int type;

  RedBlackTree<type> rb;
 
  int i = 5;
  rb.Insert (i);
  i = 2;
  rb.Insert (i);
  i = 8;
  rb.Insert (i);
  i = 1;
  rb.Insert (i);
  i = 4;
  rb.Insert (i);
  i = 3;
  rb.Insert (i);
  i = 6;
  rb.Insert (i);
  i = 7;
  rb.Insert (i);
  i = 10;
  rb.Insert (i);
  i = 9;
  rb.Insert (i);

  cout << "Print: " << endl;
  rb.Print ();

  cout << "left rotate" << endl;
  i = 5;
  rb.LeftRotate (i);
  cout << "Print: " << endl; 
  rb.Print ();
 return 0;
}
