/***********************************************************************
 * Implementation:
 *    FIBONACCI
 * Summary:
 *    This will contain the implementation for fibonacci() as well as any
 *    other function or class implementations you may need
 * Author
 *    James Call
 **********************************************************************/

#include <iostream>
#include <iomanip>
#include "fibonacci.h"   // for fibonacci() prototype
#include "list.h"        // for LIST
using namespace std;


/************************************************
 * FIBONACCI
 * The interactive function allowing the user to
 * display Fibonacci numbers
 ***********************************************/
void fibonacci()
{	
	BigNum * fib1 =  new BigNum(1);
	BigNum * fib2 = new BigNum(1);
   BigNum * sum = new BigNum(0);

   // show the first serveral Fibonacci numbers
   int number;
   cout << "How many Fibonacci numbers would you like to see? ";
   cin  >> number;
   for (int i = 0; i < number; i++)
   {
   	if (i == 0 || i == 1)
   		cout << "\t" << *fib1 << endl;
   	else
   	{

   		sum = fib1;
        
        *sum += *fib2;
   		cout << "\t" << *sum << endl;
   		fib1 = fib2; 
   		fib2 = sum;
   	}
   }
   // your code to display the first <number> Fibonacci numbers
   // prompt for a single large Fibonacci
   cout << "Which Fibonacci number would you like to display? ";
   cin  >> number;
   fib1->reset(1);
   fib2->reset(1);
   for (int i = 0; i < number; i++)
   {
      if (i == 0 || i == 1)
         {}
      else
      {
         sum = fib1;
         *sum += *fib2;
         fib1 = fib2;
         fib2 = sum;
      }
   }

   // your code to display the <number>th Fibonacci number
   cout << "\t" << *sum << endl;

   delete fib1;
   delete fib2;
   delete sum;
   
}

/*************************************************************
* BIGNUM :: ASSIGNMENT OPERATOR
* copies the BigNum to different BigNum
**************************************************************/
const BigNum & BigNum::operator=(const BigNum & rhs)
{
	this->whole = rhs.whole;
	return *this;

}

/****************************************************
* BIGNUM :: ADDITION OPERATOR
* adds one BigNum to
*****************************************************/
const BigNum & BigNum::operator+=( BigNum & rhs)
{
   int temp;
   int carry = 0;
   int loops = 0;
  
   ListIterator <unsigned int> itL = this->whole.begin();

   if ( rhs.whole.size() > this->whole.size())
      this->whole.push_back(0);
 
   for(ListIterator <unsigned int> it = rhs.whole.begin();
   	it != rhs.whole.end(); ++it)
   {
      loops++;
      if (itL != NULL)
      {   
         temp = it.getData() + itL.getData() + carry;
         carry = 0;
      }
      else
      {
         temp = it.getData() + carry;
      }
      itL.setData(temp % 1000);
      
      if (temp > 999)
      {
         carry = temp / 1000;
      }  
      if (itL != NULL)
         itL++;
   }
   if (carry == 1)
         whole.push_back(carry);
	return *this;

}

/**************************************************
 * OSTREAM OPERATOR
 * outs the wholenumber
 *************************************************/
ostream & operator << (ostream & out, BigNum & number)
{
	
   ListIterator <unsigned int> it = number.whole.rbegin();
   out << *it;
   it--;
   while (it != number.whole.end())
   {
      out << ',' << setfill('0') << setw(3) << *it;
      it--;
   }

   return out;
}


