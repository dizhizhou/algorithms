
#include<iostream>
#include<vector>
#include<math.h>
#include<algorithm>

using namespace std;


class Heap
{
public:
  Heap (int array[], int size)
    {
      m_seq.push_back (size); // m_seq[0] stores the total number of nodes
      for (int i = 0; i < size; i++)
        m_seq.push_back (array[i]);

    }

  virtual ~Heap()
    {
    }

  void Print ();
  void Sort (); // heapsort

private:
  int Parent (int i);
  int Left (int i);
  int Right (int i);  
  void BuildHeap ();
  void MaxHeapify (int i);

private:
  vector<int> m_seq;
};

int 
Heap::Parent (int i)
{
  return floor (i/2);
}

int
Heap::Left (int i)
{
  return 2*i;
}

int 
Heap::Right (int i)
{
  return 2*i + 1;
}

void
Heap::BuildHeap ()
{
  // get the last non leaf node, the last leaf node's parant
  int start = floor(m_seq.at (0)/2);

  for (;start > 0;start--)
    MaxHeapify (start);
}

void
Heap::MaxHeapify (int i)
{
  int left = Left (i);
  int right = Right (i);
  int largest = i;

  // find the largest value among i and its two child

  if ( left <= m_seq.at (0)  && (m_seq.at (i) < m_seq.at (left)) )
    largest = left;

  if ( right <= m_seq.at (0) && (m_seq.at (largest) < m_seq.at (right)) )
    largest = right;

  if (largest != i)
    {
      // switch the largest and i 

      //int tmp = m_seq.at (i);
      //m_seq.at (i) = m_seq.at (largest);
      //m_seq.at (largest) = tmp;

      swap (m_seq.at (i), m_seq.at (largest));

      MaxHeapify (largest);
    }
}

void
Heap::Print ()
{
  for (int i = 1; i < m_seq.size (); i++)
    cout << m_seq.at (i) << " ";
  cout << endl;
}

void
Heap::Sort ()
{
  int last;

  BuildHeap ();
  
  while (last > 1)
    {
      // swap the root(largest value) and the new last
      last = m_seq.at (0);
      swap (m_seq.at (1), m_seq.at (last));
      m_seq.at (0)--;

      // re-build the heap from 1 to the new last
      MaxHeapify (1);
    }
}


int main (int argc, char *argv[])
{
  int array[] = {16,4,10,14,7,9,3,2,8,1};   

  for (int i = 0; i < 10; i++) 
    cout << array[i] << " ";
  cout << endl;

  Heap heap (array, sizeof (array)/sizeof (int)); 

  heap.Sort (); // heap sort
  heap.Print ();

  return 0;
}





