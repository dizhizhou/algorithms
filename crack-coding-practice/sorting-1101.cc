#include <iostream>
#include <vector>

using namespace std;


/*NOTE 1: must pass the size of array to function 
  because the main function only pass the size of the array head to the method, but not whole array. 
  the sizse of int a[10] = sizeof (a) / sizeof (int)

  NOTE 2: modify a[] in Merge, a[] in main is also modified. Because main pass the head pointer to Merge
*/
void Merge (int a[], int size_a, int b[], int size_b)
{
  // b[] is empty
  if (size_b == 0)
    {
      return;
    }

  vector<int> temp;
  int a_tail = 0; // the position of the last element > 0 in a[]
  bool found = false;
  for (int i = 0; i < size_a; i++)
    {
      if (a[i] == 0 && !found)
        {
          a_tail = i - 1;
          found = true;
        }
      temp.push_back (a[i]);
    }


  // all elements in b[] is bigger than a[], merge b[] after a[]
  if (a[a_tail] <= b[0])
    {
      int i = a_tail + 1;
      int j = 0;
      while ( j < size_b )
        {
          a[i] = b[j];
          j++;
          i++;
        }
    }

   // all elements in b[] is smaller than a[], merge b[] before a[]
   if (b[size_b-1] <= a[0])
     {
       // copy b[] 
       int i = 0;
       int j = 0;
       while ( j < size_b )
         {
           a[i] = b[j];
           j++;
           i++;
         }

       // copy a[] after b[]
       int k = 0;
       while ( k <= a_tail )
         {
           a[i] = temp[k];
           i++;
           k++;
         }
     }

  // merge a[] and b[], similar to merge sort
  int i = 0;
  int j = 0;
  int k = 0;
  while ( j < size_b && i <= a_tail)
    {
      if (temp[i] <= b[j])
         {
           a[k] = temp[i];
           i++;
         }
      else if (temp[i] > b[j])
         {
           a[k] = b[j];
           j++;
         }
      k++;
    }

  if ( i > a_tail )
    {
      for (;j < size_b; j++,k++)
        a[k] = b[j];
    }
  else if (j >= size_b)
    {
      for (; i <= a_tail; i++,k++)
        a[k] = temp[i];
    }
   
}


int main (int argc, char *argv[])
{
  // suppose all inused elements are bigger than zero, unused elements are zero
  // suppose all elements in b[] are bigger than zero 
  int a[10] = {2,4,6,8};
  int b[5] = {1,3,5,7,10};

  for (int i = 0; i < 10; i++)
    cout << a[i] << " ";
  cout << endl;
  for (int i = 0; i < 4; i++)
    cout << b[i] << " ";
  cout << endl;

  // merge from the left
  Merge(a, sizeof(a)/sizeof(int), b, sizeof(b)/sizeof(int));
  // merge from the right (optimal)
  //RMerge(a, sizeof(a)/sizeof(int), b, sizeof(b)/sizeof(int));
 
  for (int i = 0; i < 10; i++)
    cout << a[i] << " ";
  cout << endl;

  return 0;
}
