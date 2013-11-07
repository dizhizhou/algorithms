/*
  input: direct graph, node 1, node 2
  output: true if there is a route between node 1 and 2; 
          false if there is not a route between node 1 and node 2


*/


bool IsRoute (Graph graph, Node* src, Node* dst )
{
  // special case
  if (src == dst)
    return true;

  // Breadth first search
  // suppose Graph use adjacent linked list to store a graph
  // suppose Graph's nodes->visited = false;

  queue<Node> q;

  src->visited = true;
  q.push (src);

  while (q.size () != 0)
    {
      Node* cur = q.front ();
      q.pop ();
      Node* node = graph.GetAdjacentNode (cur); // get the first adjacent nodes

      while ( node != NULL && node->visited == false)
        {
          if (node == dst)
            return true;
          else
            {
              node->visit = true;
              q.push (node);
            }

          node = node->next; // get next adjacent nodes
        }
    }


  cur = next_adjacent_nodes;

  return false;
}
