/***********************************************************************
 * Module:
 *    Week 02, Stack
 *    Brother Helfrich, CS 235
 * Author:
 *    James Call
 * Summary:
 *    This program will implement the testInfixToPostfix()
 *    and testInfixToAssembly() functions
 ************************************************************************/

#include <iostream>    // for ISTREAM and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stack.h"     // for STACK
using namespace std;

/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Convert infix equation "5 + 2" into postifx "5 2 +"
 *****************************************************/
string convertInfixToPostfix(const string & infix)
{
   string postfix;
   int parenthesis = 0;
   Stack <char> mathSymbols;
   postfix += ' ';
   for (int i = 0; i < infix.length(); ++i)
   {
      try
      {
         // use switch to move through intfix
         switch (infix[i])
         {
            // if a math symbol send to stack
            // Handle the parenthesis
            case ')':
               while (mathSymbols.top() != '(')
               {
                  postfix += ' ';
                  postfix += mathSymbols.top();
                  mathSymbols.pop();
               }
               mathSymbols.pop();
               parenthesis--;
               break;
            case '(':
               parenthesis++;
               mathSymbols.push(infix[i]);
               break;


            // handle powers
            case '^':   
               postfix += ' ';
               mathSymbols.push(infix[i]);
               break;

            // handle multiplication and division
            case '/':
            case '*':
               postfix += ' ';
               if (parenthesis != 0)
                  mathSymbols.push(infix[i]);
               else
               {     if (!mathSymbols.empty())
                     {
                        while(mathSymbols.top() == '^')
                        {
                           postfix += mathSymbols.top();
                           mathSymbols.pop();     
                        }
                     }
                  mathSymbols.push(infix[i]);
               }
               break;

            // handle addition and subtraction
            case '-':
            case '+':
               postfix += " ";
               if (parenthesis != 0)
                  mathSymbols.push(infix[i]);
               else
               {
                  while(!mathSymbols.empty())
                  {
                     postfix += mathSymbols.top();
                     mathSymbols.pop();
                     postfix += ' ';
                  }
                  mathSymbols.push(infix[i]);
               }
               break;

            // handle spaces
            case ' ':
               break;

            // handle everything else
            default:
               postfix += infix[i];
         }
      }
      // catch any errors
      catch (const char * sError)
      {  
         cout << sError << endl;
      }     
   }

   // output the remaining math symbols
   while (!mathSymbols.empty())
   {
      postfix += ' ';
      postfix += mathSymbols.top();
      mathSymbols.pop();
   }

   return postfix;
}

/*****************************************************
 * TEST INFIX TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 *****************************************************/
void testInfixToPostfix()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";
   
   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);

      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << "\tpostfix: " << postfix << endl << endl;
      }
   }
   while (input != "quit");
}

/**********************************************
 * CONVERT POSTFIX TO ASSEMBLY
 * Convert postfix "5 2 +" to assembly:
 *     LOAD 5
 *     ADD 2
 *     STORE VALUE1
 **********************************************/
string convertPostfixToAssembly(const string & postfix)
{
   string assembly;

   return assembly;
}

/*****************************************************
 * TEST INFIX TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 *****************************************************/
void testInfixToAssembly()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";

   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);
      
      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << convertPostfixToAssembly(postfix);
      }
   }
   while (input != "quit");
      
}
