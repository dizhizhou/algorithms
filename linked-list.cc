/*Name: Linked list*
 *Skills: template class, reference call by function, virtual deconstructor, 
          new & delete struct pointer or object
  Tips: for the operations in linked list, be careful about following special cases
        1, All:             empty, return value, input value
        2, Delete, Reverse: single node   
        3, Reverse:         double node   
        4, Add, Delete:     head, middle or tail
 */

#include <iostream>
using namespace std;

/*NOTE 1: cannot template a typedef*/
template<typename T>
struct Node
{
  int data;  // use template
  Node<T>* next;
};

template<typename T>
class LinkedList 
{
public:
  LinkedList ()
    : m_head (0)
    { 
    }

  /*All base class MUST have a virtual deconstructor*/
  virtual ~LinkedList ()
    {
    }

  /*operations: user API -- as simple as it can*/

  struct Node<T>* Insert (T &data); // insert data to the head of list
  struct Node<T>* Delete (T &data);
  //struct Node<T>* Search (T &data, LinkedList<T> &list);
  struct Node<T>* Reverse ();
  void Print ();

private:
  /*Internal methods*/  
  bool IsEmpty ();

private:
  struct Node<T> *m_head;
};

/*NOTE 2: template class method format: 
    tempate<typename T> 
    returnValue ClassName<T>::MethodName ()
 */
template<typename T>
bool LinkedList<T>::IsEmpty ()
{
  if (m_head != 0)
    return false;
  else 
    return true;
}


/*NOTE 3: define a new struct node:
  struct variable case:
    struct Node<T> node;
    node.data = 0;
    node.next = 0;
  struct point case: MUST use new
    struct Node<T>* node = new struct Node<T>;
    node->data = 0;
    node->next = 0;

  NOTE 4: 
    new Object
    delete pointer
 */
template<typename T>
struct Node<T>* LinkedList<T>::Insert (T &data)
{
  if ( IsEmpty() == true)
    {
      // this is an empty linked list

      // new a node and set its next to zero
      struct Node<T> *node = new struct Node<T>;
      node->data = data;
      node->next = 0;

      // add it to head
      m_head = node;
    }
  else
    {

      // new a node and set its next the head
      struct Node<T> *node = new struct Node<T>;
      node->data = data;
      node->next = m_head;

      // add it to head
      m_head = node;
    }

  return m_head;
}

template<typename T>
struct Node<T>* LinkedList<T>::Delete (T &data)
{
  if (IsEmpty () == true)
    return m_head;

  if (m_head->data == data)
    {
      // delete head
      struct Node<T>* head;
      head = m_head;       
      m_head = m_head->next;
      delete head;
      return m_head;
    }
  else
    {
      struct Node<T>* cur;
      struct Node<T>* pre;
      pre = m_head; 
      cur = m_head->next;
      
      while ( cur->data != data)
        {
          cur = cur->next;
          pre = pre->next;

          // NOTE 5: cannot put this into wihle loop conditions
          //         because if cur == 0, then cur->data will cause error
          if (cur == 0) 
            break;
        } 

      // delete tail
      if ( cur->data == data && cur == 0)
        {
          pre->next = 0;
          delete cur;
          return m_head;
        }
 
      // delete middle node
      if ( cur->data == data && cur->next != 0)
        {
          pre->next = cur->next;
          delete cur;
          return m_head;
        }
    }
}

template<typename T> 
struct Node<T>* LinkedList<T>::Reverse ()
{
   // empty
   if (IsEmpty () == true)
    return m_head;

   // only head
   if ( m_head->next == 0)
    return m_head;

   // two node case
   if ( m_head->next->next == 0)
     {
       m_head->next->next = m_head;
       m_head = m_head->next;
       m_head->next->next = 0;
       return m_head;
     }

   // define three pointers
   struct Node<T>* parent;
   struct Node<T>* me;
   struct Node<T>* child;

   parent = m_head;
   me = parent->next;
   child = me->next;
  
   parent->next = 0;
   while (child != 0)
     {
       me->next = parent;
     
       // move forward
       parent = me;
       me = child;
       child = child->next;
     }

   // reverse last
   me->next = parent;
   m_head = me;
   return m_head;
}


template<typename T> 
void LinkedList<T>::Print ()
{
  if (IsEmpty () == true)
    return;

  struct Node<T> *node = m_head;
  while (node != 0)
  {
    std::cout << node->data << " ";
    node = node->next;
  }

  cout << endl;
}

int main (int argc, char *argv[])
{
  typedef int type;

  LinkedList<type> linkList;
  struct Node<type> *node;

  cout << "Insert : ";
  int data = 8;
  node = linkList.Insert (data);
  node = linkList.Insert (++data);
  node = linkList.Insert (++data);
  linkList.Print ();

  cout << "Reverse: ";
  node = linkList.Reverse ();
  linkList.Print ();

  cout << "Delete : ";
  data = 8;
  node = linkList.Delete (data);
  linkList.Print ();

  cout << "Reverse: ";
  node = linkList.Reverse ();
  linkList.Print ();

/*
  data = 11;
  node = linkList.Insert (data);
  linkList.Print ();
*/

  return 0;
}
