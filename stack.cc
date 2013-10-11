/*Name: Linked list*
 */

#include <iostream>

using namespace std;

template<typename T>
struct Node
{
  T data;
  struct Node<T>* next;
};


/**
 * Stack: LIFO m_head -> Node -> Node -> Node -> NULL
 */
template<typename T>
class Stack
{
public:
  Stack () 
    : m_head (0)
    {
    }
  
  virtual ~Stack () 
    { 
    }

  /*API*/
  struct Node<T>* Push (T &data);  // add in the head (m_head)
  struct Node<T>* Pop ();          // del in the head (m_head)
  void Print ();

private:
  bool IsEmpty ();

private:
  struct Node<T>* m_head;
};

template<typename T>
bool Stack<T>::IsEmpty ()
{
  if (m_head != 0)
    return false;
  else 
    return true;
}

template<typename T>
void Stack<T>::Print ()
{
  if (IsEmpty () == true)
    return;

  struct Node<T>* cur = m_head;
 
  while (cur != 0)
    {
      cout << cur->data << " ";
      cur = cur->next;
    }

  cout << endl;

}

template<typename T>
struct Node<T>* Stack<T>::Pop ()
{
  if (IsEmpty () == true)
    return m_head;

  struct Node<T>* cur = m_head;
  m_head = m_head->next;
  delete cur;

  return m_head;
}

template<typename T>
struct Node<T>* Stack<T>::Push (T &data)
{
  if (IsEmpty () == true)
    {
      //first node
      struct Node<T>* node = new struct Node<T>;
      node->data = data;
      node->next = 0;
  
      m_head = node;
    }
  else
    {
      //add to the head
      struct Node<T>* node = new struct Node<T>;
      node->data = data;
      node->next = m_head;
  
      m_head = node;
    }

  return m_head;
}


int main (int argc, char *argv[])
{
  typedef int type;

  Stack<type> stack;
  struct Node<type> *node;

  cout << "Push   : " << endl;
  int data = 8;
  node = stack.Push (data);
  node = stack.Push (++data);
  node = stack.Push (++data);
  stack.Print ();

  cout << "Pop    : " << endl;
  node = stack.Pop ();
  stack.Print ();

  return 0;
}
