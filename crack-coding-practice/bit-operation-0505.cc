
#include<iostream>
#include<stdint.h>

using namespace std;

uint32_t GetConvertBitNum (const int &i, const int &j)
{
  // the number of 1 bit in t is the number of bit needed to be converted
  int t = i ^ j;
  
  uint32_t num = 0;

  // count the number of 1 bit in t
  do {
    if ( 1 & t )
      {
        num++;
      }

    t = t >> 1;

  } while (t);

  return num;
}

int main (int argc, char *argv[])
{
  int i = 31;
  int j = 14;  

  cout << "the number of bit convert is " << GetConvertBitNum (i, j) << endl;

  return 0;
}
