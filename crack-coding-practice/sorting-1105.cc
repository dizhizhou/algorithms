/*
  Skills: string compare: <, >, ==, != : use alphabeta order (dictionary order)
*/

#include <iostream>
#include <string>

using namespace std;


// find an non empty node within the range of [low, high]
// other wise, return -1
int GetClostNonEmptNodeIndex (string array[], int low, int high, int mid)
{
  int left = mid - 1;
  int right = mid + 1;

  while ( left >= low && right <= high)
    {
      if (array[left] == "")
        left--;
      else
        break;

      if (array[right] == "")
        right++;
      else
       break;
    }

  // NOTE: we prefer left side (this is just a random setting)
  if (array[left] != "" && left >= low)
    return left;
  
  if (array[right] != "" && right <= high)
    return right;

  return -1;

}

int GetIndex (string array[], int size, const string &val)
{
  if (size == 0 || val == "")
    return -1;

  int low = 0;
  int high = size - 1;
  int mid = (low + high) / 2;

  // NOTE: compared to the binary search, here we have an additional conditions: mid >= 0
  //       , which means that there are not non empty nodes between low and high
  //       Then, search fail
  while (low <= high && mid >= 0)
    {
      if (array[mid] == val)
        return mid;
        
      if (array[mid] == "")
        {
          mid = GetClostNonEmptNodeIndex (array, low, high, mid);
        }
      else if (array[mid] < val)
        {
          low = mid + 1;
          mid = (low + high)/2;
        }
      else if (array[mid] > val)
        {
          high = mid - 1;
          mid = (low + high)/2;
        }
    }

  return -1;
}


int main (int argc, char *argv[])
{
  string array[] = {"at", "", "", "", "ball", "", "", "car", "dad", "", ""};

  string value = "ball";
  cout << "index of " << value << " is " << GetIndex(array, sizeof(array)/sizeof(string),value) << endl;

  return 0;
}
