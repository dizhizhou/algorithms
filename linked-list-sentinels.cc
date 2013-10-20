/*Name: Linked list + sentinels + runner*
  Skills: 
        constructor in struct
        referernce return type: cannot return the ref of local var  (NOTE 1)
        use: pass by reference like this " const Type &data"  // data cannot be modified
        always use struct pointer to create a new node (NOTE 2)
  */

#include <iostream>
using namespace std;

template<typename T>
struct Node
{
  T data; 
  struct Node<T>* next;
};


template<typename T>
class LinkedList 
{
public:
  LinkedList ()
    {
      nil.data = 0; 
      nil.next = &nil; // set sentinel next to it self
      //nil = new struct Node<T>;
      //nil->data = 0;
      //nil->next = nil;
    }

  /*All base class MUST have a virtual deconstructor*/
  virtual ~LinkedList ()
    {
      //delete &nil;
    }

  /*operations: user API -- as simple as it can*/
  struct Node<T>& Insert (const T &data); // insert data to the head of list
  struct Node<T>& Delete (const T &data);
  struct Node<T>& Reverse ();
  struct Node<T>& MakeRunner (); // use runner tech: e.g., 1,2,3,4 -> 1,3,2,4
  void Print ();

private:
  struct Node<T> nil;  // sentinel node, store the total number of node in nil.data
};

template<typename T>
struct Node<T>& LinkedList<T>::Insert (const T &data)
{ 
  // NOTE 2: must use new to create a pointer;
   //        cannot use struct Node<T> node; because node will be destroy after Insert method; so that the nil.next will
   //        be a random value!
  // create a node
  struct Node<T>* node = new struct Node<T>;
  node->data = data;
  node->next = 0;

  // insert a node in the head
  node->next = nil.next;
  nil.next = node;

  // NOTE1: cannot return the reference of local var, such as node;
  //        because the mem of local var will be freed after method running over
  return nil;
}

template<typename T>
struct Node<T>& LinkedList<T>::Delete (const T &data)
{
  struct Node<T>* node = nil.next;
  struct Node<T>* pre = &nil;
  
  while (node != &nil)
    {
      if (node->data == data)
        {
          pre->next = node->next;
          delete node;
          break;
        }
      pre = node;
      node = node->next;
    }

  return nil;
}

template<typename T>
struct Node<T>& LinkedList<T>::Reverse ()
{
  struct Node<T> *pre;
  struct Node<T> *mid;
  struct Node<T> *nex;
 
  pre = &nil;
  mid = nil.next;
  nex = mid->next;

  while (nex != &nil) // include zero, one member node case
    {
      // break from middle
      mid->next = pre;
  
      pre = mid;
      mid = nex;
      nex = nex->next;     
    }

  mid->next = pre;
  nex->next = mid;

  return nil;
}

template<typename T>
struct Node<T>& LinkedList<T>::MakeRunner ()
{
  struct Node<T> *slow;
  struct Node<T> *fast;
  struct Node<T> *slow_next;
  struct Node<T> *fast_next;

  slow = &nil;
  fast = &nil;
  slow_next = 0;
  fast_next = 0;

  // suppose even number of node

  // set slow to the middle point
  int i = 1;
  while (fast->next !=& nil)
    {
      fast = fast->next;

      if ( i % 2 != 0)
        slow = slow->next;

      i++;
    }

  fast = nil.next;
  slow = slow->next;
  fast_next = fast->next;
  slow_next = slow->next;

  i = 0;
  while (slow_next != &nil)
    {
      slow->next = fast->next;
      fast->next = slow;

      fast = fast_next;
      slow = slow_next;
      fast_next = fast_next->next;
      slow_next = slow_next->next;
    }

  slow->next = &nil; // slow is the last node, set it to sentinal
  fast->next = slow;
/*
       cout << nil.next->data 
       << " " << nil.next->next->data 
       << " " << nil.next->next->next->data 
       << " " << nil.next->next->next->next->data 
       << " " << nil.next->next->next->next->next->data 
       << " " << nil.next->next->next->next->next->next->data
       << " " << nil.next->next->next->next->next->next->next->data
       << " " << nil.next->next->next->next->next->next->next->next->data
       << " " << nil.next->next->next->next->next->next->next->next->next->data
       << endl;
*/
}


template<typename T>
void LinkedList<T>::Print ()
{
  struct Node<T> *cur = nil.next;
  while ( cur != &nil)
    {
      cout << cur->data << " ";
      cur = cur->next;
    }

  cout << endl;
}


int main (int argc, char *argv[])
{
  typedef int type;

  LinkedList<type> linkList;
  struct Node<type> node;  

  cout << "Insert : ";
  int data = 1;
  node = linkList.Insert (data);
  node = linkList.Insert (++data);
  node = linkList.Insert (++data);
  node = linkList.Insert (++data);
  node = linkList.Insert (++data);
  node = linkList.Insert (++data);
  node = linkList.Insert (++data);
  node = linkList.Insert (++data);
  linkList.Print ();

  cout << "Reverse: ";
  node = linkList.Reverse ();
  linkList.Print ();

  cout << "Runner: ";
  node = linkList.MakeRunner ();
  linkList.Print ();
  
  cout << "Delete : ";
  data = 8;
  node = linkList.Delete (data);
  linkList.Print ();

   return 0;
}
