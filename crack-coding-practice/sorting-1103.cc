/*
NOTE 1: must test thoroughly
*/

#include <iostream>

using namespace std;


int BinarySearch (int array[], int begin, int end, const int &val)
{
  int low = begin;
  int high = end;
  int mid = (low + high)/2;

  while ( low <= high )
    {
      if ( array[mid] < val )
        {
          low = mid + 1;
        }
      else if ( array[mid] > val)
        {
          high = mid - 1;
        }   
      else
        return mid;

      mid = (low + high)/2;
    }

  return -1;
}


int GetIndex (int array[], int size, const int &val)
{
  // special cases
  if (size == 0)
    return -1;

  if (array[0] < array[size-1])
    return BinarySearch (array, 0, size - 1, val);

  // rotate cases
  int low = 0;
  int high = size - 1;
  int mid = (low + high)/2;
 
  do {
    if (val == array[low])
      return low;
    else if (val == array[mid])
      return mid;
    else if (val == array[high])
      return high;

    if (array[mid] < array[high])
      {
        if (val > array[mid] && val < array[high])
           return BinarySearch (array, mid+1, high, val);
        else
          {
            high = mid - 1;
            mid = (low + mid)/2;
            continue;
          }
      }
    else if (array[mid] > array[low])
      {
        if (val < array[mid] && val > array[low])
            return BinarySearch (array, low, mid-1, val);
        else
          {
            low = mid + 1;
            mid = (mid + high)/2;
            continue;
          }
      }
  
  } while (low <= high);  
 
  return -1;
}


int main (int argc, char* argv[])
{
  int array[] = {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 9, 10};
  int array1[] = {16, 19, 20, 25, 1, 3, 4, 5, 7, 9, 10, 15};
  int array2[] = {19, 20, 25, 1, 3, 4, 5, 7, 9, 10, 15,16};
  int array3[] = {20, 25, 1, 3, 4, 5, 7, 9, 10, 15,16,19};
  int array4[] = {25, 1, 3, 4, 5, 7, 9, 10, 15,16,19,20};
  int array5[] = {1, 3, 4, 5, 7, 9, 10, 15,16,19,20,25};
   
  // test cases
  for (int i = 0; i < 12; i++)
    {
      int value = array[i];
      cout << "value = " << value << endl;
      cout << " " << GetIndex (array, sizeof (array)/sizeof (int), value) << " ";
      cout << " " << GetIndex (array1, sizeof (array)/sizeof (int), value) << " ";
      cout << " " << GetIndex (array2, sizeof (array)/sizeof (int), value) << " ";
      cout << " " << GetIndex (array3, sizeof (array)/sizeof (int), value) << " ";
      cout << " " << GetIndex (array4, sizeof (array)/sizeof (int), value) << " ";
      cout << " " << GetIndex (array5, sizeof (array)/sizeof (int), value) << endl;
    }

  return 0;
}
