
#include<iostream>
#include<stdint.h>
#include<math.h>

using namespace std;

uint8_t SwapOddEvenBits (const uint8_t &x)
{
  // generate mask
  uint8_t mask_odd = pow (2,7) + pow (2,5) + pow (2,3) + pow (2,1);   // 1010 1010
  uint8_t mask_even = pow (2,6) + pow (2,4) + pow (2,2) + pow (2,0);  // 0101 0101

  // retreive odd and even bit sequences
  uint8_t odd_seq = x & mask_odd;
  uint8_t even_seq = x & mask_even;
  
  // swap odd to even position
  odd_seq = odd_seq >> 1;
  // swap even to odd position
  even_seq = even_seq << 1;

  // combine
  uint8_t result = 0 | odd_seq;
  result = result | even_seq;
 
  return result;
}

int main (int argc, char* argv[])
{
  // suppose integer is 8 bit
  uint8_t x = pow (2,7) + pow (2,6) + pow (2,3) + pow (2,0);  // 1100 1001

  uint8_t x_ = SwapOddEvenBits (x);
  
  cout << " x = " << (uint16_t)x << endl;
  cout << " result = " << (uint16_t)x_ << endl;
 
  return 0;
}
