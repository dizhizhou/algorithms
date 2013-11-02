/*
  NOTE: stack.size () is uint, so that we cannot transfer stack.size () to n
*/

#include <iostream>
#include <stack>

using namespace std;

int count = 0;

void MoveTop (stack<int> &src, stack<int> &dst)
{
  dst.push ( src.top () );
  src.pop ();
  count++;
}

void Hanoi (int n, stack<int> &src, stack<int> &dst, stack<int> &buffer)
{
  if (n <= 0) 
    return;

  // move top n-1 node from src to buffer with the help of dst
  Hanoi (n-1,src, buffer, dst);

  // move the top node from src to dst
  MoveTop (src, dst);

  // move the top n-1 node from buffer to dst with the help of src
  Hanoi (n-1,buffer, dst, src);
}

int main (int argc, char *argv[])
{

  stack<int> s1,s2,s3;

  int n = 8;
  for (int i = n; i > 0; i--)
    s1.push (i);

  Hanoi (n,s1,s3,s2);


  while (s3.size())
    {
      cout << s3.top() << " ";
      s3.pop ();
    }
  cout << endl;

  cout << "total " << count << " steps" << endl;
  return 0;
}
