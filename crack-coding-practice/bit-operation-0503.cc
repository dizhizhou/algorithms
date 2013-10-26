#include <iostream>
#include <cstdint>
#include <math.h>

using namespace std;

uint32_t FindOneBitNum (const uint32_t &n)
{
  uint32_t num = 0;
  for (uint32_t i = 0; i < 32; i++)
    {
      if ( n & (1 << i))
        num++;
    }

  return num;
}

uint32_t GetSmallNum (const uint32_t &n)
{
  // find the number of 1 bit in n
  uint32_t count_n = FindOneBitNum (n);

  uint32_t num = n;
  uint32_t count_num = 0;

  do {

    if (num <= 1 )
      break;

    num--;

    count_num = FindOneBitNum (num);
    
  } while ( count_num != count_n);

  return num;
}

uint32_t GetLargeNum (const uint32_t &n)
{
  // find the number of 1 bit in n
  uint32_t count_n = FindOneBitNum (n);

  uint32_t num = n;
  uint32_t count_num = 0;

  do {

    if (num >= UINT32_MAX )
      break;

    num++;

    count_num = FindOneBitNum (num);
    
  } while ( count_num != count_n);

  return num;

}

uint32_t OptimalGetLargeNum (const uint32_t &n)
{
  uint32_t c = n;
  uint32_t c0 = 0;
  uint32_t c1 = 0;
  uint32_t p = 0;

  // find the position p, the bit of p is 0, and there is at least a 1 bit in the right of position p; ...0...1...
  // find c0: the number of 0s in the right of position p
  // find c1: the number of 1s in the right of position p
  bool found = false;
  uint32_t i = 0;
  while ( i < 32 )
    {
      // if meet a 0 bit, and if its right has 1 bit
      if ( ((c & 1) == 0) && found)
        {
          p = i;
          break;;
        }
      else if ((c & 1) == 0)
        c0++;
      else if ((c & 1) == 1)
        {
          c1++;
          found = true;
        }

      c = c >> 1;
      i++;
    }

  // set the 0 in position p to 1
  c = n; // reset c
  c = c | (1 << p);

  // set c0 0s to the right of position p and c1 - 1 1s to the rightmost of c
  

  return c;

}


int main (int argc, char* argv[])
{
  
  uint32_t n = 50;

  // brute force approach
  //cout << "Small: " << GetSmallNum (n) << endl;
  //cout << "Large: " << GetLargeNum (n) << endl;

  // more optimal approach
  uint32_t n_ = pow (2, 13) + pow (2, 12) + pow (2, 10) + pow (2, 9) + pow (2, 6) + pow (2,5) + pow (2,4) + pow (2,3) + pow (2,2);
  //uint32_t n_ = pow (2, 13) + pow (2, 12) + pow (2, 11) + pow (2, 10);

  cout <<  n_ << endl;
  cout << "Large: " << OptimalGetLargeNum (n_) << endl;


  return 0;
}
