// Fig. 20.14: Fig20_14.cpp
// Template Stack class test program.
#include <iostream>
#include "Stack.h" // Stack class definition
using namespace std;

int main()
{
   Stack<int> intStack; // create Stack of ints

   cout << "processing an integer Stack" << endl;

   // push integers onto intStack
   for (int i = 0; i < 3; i++)
   {
      intStack.push(i);
      intStack.printStack();
   } // end for

   int popInteger; // store int popped from stack

   // pop integers from intStack
   while (!intStack.isStackEmpty())
   {
      intStack.pop(popInteger);
      cout << popInteger << " popped from stack" << endl;
      intStack.printStack();
   } // end while

   Stack<double> doubleStack; // create Stack of doubles
   double value = 1.1;

   cout << "processing a double Stack" << endl;

   // push floating-point values onto doubleStack
   for (int j = 0; j < 3; j++)
   {
      doubleStack.push(value);
      doubleStack.printStack();
      value += 1.1;
   } // end for

   double popDouble; // store double popped from stack

   // pop floating-point values from doubleStack
   while (!doubleStack.isStackEmpty())
   {
      doubleStack.pop(popDouble);
      cout << popDouble << " popped from stack" << endl;
      doubleStack.printStack();
   } // end while
} // end main

