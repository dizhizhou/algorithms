#include <iostream>
#include <queue>

using namespace std;

struct BiNode 
{
  BiNode () 
    : node1 (NULL),
      node2 (NULL),
      data (-1)
    {
    }
  struct BiNode* node1;
  struct BiNode* node2;
  int data;
};

/*NOTE: MUST use a struct (not struct pointer) to transfer data between levels of recursive*/
struct LinkedList
{
  struct BiNode* head;
  struct BiNode* tail;
};

void Init (struct BiNode* root);
void Print (struct BiNode* root);
struct BiNode* TransferToDoubleLinkedList (struct BiNode* root);
void InOrderTransfer (struct BiNode* root, struct LinkedList &head);
void PrintLinkedList (struct BiNode* head);
void PrintLinkedListBack (struct BiNode* tail);

void Init (struct BiNode* root)
{
  root->data = 4;
  
  struct BiNode* node1 = new struct BiNode;
  struct BiNode* node2 = new struct BiNode;
  struct BiNode* node3 = new struct BiNode;
  struct BiNode* node4 = new struct BiNode;
  struct BiNode* node5 = new struct BiNode;
  struct BiNode* node6 = new struct BiNode;

  node1->data = 2;
  node2->data = 5;
  node3->data = 1;
  node4->data = 3;
  node5->data = 6;
  node6->data = 0;

  root->node1 = node1;
  root->node2 = node2;

  node1->node1 = node3;
  node1->node2 = node4;

  node2->node1 = NULL;
  node2->node2 = node5;

  node3->node1 = node6;
  node3->node2 = NULL;

  node4->node1 = NULL;
  node4->node2 = NULL;

  node5->node1 = NULL;
  node5->node2 = NULL;

  node6->node1 = NULL;
  node6->node2 = NULL;

} 

void Print (struct BiNode* root)
{
  queue<struct BiNode* > q;
  int curLevel = 0;
  int nextLevel = 0;

  q.push (root);  
  curLevel++;

  while (q.size () > 0)
    {
      struct BiNode* cur = q.front ();

      cout << cur->data << " ";

      q.pop ();
      curLevel--;

      if (cur->node1 != NULL)
        {
          q.push (cur->node1);
          nextLevel++;
        }
      if (cur->node2 != NULL)
        {
          q.push (cur->node2);
          nextLevel++;
        }

      if (curLevel == 0)
        {
          cout << endl;
          curLevel = nextLevel;
          nextLevel = 0;
        }
    } // while ()
}


struct BiNode* TransferToDoubleLinkedList (struct BiNode* root)
{
  struct LinkedList h;
  h.head = NULL;

  // transfer binary search tree to a doubled linked list with a head pointer
  InOrderTransfer (root, h);

  return h.head;
}

void InOrderTransfer (struct BiNode* root, struct LinkedList &h) 
{
  // base case
  if (root == NULL)
    return;

  InOrderTransfer (root->node1, h);

  if (h.head == NULL)
    {
      // set the most left leaf node as the head of doubled linked list
      h.head = root;
      h.tail = root;
      (h.head)->node1 = NULL;
      (h.tail)->node2 = NULL;
      InOrderTransfer (root->node2, h);
    }
  else
    {
      // add root to the tail
      root->node1 = h.tail;
      (h.tail)->node2 = root;
      // update tail
      (h.tail) = root;
      // save right child and set right child(tail next) to NULL
      struct BiNode* tmp = root->node2;
      root->node2 = NULL;

      InOrderTransfer (tmp, h);
    }
  

}

void PrintLinkedList (struct BiNode* head)
{
  struct BiNode* cur = head;
  struct BiNode* pre = cur;
  cout << "forward sequence: ";
  while (cur != NULL)
    {
      cout << cur->data << " ";
      pre = cur;
      cur = cur->node2;
    }
  cout << endl;

  cout << "back sequence   : ";
  PrintLinkedListBack (pre);
}

void PrintLinkedListBack (struct BiNode* tail)
{
  struct BiNode* cur = tail;
  while (cur != NULL)
    {
      cout << cur->data << " ";
      cur = cur->node1;
    }
  cout << endl;

}



int main (int argc, char* argv[])
{
  struct BiNode* root = new struct BiNode;

  Init (root);
 
  Print (root);

  struct BiNode* head = TransferToDoubleLinkedList (root);

  PrintLinkedList (head);

  return 0;
}
