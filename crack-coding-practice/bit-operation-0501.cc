#include <iostream>
#include <math.h>
#include <stdint.h>

using namespace std;

void AddMtoN (uint32_t &n, const uint32_t &m, const uint32_t &i, const uint32_t &j )
{
  uint32_t M = m;  

  // mask
  uint32_t x = pow (2, (j - i + 1));
  x = x - 1; // x = 1111...1, the length of x is (j - i + 1)
  x = ~( x << i );

  // clear bit
  n = n & x;
 
  // set bit
  n = n | (M << i);

//  return n; 
}


int main (int argc, char* argv[])
{
/* exmaple 1: size of m = j - i + 1
  0010 0100, 36, n
       1 01, 5,  m
  i = 2, j = 4
  0011 0100, 52, new n
*/
  uint32_t n = 36;
  uint32_t m = 5;
  uint32_t i = 2;
  uint32_t j = 4;
  AddMtoN (n,m,i,j);
  cout << "result-1 is " << n << endl;

}
