/*
 * stack.h
 */

/* A Stack data type is defined as a pointer to the linked
 list, defined by its "top" variable. I.e. a Stack variable 
 points to the variable which points to the first item in the linked list.
 */

typedef struct node {
  int num;
  struct node *next;
} Node, *NodePtr; //we also declare a name for node*

typedef struct {
  NodePtr top;
} StackType, *Stack; 

Stack init_stack();
int pop (Stack S);
int empty(Stack S);
void push (Stack S, int n);
void delete_all_entries (Stack S);
void print_stack (Stack S);
//int length_stack (Stack S);