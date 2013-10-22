/*Name: bit operations*/

#include <iostream>

using namespace std;

class BitOperation
{
public:

  BitOperation ()
      : m_data (0)
    {
    }
  
  BitOperation (int d)
      : m_data (d)
    {
    }

  // method to do this:
  // 1, consider the input and output of i-th bit;
  // 2, desicde the sequence and operation in this pattern: sequence operation m_data, e.g., 0000 1000 | 0000 0101
  // 3, consider the input and output of left bit;
  // 4, desicde the sequence and operation in this pattern: sequence operation m_data, e.g., 0000 1000 | 0000 0101
  // 5, choose the intersection of above sequences and operations
  bool GetBit (const int &i); // get the i-th bit of m_data
  int SetBit (const int &i); // set the i-th bit of m_data to 1
  int ClearBit (const int &i); // clear the i-th bit of m_data ( set to 0)

private:
  int m_data;
};

bool
BitOperation::GetBit (const int &i)
{
  return ( (1 << i) & m_data  );
}

int
BitOperation::SetBit (const int &i)
{
  m_data = (1 << i) | m_data;

  return m_data;
}

int 
BitOperation::ClearBit (const int &i)
{
  m_data = (~(1 << i)) & m_data;

  return m_data;
}

int main (int argc, char *argv[])
{
  BitOperation op(5);

  int i = 1;
  cout << " the " << i << "-th bit is " << op.GetBit (i) << endl;

  cout << " set the " << i << "-th bit to 1, then we get " << op.SetBit (i) << endl;
   
  cout << " the " << i << "-th bit is " << op.GetBit (i) << endl;

  cout << " clear the " << i << "-th bit, then we get " << op.ClearBit (i) << endl;

  cout << " the " << i << "-th bit is " << op.GetBit (i) << endl;

  return 0;
}


