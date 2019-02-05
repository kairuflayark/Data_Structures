   /***********************************************************************
* Header:
*    Stack
* Summary:
*    This class contains the notion of a container: a bucket to hold
*    data for the user. This is just a starting-point for more advanced
*    constainers such as the stack, set, stack, queue, deque, and map
*    which we will build later this semester.
*
*    This will contain the class definition of:
*        Stack         : A class that holds stuff
*        StackIterator : An interator through Stack
* Author
*    Br. Helfrich
************************************************************************/

#ifndef STACK_H
#define STACK_H

#include <cassert>

// forward declaration for StackIterator
template <class T>
class StackIterator;

/************************************************
 * STACK
 * A class that holds stuff
 ***********************************************/
template <class T>
class Stack
{
public:
   // default constructor : empty and kinda useless
   Stack() : numItems(0), cap(0), data(NULL) {}

   // non-default constructor : pre-allocate
   Stack(int capacity) throw (const char *);

   // copy constructor : copy it
   Stack(const Stack & rhs) throw (const char *);

   // assignment operation
   const Stack & operator=(const Stack <T> & rhs) throw (const char *);   

   // subscript operator
   T & operator[](int index) throw (const char *);

   // subscript operator
   T & operator[](int index) const throw (const char *);
   
   // destructor : free everything
   ~Stack()        { if (cap) delete [] data; }
   
   // is the container currently empty
   bool empty() const  { return numItems == 0;         }

   // remove all the items from the container
   void clear()        { numItems = 0;                 }

   // how many items are currently in the container?
   int size() const    { return numItems;              }
   
   // reallocate more room in data array
   void reallocate() throw (const char *);

   // add an item to end of container
   void push(const T & item) throw (const char *);

   // remove item from stack
   void pop() throw (const char *);

   // retrieve value of top item in stack
   T top() throw (const char *);

   // how large is the container
   int capacity(){ return cap; }


private:
   T * data;          // dynamically allocated array of T
   int numItems;      // how many items are currently in the Stack?
   int cap;           // how many items can I put on the Stack before full?
};


/*******************************************
 * STACK :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Stack <T> :: Stack(const Stack <T> & rhs) throw (const char *)
{
   assert(rhs.cap >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.cap == 0)
   {
      cap = numItems = 0;     
      data = NULL;
      delete [] data;
 
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.cap];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   // copy over the capacity and size
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
   cap = rhs.cap;
   numItems = rhs.numItems;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numItems; i++)
      data[i] = rhs.data[i];

   // the rest needs to be filled with the default value for T
   for (int i = numItems; i < cap; i++)
      data[i] = T();
}

/*******************************************
 * STACK :: ASSIGNMENT OPERATOR
 *******************************************/
template <class T>
const Stack <T> & Stack <T>::operator=(const Stack <T> & rhs) throw (const char *)
{
	if (this == &rhs)
	{
		return *this;
	}
   // check that it has enough space allocate
   else
   {   	
   	//data = NULL;    
    delete [] data;
      // attempt to allocate
      try
      {	
      data = new T[rhs.numItems];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for stack";
      }
   }
   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numItems; i++)
      data[i] = rhs.data[i];
   numItems = rhs.numItems;
   cap = rhs.numItems;
   
   return *this;
}


/**********************************************
 * STACK : NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "capacity"
 **********************************************/
template <class T>
Stack <T> :: Stack(int capacity) throw (const char *)
{
   assert(capacity >= 0);
   
   // do nothing if there is nothing to do
   if (capacity == 0)
   {
      this->cap = this->numItems = 0;
      //this->data = NULL;      
      delete [] data;
      return;
   }

   // attempt to allocate
   try
   {
    	data = new T[capacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for stack";
   }

      
   // copy over the stuff
   this->cap = capacity;
   this->numItems = 0;

   // initialize the container by calling the default constructor
   for (int i = 0; i < capacity; i++)
      data[i] = T();
}


/****************************************************
* STACK :: POP
* Remove item from container
*****************************************************/
template <class T>
void Stack <T> ::pop() throw (const char *)
{
    if (numItems != 0)
    {
    	this->numItems--;
    }
    else
    {
    	throw "ERROR: Unable to pop from an empty Stack";
   	}
}


/****************************************************
* STACK :: PUSH
* Insert an item on the top of the container
*****************************************************/
template <class T>
void Stack <T> ::push(const T &item) throw (const char *)
//void push(T & item) throw (const char *);

{
   // check that there is enough space for it to add
   	if (cap == 0 || numItems == cap  )
   	{
      	reallocate();
   		data[numItems] = item;
   	}
   else 
 	{
   	data[numItems] = item;
 	}
   numItems++;

}

/****************************************************
* STACK :: TOP
* Returns the value of the top item on a stack
*****************************************************/
template <class T>
T Stack <T> ::top() throw (const char *)
{
   if (numItems == 0)
   {
      throw "ERROR: Unable to reference the element from an empty Stack";
   }
   else
   {
      return data[numItems - 1];
   }
}


/****************************************************
* STACK :: REALLOCATE
* Returns the value of the top item on a stack
*****************************************************/
template <class T>
void Stack <T> ::reallocate() throw (const char *)
{
	T * nData;
    int nCap;
      
      //attempt to allocate
    try
    {
       	if (cap == 0)
       	{
        	nData = new T[1];
        	nCap = 1;
        }
        else
        {
        
            nCap = cap * 2;
            nData = new T[nCap];  

            // loop through old data
   			for(int i = 0; i < numItems; i++)
   			{
       			 nData[i] = data[i];
    		}
        }
    }
   	catch (std::bad_alloc)
    {
  	   	throw "ERROR: Unable to allocate a new buffer for stack";
    }   	
    cap = nCap;
   	data = nData;   	
   	nData = NULL;
    delete [] nData;

}


#endif // STACK_H

