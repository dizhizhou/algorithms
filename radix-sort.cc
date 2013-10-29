// C++ LSD Radix Sort example, queue implementation
// TBD: use queue STL
 
#include <iostream>
#include <cstdlib>
#include <ctime>
 
using namespace std;
 
typedef struct slist_ { 
    int val;
    struct slist_ *next; 
} slist;
 
void Print (slist *start)
{
  slist *temp = start;
  while (temp->next != NULL)
    {
      cout << temp->val << " ";
      temp = temp->next;
    }
  cout << endl;
}


slist *radixsort(slist *L, int t) 
{
    int i, j, d, m=1;
    slist *temp, *head[10], *tail[10];
 
    // Process t digits
    for (j=1; j<=t; j++) 
    { 
        // Initialize the queues, 0 to 9
        for (i=0; i<=9; i++)
        {
            head[i] = NULL;
            tail[i] = NULL;
        }

        /*sort each digital numbers*/
 
        // Process the list L
        //  e.g., head[d] --> node 1 --> node 2 <-- tail[d]
        while ( L != NULL ) 
        {
            // Get the decimal digit with place value m
            d = static_cast<int>(L->val/m)%10;
 
            // Make temp point to the current list item
            temp = L;
 
            // Make L point to the next list item
            L = L->next;
 
            // Disconnect the current list item, making it self-contained
            temp->next = NULL;
 
            if (head[d]!= NULL)
            {   // The queue for digit d is not empty
 
                // Add the list item to the end of the queue for digit d
                tail[d]->next = temp;
 
                // Make tail[d] point to the new tail item of queue d
                tail[d] = temp;
            }
            else
            {   // The queue for digit d is empty
                head[d] = temp;  // Point to the new head
                tail[d] = temp;  // Point to the new tail
            }
        } // while
 
        /* re-build the L by insert nodes from head[] one by one
         * as such, the sequence of nodes in the same queue can be maintained
         */

        // Find the index, d, of the first non-empty queue
        d=0;
        while (head[d]==NULL)
            d++;
 
        // Point to the first item of the first non-empty queue
        L = head[d];
 
        // Point to the last item of the first non-empty queue
        temp = tail[d];
 
        // Append the items of the remaining non-empty queues
        // to the tail of list L.
        d++;
        while (d<10)
        {
            if (head[d]!=NULL)
            {
                // Append the items of non-empty queue d to list L
                temp->next = head[d];
 
                // Point to the new tail of list L
                temp = tail[d];
            }
 
            d++;
        } // while
 
        // Prepare to process the next more significant digit
        m = m*10;

        //Print (L);
    } // for
 
    return L;
}
 

int main()
{
    // Initialize the random number seed with the time
    srand( static_cast<unsigned int>(time(NULL)) );
 
    const int size = 10;
    int n[size];
    int i, max=-1, t=0;
 
    // Generate some random numbers
    slist *start=NULL,*end=NULL,*temp;

    /*
    for (i=0; i<size; i++)
    {
        n[i] = rand();
    }
    */
    n[0] = 624;
    n[1] = 852;
    n[2] = 426;
    n[3] = 987;
    n[4] = 269;
    n[5] = 146;
    n[6] = 415;
    n[7] = 301;
    n[8] = 730;
    n[9] = 78;
     

    // Find the largest value and create a linked list of the random values
    for (i=0; i<size; i++)
    {
        // Find the largest value
        if (n[i] > max)
            max = n[i];
 
        // Create a new node
        temp = new slist;
 
        // Fill the node with a random value
        temp->val = n[i];
 
        // Seal the node
        temp->next = NULL;
 
        if (start != NULL)
        {   // Append the new node to the linked list
            end->next = temp;
            end = temp;
        }
        else
        {   // Add the first node to the linked list
            start = temp;
            end = temp;
        }
    }
 
    // Find the number of decimal digits in the largest random value
    while (max>0)
    {
        t=t+1;
        max=max/10;    
    } 
 
    //Print (start);

    // Perform the radix sort
    start = radixsort(start, t);
 
    // Display the results
    cout << "after radix sort.\n";
    temp = start;
    for (i=0; i<size; i++)
    {
        cout << temp->val << "\n";
        temp = temp->next;
    }
 
    // Return a zero to the calling script, batch file, or command shell
    // to indicate successful completion.
    return 0;
} // main
