/*Name: Hash table
 *  Skills: 
            typename list<Node>::iterator it;  // because 'it' depends on the template parameter 'Node', 'it' is a dependent name which cannot be looked-up immediately
            In Delete, user list<Node>& ls = ... // use &

 *  version 1.0:
            hash table: array (vector)
            hash function: division, multiplication, djb2, sdbm, lose base
            collision: chaining (list)

     performance: 
       insert: worst case: O (N)   // all nodes has the same index so that 
                                      you need to search all the N node in the list to insert          
               best case: O (1) // empty index
       delete: worst case: O (N), best case: O (1)
       search: worst case: O (N), best case: O (1)


    version 2.0
            hash table: self-balance binary search tree
            hash function: division 
            collision: self-balance binary search tree

     performance:
           insert, delete and search: O(logN)
 */

#include <iostream>
#include <vector>
#include <list>
#include <cstdint> // c++ 11 support:  g++ -std=c++11 -o hash-table hash-table.cc  // must update gcc/g++ to 4.8 version
//#include <stdint.h>
#include <string>
#include <cmath>

using namespace std;

// T: mapped data type
// the type of the Key is uint32_t
template<typename T>
class HashTable 
{
public:

  // store the (key, data)
  class Node
    {
      public:
        Node ()
          {
            key = 0;
          }
        virtual ~Node ()
          {
          }

      public:
        uint32_t key;
        T data;
    };

  HashTable (uint32_t size)
      : m_size (size) 
    {
      m_htable.resize (m_size, list<Node>(0) ); // or list<Node>(), create m_size items in vector, each vector has 0 node in list
    }

  virtual ~HashTable ()
    {
    }

  /*APIs*/
  bool Insert (uint32_t key, T data);
  bool Delete (uint32_t key);
  T Search (uint32_t key);

  void Print ();

  // hash function
  uint32_t HashDivision (uint32_t key); // map Key to the index of vector
  uint32_t HashMultiplication (uint32_t key);
  uint64_t HashDjb2 (string &str);
  uint64_t HashSdbm (string &str);
  uint64_t HashLoselose (string &str);

private:
  uint32_t m_size;           // the maximum length of hash table
  vector<list<Node> > m_htable; // hash table
}; 

template<typename T>
uint32_t HashTable<T>::HashDivision (uint32_t key)
{
  return key % m_size;// division
}

template<typename T>
uint32_t HashTable<T>::HashMultiplication (uint32_t key)
{
  uint32_t hash = 0;
  uint32_t m= 8;
  float a = 0.618;

  hash = floor (m * (key*a - floor (key*a) ) );

  return hash;
}


template<typename T>
uint64_t HashTable<T>::HashDjb2 (string &str)
{
  uint64_t hash = 5381;
  int c;
  uint32_t i = 0;

  while ( i < str.size ())
    {
      c = static_cast<int>(str.at (i));
      hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
      i++;
    }

  return hash;
}

template<typename T>
uint64_t HashTable<T>::HashSdbm (string &str)
{
  uint64_t hash = 0;
  int c;
  uint32_t i = 0;

  while ( i < str.size ())
    {
      c = static_cast<int>(str.at (i));
      hash = c + (hash << 6) + (hash << 16) - hash;
      i++;
    }

  return hash;
}

template<typename T>
uint64_t HashTable<T>::HashLoselose (string &str)
{
  uint64_t hash = 0;
  int c;
  uint32_t i = 0;

  while ( i < str.size ())
    {
      c = static_cast<int>(str.at (i));
      hash += c;
      i++;
    }

  return hash;
}

template<typename T>
bool HashTable<T>::Insert (uint32_t key, T data)
{
  bool rt = false;

  Node node;
  node.key = key;
  node.data = data;

  uint32_t index = HashDivision (key);

  // find the index-th item in vector
  list<Node> ls = m_htable[index];

  if (ls.size () == 0)
    {
      // new item in vector
      ls.push_back (node);
      m_htable[index] = ls;
      rt = true;
    }
  else
    {
      // collision in vector
      
      // find node in the list of m_htable[index]
      typename list<Node>::iterator it;
      for (it = ls.begin (); it != ls.end (); it++)
        {
          if (it->key == key)
            {
              // update the existing node
              it->data = data;
              rt = true;
              break;
            }
        }

     if (rt == false)
       {
         // new item in list (collision in vector)
         m_htable[index].push_back (node);
         rt = true;
       }
    }

  return rt;
}

template<typename T>
void HashTable<T>::Print ()
{
  cout << "Print: " << endl;
  for (uint32_t i = 0; i < m_htable.size (); i++)
    {
      list<Node> ls = m_htable[i];

      if (ls.size () == 0)
        {
          cout << endl;
          continue;
        }

      typename list<Node>::iterator it;
      for (it = ls.begin (); it != ls.end (); it++)
        {
          cout << "(" << it->key << ", " << it->data << ") ";
        }

      cout << endl;
    }
}

template<typename T>
T HashTable<T>::Search (uint32_t key)
{
  bool found = false;  

  uint32_t index = HashDivision (key);

  // find the index-th item in vector
  list<Node> ls = m_htable[index];

  if (ls.size () == 0)
    {
      // no result
      found = false;
    }
  else
    {
      typename list<Node>::iterator it;
      for (it = ls.begin (); it != ls.end (); it++)
        {
          if (it->key == key)
            {
              return it->data;
            }
        }
    }

  if (!found)
    {
      // Do not search, create an empty an return it;
      Insert (key, "");
      return Search (key);
    }
}

template<typename T>
bool HashTable<T>::Delete (uint32_t key)
{
  uint32_t index = HashDivision (key);

  // find the index-th item in vector
  list<Node>& ls = m_htable[index]; // note: we must use &, otherwise, we cannot erase node in m_htable

  if (ls.size () == 0)
    {
      // no result
      cout << " cannot find the key number " << key << endl;
      return false;
    }
  else
    {
      typename list<Node>::iterator it;
      for (it = ls.begin (); it != ls.end (); it++)
        {
          if (it->key == key)
            {
              ls.erase(it);
              return true;
            }
        }

    }

}



int main (int argc, char *argv[])
{
  HashTable<string> table(5);
 
  cout << "Insert: " << endl; 
  table.Insert (0, "zero");
  table.Insert (1, "one");
  table.Insert (2, "second");
  table.Insert (3, "three");
  table.Insert (4, "four");
  table.Insert (5, "five");
  table.Insert (6, "six");
  table.Insert (7, "seven");
  table.Insert (8, "eight");
  table.Insert (9, "nigh");
  table.Insert (5, "five");

  table.Print ();

  uint32_t key = 5;
  cout << " search: " << key << " ";
  cout << table.Search (key)  << endl;  
  cout << " search: " << key + 8 << " ";
  cout << table.Search (key + 8)  << endl;  

  table.Delete (key);
  table.Print ();
  cout << " search: " << key << " ";
  cout << table.Search (key)  << endl;  

  string str("two");
  cout << " djb2 " << table.HashDjb2 (str) << endl;
  cout << " sdbm " << table.HashSdbm (str) << endl;
  cout << " lose " << table.HashLoselose (str) << endl;
  for (uint32_t i = 0; i < 10; i++)
    cout << " Multiplication " << " key " << i << " hash " << table.HashMultiplication (i) << endl;

  return 0;
}
