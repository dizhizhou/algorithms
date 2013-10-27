/*
  Skills: pass by reference for vector
*/

#include<iostream>
#include<stdint.h>
#include<vector>
#include<string>
#include<algorithm>
#include<map>

using namespace std;

class Anagram
{
public:
  Anagram (vector<string> &seq)
      : m_seq (seq)
    {
    }

  Anagram (string a[], uint32_t size)
    {
      for (uint32_t i = 0; i < size; i++)
        m_seq.push_back (a[i]);
    }

  virtual ~Anagram ()
    {
    }

  void Print ();
  void Sort ();

private:
  vector<string> m_seq; 
};

void Anagram::Print ()
{
  for (uint32_t i = 0; i < m_seq.size (); i++)
    cout << m_seq.at (i) << " ";
  cout << endl;
}

void Anagram::Sort ()
{
  // create a hash table 
  map<string, vector<string> > mapStr;    

  // sort and insert string into map
  for (uint32_t i = 0; i < m_seq.size (); i++)
    {
      // sort
      string key = m_seq.at (i);
      sort (key.begin (), key.end ());

      // insert into hash table
      map<string, vector<string> >::iterator it = mapStr.end ();
      it = mapStr.find (key);
      if (it == mapStr.end ())
        {
          vector<string> vec;
          vec.push_back (m_seq.at (i));
          mapStr.insert (pair<string, vector<string> >(key,vec));
        }
      else
        {
          (*it).second.push_back (m_seq.at (i));
        }
    }

  // retreive strings from map
  map<string, vector<string> >::iterator it;
  uint32_t i = 0;
  for (it = mapStr.begin (); it != mapStr.end (); it++)
    {
      for (uint32_t j = 0; j < (*it).second.size (); j++)
        {
          m_seq.at (i) = ((*it).second.at (j));
          i++;
        }     
    }

}

int main (int argc, char *argv[])
{
  string a[] = {"abc", "cd", "efth", "dc", "cba", "feht", "cd"};

  Anagram anagram(a, 7);

  anagram.Print ();
  anagram.Sort ();
  anagram.Print ();

  return 0;
}
