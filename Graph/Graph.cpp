#include "stdio.h"

class Node
{
public:
   Node():d_weight(0)
   {
   }

   ~Node() { ; }

   void add_weight(int p_weight)
   {
      d_weight = p_weight;
   }

private:
   int d_weight;
};

template<int NO_OF_LINKS>
class Node_T : public Node
{
public:
   Node_T():Node(),d_no_of_linked_nodes(0),d_max_no_of_linked_nodes(NO_OF_LINKS)
   {
      for(int i = 0; i<d_max_no_of_linked_nodes; i++)
         d_link[i] = NULL;
   }

   ~Node_T() { ; }

   bool insert_link(Node* p_linked_node_p)
   {
      if(d_no_of_linked_nodes < d_max_no_of_linked_nodes)
      {
         d_link[d_no_of_linked_nodes++] = p_linked_node_p;
         return true;
      }
      else
         return false;
   }

private:
   int d_no_of_linked_nodes;
   int d_max_no_of_linked_nodes;
   Node* d_link[NO_OF_LINKS];
};

int main()
{
   printf("Hello World\n");

   Node_T<2> a;
   Node_T<2> b;
   Node_T<2> c;
   Node_T<2> d;
   Node_T<2> e;
   Node_T<2> f;
   Node_T<6> g;

   a.insert_link(&b);
   b.insert_link(&c);
   c.insert_link(&d);
   d.insert_link(&e);
   e.insert_link(&f);
   f.insert_link(&a);
   g.insert_link(&a);
   g.insert_link(&b);
   g.insert_link(&c);
   g.insert_link(&d);
   g.insert_link(&e);
   g.insert_link(&f);

   return 0;
}


