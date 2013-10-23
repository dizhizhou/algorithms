/*Name: sort
  Operations: merge sort
*/

#include <iostream>
#include <vector>
#include <cstdint>
#include <cmath>

using namespace std;

#define MAX 10

class Sort
{
public:
  Sort ()
    {
      Init (); // init the m_seq
    }

  virtual ~Sort ()
    {
    }

  void MergeSort ();

  void Print ();

private:
  void Init ();

  void DoMergeSort (uint32_t p, uint32_t r);
  void Merge (uint32_t p, uint32_t q, uint32_t r);

private:
  vector<int> m_seq;
};

void
Sort::Init ()
{
  for (uint32_t i = MAX; i > 0; i--)
    m_seq.push_back (i);
}

void
Sort::Print ()
{
  for (uint32_t i = 0; i < m_seq.size (); i++)
    cout << m_seq.at (i) << " ";
  cout << endl;
}

void
Sort::MergeSort ()
{
  DoMergeSort (0, m_seq.size () - 1);
}

void 
Sort::DoMergeSort (uint32_t p, uint32_t r)
{
  if ( p < r )
    {
      uint32_t q = floor((r + p)/2);

      // test
      if (0)
        cout << p << " " << q << " | " << q + 1 << " " << r << endl;
   
      DoMergeSort (p, q);
      DoMergeSort (q+1, r);
      Merge (p, q, r);
    }
}

void 
Sort::Merge (uint32_t p, uint32_t q, uint32_t r)
{
  vector<int> left;
  vector<int> right;

  // save left and right seqs to two new dynamic arrays
  for (uint32_t i = p; i <= q; i++)
    left.push_back (m_seq.at (i));

  for (uint32_t j = q + 1; j <= r; j++ )
    right.push_back (m_seq.at (j));

  //test
if (0)
{
   cout << " left ";
   for (uint32_t i = 0; i < left.size (); i++)
      cout << left.at (i) << " ";

   cout << " | right ";
   for (uint32_t i = 0; i < right.size (); i++)
      cout << right.at (i) << " ";

   cout << endl;
}

  // sort the left and right, ascending sequence
  uint32_t i = 0;
  uint32_t j = 0;
  uint32_t k = 0;
  for ( k = p; k <= r; k++ )
    {
      // select the smallest one from left and right, and put it to m_seq
      if ( left.at (i) <= right.at (j) )
        {
          m_seq.at (k) = left.at (i);
          i++;
          if ( i >= left.size () )
            {
              k++;
              break;
            }
        }
      else
        {
          m_seq.at (k) = right.at (j);
          j++;
          if ( j >= right.size () )
            {
              k++;
              break;
            }
        }
    }

  // copy the reat data into m_seq
  // NOTE: we only need to copy the left one because the rest of right nodes are already there
  if  ( j >= right.size () )
    {
      // put the rest left into m_seq
      for (; i < left.size (); i++,k++)
        m_seq.at (k) = left.at (i);
    }

  //Print ();
}

int main (int argv, char *argc[])
{
  Sort sort;
  
  sort.Print ();
  cout << "MergeSort: ";
  sort.MergeSort ();
  sort.Print ();
  return 0;
}
