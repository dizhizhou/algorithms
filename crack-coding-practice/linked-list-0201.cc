
#include <iostream>
#include <set>

using namespace std;

struct Node 
{
  int key;
  struct Node *next;
};

class LinkedList 
{
public:
  LinkedList ()
    : m_head (NULL)
    {
    }

  virtual ~LinkedList ()
    {
    }

  void Add (int key);
  void Print ();
  void RemoveDup ();  // method 1: use hash table (set); method 2: use runner (not additional buffer need )

private:
  struct Node *m_head;
};

void
LinkedList::Add (int key)
{
  struct Node *node = new struct Node;
  node->key = key;
  node->next = NULL;

  if (m_head == NULL)
    m_head = node;
  else
    {
      // add to the head
      node->next = m_head;
      m_head = node;
    }
}

void
LinkedList::Print ()
{ 
  struct Node *cur = m_head;
  while (cur!=0)
    {
      cout << cur->key << " ";
      cur = cur->next;
    }
  cout << endl;
}

void
LinkedList::RemoveDup ()
{
  // special cases

  // case 1: non list or only 1 element
  if (m_head == NULL || m_head->next == NULL)
    return;

/*  method 1:
  set<int> mapCount;

  mapCount.insert (m_head->key); // insert the first node in to set

  struct Node *cur = m_head->next; // start from the second node  
  struct Node *pre = m_head; 
  while ( cur != 0 )
    {
      set<int>::iterator it = mapCount.end ();
      it = mapCount.find (cur->key);
      if (it != mapCount.end ())
        {
          // duplicate node, delete
          pre->next = cur->next;
          delete cur;
          cur = pre->next; // move to next node
        }
      else
        {
          // new node
          mapCount.insert (cur->key);
          pre = cur;
          cur = cur->next;
        }
    }
*/

/* method 2: runner*/
  struct Node *slow = m_head;

  while (slow!=0)
    {
      struct Node* fast = slow;
      while ( fast->next != 0 )
        {
          if (fast->next->key == slow->key)
            {
              // delete fast->next
              struct Node* tmp = fast->next;
              fast->next = fast->next->next;
              delete tmp; // we must use delete here
            }
          else
            {
              fast = fast->next;
            }
        }
      slow = slow->next;  
    }
}

int main (int argc, char* argv[])
{
  // suppose: int, single linked list
  LinkedList llist;
  
  llist.Add (1);
  llist.Add (1);
  llist.Add (2);
  llist.Add (4);
  llist.Add (2);

  llist.Print ();
  llist.RemoveDup ();
  llist.Print ();


  return 0; 
}
