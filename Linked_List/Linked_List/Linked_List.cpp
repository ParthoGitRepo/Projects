// Linked_List.cpp : Defines the entry point for the console application.
//

#include "stdio.h"

//Single Linked List Node
class Node
{
   friend class Single_Linked_List;
   public:
      Node();
      ~Node();
      virtual void display() = 0;
      virtual bool compare(Node* p_node_p) = 0;
      virtual void copy_data(Node* p_node_p) = 0;
   private:
      Node* d_next_p;
      Node* d_child_p;
};
Node::Node():d_next_p(NULL),d_child_p(NULL)
{
}
Node::~Node()
{
}

template <typename T>
class Node_T:public Node
{
   public:
      Node_T(const T& p_val_r);
      ~Node_T();
      void display();
      bool compare(Node* p_node_p);
      void copy_data(Node* p_node_p);
      Node_T<T>& operator=(const Node_T<T>& p_rhs_r);
      bool operator==(const Node_T<T>& p_rhs_r);
   private:
      T d_data;
};
template <typename T>
Node_T<T>::Node_T(const T& p_val_r):
   Node(),
   d_data(p_val_r)
{
}
template <typename T>
Node_T<T>::~Node_T()
{
}
template <typename T>
void Node_T<T>::display()
{
   printf("%d",d_data);
}
template <typename T>
bool Node_T<T>::compare(Node *p_node_p)
{
   return d_data == (reinterpret_cast<Node_T<T>*>(p_node_p))->d_data;
}
template<typename T>
void Node_T<T>::copy_data(Node* p_node_p)
{
   d_data = (reinterpret_cast<Node_T<T>*>(p_node_p))->d_data;
}
template <typename T>
Node_T<T>& Node_T<T>::operator =(const Node_T<T> &p_rhs_r)
{
   if(this != &p_rhs_r)
   {
      d_data = p_rhs_r.d_data;
   }
}
template <typename T>
bool Node_T<T>::operator ==(const Node_T<T> &p_rhs_r)
{
   d_data == p_rhs_r.d_data;
}
//Single Linked List
class Single_Linked_List
{
   public:
      Single_Linked_List();
      ~Single_Linked_List();
      //Insert at end
      void insert(Node* p_node_p);
      //Remove the given node
      void remove(const Node& p_node_r);
      //Removes a node given a pointer
      bool remove(Node* p_node_p);
      //Reverse using pointers
      void reverse();
      //Reverse using reccursion
      void recursive_reverse(Node* p_node_p);
      //Make linked list cyclic
      void insert_loop(Node* p_node_p);
      //Removes the loop
      void remove_loop();
      //Provides mth node from last
      Node* mth_node_from_last(int p_index);
      //Print the list
      void print();
      //Gives the size of the list
      int size();
      Node* get_head() { return d_head_p; }
   private:
      Node* d_head_p;
      Node* d_end_p;
};
Single_Linked_List::Single_Linked_List():
   d_head_p(NULL),
   d_end_p(NULL)
{
}
Single_Linked_List::~Single_Linked_List()
{
}
void Single_Linked_List::insert(Node *p_node_p)
{
   Node* itor = d_head_p;
   if(NULL == itor)
   {
      d_head_p = p_node_p;
      d_end_p = p_node_p;
   }
   else
   {
      d_end_p->d_next_p = p_node_p;
      d_end_p = p_node_p;
   }
}
void Single_Linked_List::remove(const Node& p_node_r)
{
   Node* itor = d_head_p;
   if(d_head_p->compare(&(const_cast<Node&>(p_node_r))))
   {
      d_head_p = d_head_p->d_next_p;
   }
   else 
   {
      Node* itor_prev = itor;
      while(NULL != itor)
      {
         if(itor->compare(&(const_cast<Node&>(p_node_r))))
         {
            if(d_end_p->compare(&(const_cast<Node&>(p_node_r))))
            {
               itor_prev->d_next_p = NULL;
               d_end_p = itor_prev;
            }
            else
            {
               itor_prev->d_next_p = itor->d_next_p;
               delete(itor);
            }
            break;
         }
         itor_prev = itor;
         itor = itor->d_next_p;
      }
   }
}
bool Single_Linked_List::remove(Node* p_node_p)
{
   Node* itor = p_node_p;
   Node* itor_prev = NULL;
   if(NULL == itor->d_next_p)
      return false; //Cannot delete last node
   while(itor->d_next_p)
   {
      itor->copy_data(itor->d_next_p);
      itor_prev = itor;
      itor = itor->d_next_p;
   }
   itor_prev->d_next_p = NULL;
   delete(d_end_p);
   d_end_p = itor_prev;
   return true;
}
void Single_Linked_List::recursive_reverse(Node* p_node_p)
{
   if(p_node_p->d_next_p == NULL)
   {
      d_end_p = d_head_p;
      d_head_p = p_node_p;
   }
   else
   {
      recursive_reverse(p_node_p->d_next_p);
      p_node_p->d_next_p->d_next_p = p_node_p;
      p_node_p->d_next_p = NULL;//This is important step to avoid cyclic dependency
   }
}
void Single_Linked_List::reverse()
{
   Node* itor = d_head_p;
   Node* itor_prev = d_head_p;
   Node* itor_next = d_head_p;
   while(NULL != itor)
   {
      itor_next = itor->d_next_p;
      if(itor == d_head_p)
      {
         itor->d_next_p = NULL;
      }
      else
      {
         itor->d_next_p = itor_prev;
      }
      itor_prev = itor;
      itor = itor_next;
   }
   itor = d_head_p;
   d_head_p = d_end_p;
   d_end_p = itor;
}
void Single_Linked_List::insert_loop(Node* p_node_p)
{
   d_end_p->d_next_p = p_node_p;
}
void Single_Linked_List::remove_loop()
{
   Node* itor_1 = d_head_p;
   Node* itor_2 = d_head_p;
   Node* itor_prev = NULL;

   while(itor_1)
   {
      itor_1 = itor_1->d_next_p->d_next_p;
      itor_prev = itor_2;
      itor_2 = itor_2->d_next_p;
      if(itor_1 == itor_2) //Loop detected
      {
         itor_1 = d_head_p;
         while(itor_1 != itor_2)
         {
            itor_1 = itor_1->d_next_p;
            itor_prev = itor_2;
            itor_2 = itor_2->d_next_p;
         }
         itor_prev->d_next_p = NULL;
         break;
      }
   }
}
Node* Single_Linked_List::mth_node_from_last(int p_index)
{
   int len = size();
   Node *p1 = d_head_p, *p2 = d_head_p;
   if(p_index > len || 0 >= len || 0 >= p_index)
      return NULL;
   for(int i = 0; i < p_index; i++)
   {
      p1 = p1->d_next_p;
   }
   while(NULL != p1)
   {
      p1 = p1->d_next_p;
      p2 = p2->d_next_p;
   }
   return p2;
}
void Single_Linked_List::print()
{
   Node* itor = d_head_p;
   printf("LIST: ");
   while(NULL != itor)
   {
      itor->display();
      printf(" ");
      itor = itor->d_next_p;
   }
   printf("\n");
   printf("LIST Size: %d\n",size());
}
int Single_Linked_List::size()
{
   Node* itor = d_head_p;
   int size = 0;
   if(NULL != d_head_p)
   {
      while(NULL != itor){itor = itor->d_next_p; size++;}
      return size;
   }
   else
      return(0);
}

int main()
{
   printf("Single Linked List\n");
   typedef Node_T<int> Node_int;
   typedef Node_T<char> Node_char;
   typedef Node_T<float> Node_float;
   int val = 0;
   Single_Linked_List myList;
   myList.insert(new Node_int(val++));
   myList.insert(new Node_int(val++));
   myList.insert(new Node_int(val++));
   myList.insert(new Node_int(val++));
   myList.insert(new Node_int(val++));
   myList.insert(new Node_int(val++));
   myList.insert(new Node_int(val++));
   myList.insert(new Node_int(val++));
   myList.insert(new Node_char('M'));
   myList.insert(new Node_float(98.3f));
   myList.insert(new Node_float(101.2f));
   myList.print();
   myList.remove(Node_char('M'));
   myList.print();
   myList.remove(myList.mth_node_from_last(2));
   myList.print();
   myList.remove(Node_float(101.2f));
   myList.print();
   myList.reverse();
   myList.print();
   myList.recursive_reverse(myList.get_head());
   myList.print();
   myList.insert_loop(myList.mth_node_from_last(4));
   myList.remove_loop();
   myList.print();
   myList.insert_loop(myList.mth_node_from_last(1));
   myList.remove_loop();
   myList.print();
   myList.insert_loop(myList.mth_node_from_last(8));
   myList.remove_loop();
   myList.print();
   return 0;
}

