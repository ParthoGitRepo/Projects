#include"stdio.h"
#include"new.h"

class Allocator
{
   public:
   Allocator() { ; }
   ~Allocator() { ; }
   virtual void* allocate(int p_size)
   {
      return new char[p_size];
   }
   virtual void deallocate(void* p_address_p)
   {
      delete(p_address_p);
   }
};

template<typename Tn>
class Node
{
   public:
   Node():d_left_p(NULL),d_right_p(NULL),d_data() {;}
   Node(Tn& p_data_p):d_left_p(NULL),d_right_p(NULL),d_data(p_data_p) {;}
   void visit() { printf("%d ", d_data); }
   ~Node(){;}
   Node* d_left_p;
   Node* d_right_p;
   Tn d_data;
};

class Tree
{
   public:
   Tree() {;}
   ~Tree() {;}
};

template<typename T, typename A>
class BST : public Tree
{
   public:
   BST();
   ~BST();
   bool insert(T p_data);
   bool remove(T p_data);
   void preorder(){ rec_preorder(d_root_p); }
   void inorder(){ rec_inorder(d_root_p); }
   void postorder(){ rec_postorder(d_root_p); }
   int height(){ return rec_height(d_root_p); }
   int min_depth(){ return rec_min_depth(d_root_p); }
   int max_depth(){ return rec_max_depth(d_root_p); }
   bool is_balanced();
   void balance(){ rec_balance(&d_root_p); }
   T& determine_LCA(){ return rec_determine_LCA(d_root_p); }

   private:
   void rec_preorder(Node<T> *p_node_p);
   void rec_inorder(Node<T> *p_node_p);
   void rec_postorder(Node<T> *p_node_p);
   int rec_height(Node<T> *p_node_p);
   int rec_min_depth(Node<T> *p_node_p);
   int rec_max_depth(Node<T> *p_node_p);
   int rec_balance(Node<T> **p_node_pp);
   T& rec_determine_LCA(Node<T> *p_node_p);
   bool rotate_left(Node<T> **p_node_pp);
   bool rotate_right(Node<T> **p_node_pp);

   Node<T> *d_root_p;
   int d_no_of_nodes;
   A d_allocator;
};
template<typename T, typename A>
BST<T,A>::BST():
   Tree(),
   d_root_p(NULL),
   d_no_of_nodes(0),
   d_allocator()
{
}
template<typename T, typename A>
BST<T,A>::~BST()
{
}
template<typename T, typename A>
bool BST<T,A>::insert(T p_data)
{
   bool status_b = false;
   Node<T> **itor = &d_root_p;

   if(NULL == d_root_p)
   {
      d_root_p = new(d_allocator.allocate(sizeof(Node<T>)))Node<T>(p_data);
      d_no_of_nodes++;
      status_b = true;
   }
   else
   {
      while(*itor)
      {
         if(p_data > (*itor)->d_data)
         {
            itor = &((*itor)->d_right_p);
         }
         else if (p_data < (*itor)->d_data)
         {
            itor = &((*itor)->d_left_p);
         }
         else
            return status_b; //Data allready present
      }
      *itor = new(d_allocator.allocate(sizeof(Node<T>)))Node<T>(p_data);
      d_no_of_nodes++;
      status_b = true;
   }
   return status_b;
}
template<typename T, typename A>
bool BST<T,A>::remove(T p_data)
{
   bool status_b = false;
   bool found_b = false;
   Node<T>** itor = &d_root_p;
   while(NULL != (*itor))
   {
      if((*itor)->d_data == p_data)
      {
         found_b = true;
         break;
      }
      if((*itor)->d_data < p_data)
         itor = &((*itor)->d_right_p);
      else if((*itor)->d_data > p_data)
         itor = &((*itor)->d_left_p);
   }
   if(found_b)
   {
      Node<T> *node_p = (*itor);
      Node<T> **node_pp = itor;
      if((NULL == (*itor)->d_left_p) && (NULL == (*itor)->d_right_p))//Node to be deleted is the leaf node
      {
         (*itor) = NULL;
         d_allocator.deallocate(node_p);
      }
      else if((NULL == (*itor)->d_left_p) && (NULL != (*itor)->d_right_p))//Node with one Right child only
      {
         (*itor) = (*itor)->d_right_p;
         d_allocator.deallocate(node_p);
      }
      else if((NULL != (*itor)->d_left_p) && (NULL == (*itor)->d_right_p))//Node with one Left child only
      {
         (*itor) = (*itor)->d_left_p;
         d_allocator.deallocate(node_p);
      }
      else//Node with both child
      {
         itor = &(*itor)->d_left_p;
         while(NULL != (*itor)->d_right_p)
            itor = &((*itor)->d_right_p);
         Node<T>* node_to_swap_p = (*itor);
         (*itor) = (*itor)->d_right_p;
         node_to_swap_p->d_left_p = node_p->d_left_p;
         node_to_swap_p->d_right_p = node_p->d_right_p;
         d_allocator.deallocate(node_p);
         (*node_pp) = node_to_swap_p;
      }
      status_b = true;
      d_no_of_nodes--;
   }
   
   return status_b;
}
template<typename T, typename A>
void BST<T,A>::rec_preorder(Node<T> *p_node_p) //N-L-R
{
   if(NULL == p_node_p)
      return;
   if(p_node_p == d_root_p) printf("\nTREE: Preorder - ");
   p_node_p->visit();
   rec_preorder(p_node_p->d_left_p);
   rec_preorder(p_node_p->d_right_p);
   return;
}
template<typename T, typename A>
void BST<T,A>::rec_inorder(Node<T> *p_node_p) //L-N-R
{
   if(NULL == p_node_p)
      return;
   if(p_node_p == d_root_p) printf("\nTREE: Inorder - ");
   rec_inorder(p_node_p->d_left_p);
   p_node_p->visit();
   rec_inorder(p_node_p->d_right_p);
   return;
}
template<typename T, typename A>
void BST<T,A>::rec_postorder(Node<T> *p_node_p) //L-R-N
{
   if(NULL == p_node_p)
      return;
   if(p_node_p == d_root_p) printf("\nTREE: Postorder - ");
   rec_postorder(p_node_p->d_left_p);
   rec_postorder(p_node_p->d_right_p);
   p_node_p->visit();
   return;
}
template<typename T, typename A>
int BST<T,A>::rec_height(Node<T> *p_node_p)
{
   int ht_L = 0;
   int ht_R = 0;
   if(NULL == p_node_p)
      return -1;
   if(p_node_p == d_root_p) printf("\nTREE: Height - ");

   ht_L = 1 + rec_height(p_node_p->d_left_p);
   ht_R = 1 + rec_height(p_node_p->d_right_p);
   p_node_p->visit();
   printf("(%d|%d), ", ht_L, ht_R);

   return (ht_L >= ht_R ? ht_L : ht_R);
}
template<typename T, typename A>
int BST<T,A>::rec_max_depth(Node<T> *p_node_p)
{
   if(NULL == p_node_p)
      return 0;

   int dp_L,dp_R;
   dp_L = rec_max_depth(p_node_p->d_left_p);
   dp_R = rec_max_depth(p_node_p->d_right_p);
   return ((dp_L >= dp_R) ? (dp_L + 1) : (dp_R + 1));
}
template<typename T, typename A>
int BST<T,A>::rec_min_depth(Node<T> *p_node_p)
{
   if(NULL == p_node_p)
      return 0;

   int dp_L,dp_R;
   dp_L = rec_min_depth(p_node_p->d_left_p);
   dp_R = rec_min_depth(p_node_p->d_right_p);
   return ((dp_L <= dp_R) ? (dp_L + 1) : (dp_R + 1));
}
template<typename T, typename A>
bool BST<T,A>::is_balanced()
{
   int min, max;
   min = min_depth();
   max = max_depth();
   printf("\nTREE: Min Depth - %d, Max Depth - %d ",min,max);
   if((max-min) > 1)
   {
      printf("UNBALANCED\n");
      return false;
   }
   else
   {
      printf("BALANCED\n");
      return true;
   }
}
template<typename T, typename A>
int BST<T,A>::rec_balance(Node<T> **p_node_pp)
{
   int ht_L = 0;
   int ht_R = 0;
   if(NULL == (*p_node_pp))
      return 0;
   ht_L = 1 + rec_balance(&(*p_node_pp)->d_left_p);
   ht_R = 1 + rec_balance(&(*p_node_pp)->d_right_p);
   if(ht_L - ht_R > 1)
   {
      rotate_right(p_node_pp);
      ht_L =- 1;
      ht_R =+ 1;
   }
   if(ht_R - ht_L > 1)
   {
      rotate_left(p_node_pp);
      ht_R =- 1;
      ht_L =+ 1;
   }
   return (ht_L >= ht_R ? ht_L : ht_R);
}
template<typename T, typename A>
T& BST<T,A>::rec_determine_LCA(Node<T> *p_node_p)     
{
   T data;
   return data;
}
template<typename T, typename A>
bool BST<T,A>::rotate_left(Node<T>** p_node_pp)
{
   bool status_b = false;
   if(NULL != (*p_node_pp)->d_right_p)
   {
      Node<T>* old_root = (*p_node_pp);
      (*p_node_pp) = old_root->d_right_p;
      old_root->d_right_p = NULL;
      Node<T>* new_root = (*p_node_pp);
      if(NULL != new_root->d_left_p)
         old_root->d_right_p = new_root->d_left_p;
      new_root->d_left_p = old_root;
      status_b = true;
   }
   return status_b;
}
template<typename T, typename A>
bool BST<T,A>::rotate_right(Node<T>** p_node_pp)
{
   bool status_b = false;
   if(NULL != (*p_node_pp)->d_left_p)
   {
      Node<T> *old_root = *p_node_pp;
      *p_node_pp = old_root->d_left_p;
      old_root->d_left_p = NULL;
      Node<T> *new_root = *p_node_pp;
      if(NULL != new_root->d_right_p)
         old_root->d_left_p = new_root->d_right_p;
      new_root->d_right_p = old_root;
      status_b = true;
   }
   return status_b;
}

int main()
{
   printf("Binary Search Tree \n");
   BST<int,Allocator> myTree;
   myTree.insert(7);
   myTree.insert(5);
   myTree.insert(8);
   myTree.insert(6);
   myTree.insert(9);
   myTree.insert(4);
   myTree.insert(10);
   myTree.insert(1);
   myTree.insert(3);
   myTree.insert(2);
   myTree.preorder();
   myTree.inorder();
   myTree.postorder();
   myTree.height();
   myTree.is_balanced();
   myTree.remove(11);
   myTree.inorder();
   myTree.remove(10);
   myTree.inorder();
   myTree.remove(3);
   myTree.inorder();
   myTree.remove(7);
   myTree.inorder();
   myTree.remove(1);
   myTree.inorder();
   myTree.remove(2);
   myTree.inorder();
   myTree.remove(5);
   myTree.inorder();
   myTree.remove(8);
   myTree.inorder();
   myTree.remove(9);
   myTree.inorder();
   myTree.remove(6);
   myTree.inorder();
   myTree.remove(4);
   myTree.inorder();
   myTree.insert(5);
   myTree.insert(3);
   myTree.insert(7);
   myTree.insert(2);
   myTree.insert(4);
   myTree.insert(6);
   myTree.insert(8);
   myTree.insert(1);
   myTree.insert(9);
   myTree.inorder();
   myTree.is_balanced();

   //myTree.balance();
   //myTree.height();
   return 0;
}

