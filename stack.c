/*
 * stack.c
 */

#include "stack.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


Stack init_stack()
{
   Stack sp = (Stack)malloc(sizeof(StackType));
   sp->top = NULL;
   return sp;
}

int empty(Stack S)
{
  return (S -> top == NULL);
}

void push (Stack S, int n) 
{
  // Allocate a new list element with malloc
  NodePtr np = (NodePtr) malloc(sizeof(Node));
  
  // If malloc fails end the program
  // not sure...
  if (np == NULL) {
    printf ("Couldn't allocate a new stack element\n");
    exit (1);
  }

  np -> num = n;
  np -> next = S -> top;
  S -> top = np; 
}


 int pop (Stack S)
{
  if (empty(S)) {
    printf("ERROR : Can't POP an empty stack \n");
    return 0;
  }

  int hold = S -> top -> num;
  NodePtr temp =  S -> top;
  S -> top = S -> top -> next;
  free(temp);
  return (hold);

}

void delete_all_entries (Stack S)
{
  while (!empty(S)) {
    pop(S);
  }
}

//How can I print without popping
void print_stack (Stack S)
{
    printf ("%d\n", S-> top -> num);
 
  

  
}