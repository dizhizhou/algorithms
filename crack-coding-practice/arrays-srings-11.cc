/*
  Skills: bit operations use ()
          bit vector
*/

#include<string>
#include<iostream>

using namespace std;

bool UniqueStr (const string &str)
{
  // special cases
  if (str.size () <= 1)
    return true;

  if (str.size () > 256 ) // assume it is ASCII string
    return false;

  // array[key] count method
/*
  int array[256] = {0};
  for (int i = 0; i < str.size (); i++)
    {
      array[str.at (i)]++;
      if (array[str.at (i)] > 1)
        return false;
    }
*/

  // hash table method
  // map<int, int> mapStr; // str.at (i) --- count

  // bit vector
  //  NOTE 1: this methods only can be used when strings are all in a - z
  int checker = 0; 
  cout << "size " << str.size () << endl;
  for (int i = 0; i < str.size (); i++)
    {
      int offset = str.at (i) - 'a';
      // NOTE 2: the bit operation must use (), otherwise, the sequence will be disordered
      if ( ( checker & ( 1 << offset ) ) > 0 )
          return false;

      checker = checker | (1 << offset);
    } 

  return true;
    

}


int main (int argc, char *argv[])
{
  string str1 = "abcdefb";
  string str2 = "abcdefg";

  cout << "unique charactors str: " << endl;
  cout << str1 << " " << UniqueStr (str1) << endl;
  cout << str2 << " " << UniqueStr (str2) << endl;

  return 0;
}
