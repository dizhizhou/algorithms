#include <iostream>
#include <cstdint>

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


int main (int argc, char* argv[])
{
  
  uint32_t n = 10;

  cout << "Small: " << GetSmallNum (n) << endl;
  cout << "Large: " << GetLargeNum (n) << endl;

  return 0;
}
