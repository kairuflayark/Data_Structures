/***********************************************************************
 * Header:
 *    FIBONACCI
 * Summary:
 *    This will contain just the prototype for fibonacci(). You may
 *    want to put other class definitions here as well.
 *    Contains the BigNum class for use in storing the fibonacci.
 * Author
 *    James Call
 ************************************************************************/

#ifndef FIBONACCI_H
#define FIBONACCI_H

#include "list.h"        // for LIST
#include <iostream>

class BigNum
{
public:
	// default constructor
	BigNum(){ whole.insert(whole.begin(), 0); }

	// non-default constructor
	BigNum( const unsigned int nData){ whole.push_back(nData); }
	
	// copy constructor
	BigNum(const BigNum & rhs){ this->whole = rhs.whole; }

	// reset to list to a single node
	void reset(const unsigned int nData){ whole.clear(); whole.push_front(nData); }
	
	// ostream operator
	friend std::ostream & operator << (std::ostream & out, BigNum & number);
	
	// assignment operator
	const BigNum & operator=(const BigNum & rhs);

	// assignment operator
	const BigNum & operator+=(BigNum & rhs);


private:
	List<unsigned int> whole; // list for the big number 

};


// the interactive fibonacci program
void fibonacci();

#endif // FIBONACCI_H

