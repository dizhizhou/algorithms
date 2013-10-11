/*Name: Queue*
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
 * Queue: FIFO m_head -> Node -> Node -> Node -> NULL
                                          ^
                                          |
                                        m_tail
   NOTE 1: queue needs two pointers: head, tail
 */
template<typename T>
class Queue
{
public:
  Queue () 
    : m_head (0),
      m_tail (0)
    {
    }
  
  virtual ~Queue () 
    { 
    }

  /*API*/
  struct Node<T>* Enqueue (T &data); // add in the tail (m_tail)
  struct Node<T>* Dequeue ();        // del in the head (m_head)
  void Print ();

private:
  bool IsEmpty ();

private:
  struct Node<T>* m_head;
  struct Node<T>* m_tail;
};

template<typename T>
bool Queue<T>::IsEmpty ()
{
  if (m_head != 0)
    return false;
  else 
    return true;
}

template<typename T>
void Queue<T>::Print ()
{
  if (IsEmpty () == true)
    {
      cout << "null" << endl;
      return;
    }

  struct Node<T>* cur = m_head;
 
  while (cur != 0)
    {
      cout << cur->data << " ";
      cur = cur->next;
    }

  cout << endl;

}

template<typename T>
struct Node<T>* Queue<T>::Dequeue ()
{
  if (IsEmpty () == true)
    return m_head;

  if (m_head->next == 0)
    {
      delete m_tail;
      m_head = 0;
      m_tail = 0;
      return m_head;
    }

  struct Node<T>* cur = m_head;
  m_head = m_head->next;
  delete cur;

  return m_head;
}

template<typename T>
struct Node<T>* Queue<T>::Enqueue (T &data)
{
  if (IsEmpty () == true)
    {
      //first node
      struct Node<T>* node = new struct Node<T>;
      node->data = data;
      node->next = 0;
  
      m_head = node;
      m_tail = node;
    }
  else
    {
      //add to the tail
      struct Node<T>* node = new struct Node<T>;
      node->data = data;
      node->next = 0;
  
      // update tail to the new node in the end of queue
      m_tail->next = node;
      m_tail = node;
    }

  return m_head;
}


int main (int argc, char *argv[])
{
  typedef int type;

  Queue<type> queue;
  struct Node<type> *node;

  cout << "Enqueue   : " << endl;
  int data = 8;
  node = queue.Enqueue (data);
  queue.Print ();
  node = queue.Enqueue (++data);
  queue.Print ();
  node = queue.Enqueue (++data);
  queue.Print ();

  cout << "Dequeue    : " << endl;
  node = queue.Dequeue ();
  queue.Print ();
  node = queue.Dequeue ();
  queue.Print ();
  node = queue.Dequeue ();
  queue.Print ();

  return 0;
}
