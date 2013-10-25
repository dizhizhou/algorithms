// Binary representation for decimal number 
// 0.101 in decimal format is 1 * 2^-1 + 0 * 2^-2 + 1 * 2^-3 = 0.625


#include<iostream>
#include<string>

using namespace std;

string GetBinaryFormat (const double &num)
{
  string error ("error");

  double n = num;

  if ( n >= 1 || n <= 0 )
    return error;

  string str (".");

  while ( n > 0 )
    {
      if (str.size () > 32)
        return error;

      double tmp = n * 2;
      if (tmp >= 1.0)
        {
          str.append("1");
          n = tmp - 1.0;
        }
      else
        {
          str.append ("0");
          n = tmp;
        }
    }

  return str;
}


int main (int argc, char *argv[])
{ 
  double num = 0.625; // 0.72 returns error in 32 max size case
  
  string str = GetBinaryFormat (num);

  cout << "The bit representation of " << num << " is " << str << endl;

  return 0;
}
