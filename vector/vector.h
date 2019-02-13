/***********************************************************************
* Header:
*    Vector
* Summary:
*    This class contains the notion of a container: a bucket to hold
*    data for the user. This is just a starting-point for more advanced
*    constainers such as the vector, set, stack, queue, deque, and map
*    which we will build later this semester.
*
*    This will contain the class definition of:
*        Vector         : A class that holds stuff
*        VectorIterator : An interator through Vector
* Author
*    Br. Helfrich
************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>

// forward declaration for VectorIterator
template <class T>
class VectorIterator;

/************************************************
 * VECTOR
 * A class that holds stuff
 ***********************************************/
template <class T>
class Vector
{
public:
   // default constructor : empty and kinda useless
   Vector() : numItems(0), cap(0), data(NULL) {}

   // non-default constructor : pre-allocate
   Vector(int capacity) throw (const char *);

   // copy constructor : copy it
   Vector(const Vector & rhs) throw (const char *);

   // assignment operation
   const Vector & operator=(const Vector <T> & rhs) throw (const char *);   

   // subscript operator
   T & operator[](int index) throw (const char *);

   // subscript operator
   T & operator[](int index) const throw (const char *);
   
   // destructor : free everything
   ~Vector()        { if (cap) delete [] data; }
   
   // is the container currently empty
   bool empty() const  { return numItems == 0;         }

   // remove all the items from the container
   void clear()        { numItems = 0;                 }

   // how many items are currently in the container?
   int size() const    { return numItems;              }

   // add an item to the container
   void insert(const T & t) throw (const char *);

   // add an item to end of container
   void push_back(const T & item) throw (const char *);

   // how large is the container
   int capacity(){ return cap; }


   // return an iterator to the beginning of the list
   VectorIterator <T> begin() { return VectorIterator<T>(data); }

   // return an iterator to the end of the list
   VectorIterator <T> end() { return VectorIterator<T>(data + numItems);}
   
private:
   T * data;          // dynamically allocated array of T
   int numItems;      // how many items are currently in the Vector?
   int cap;           // how many items can I put on the Vector before full?
};

/**************************************************
 * VECTOR ITERATOR
 * An iterator through Vector
 *************************************************/
template <class T>
class VectorIterator
{
  public:
   // default constructor
  VectorIterator() : p(NULL) {}

   // initialize to direct p to some item
  VectorIterator(T * p) : p(p) {}


   // not equals operator
   bool operator != (const VectorIterator & rhs) const
   {
      return rhs.p != this->p;
   }

   // equal operator
   bool operator ==(const VectorIterator & rhs) const
   {
      return rhs.p == this->p;
   }

   // dereference operator
   T & operator * ()
   {
      return *p;
   }

   // prefix increment
   VectorIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   VectorIterator <T> operator++(int postfix)
   {
      VectorIterator tmp(*this);
      p++;
      return tmp;
   }

   // assignment operator
   const VectorIterator <T> operator=(const VectorIterator & rhs)
   {
      this->p = rhs.p;
   }

  private:
   T * p;
};



/*******************************************
 * VECTOR :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Vector <T> :: Vector(const Vector <T> & rhs) throw (const char *)
{
   assert(rhs.cap >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.cap == 0)
   {
      cap = numItems = 0;
      data = NULL;
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
 * VECTOR :: ASSIGNMENT OPERATOR
 *******************************************/
template <class T>
const Vector <T> & Vector <T>::operator=(const Vector <T> & rhs) throw (const char *)
{
   assert(rhs.cap >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.cap == 0)
   {
      cap = numItems = 0;
      data = NULL;
   }

   // check that it has enough space allocate
   if (cap < rhs.cap)
   {
      // attempt to allocate
      try
      {
         data = new T[rhs.cap];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate buffer";
      }
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


/**********************************************
 * VECTOR : NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "capacity"
 **********************************************/
template <class T>
Vector <T> :: Vector(int capacity) throw (const char *)
{
   assert(capacity >= 0);
   
   // do nothing if there is nothing to do
   if (capacity == 0)
   {
      this->cap = this->numItems = 0;
      this->data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[capacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

      
   // copy over the stuff
   this->cap = capacity;
   this->numItems = 0;

   // initialize the container by calling the default constructor
   for (int i = 0; i < capacity; i++)
      data[i] = T();
}


/****************************************************
* VECTOR :: PUSH_BACK
* Insert an item on the end of the container
*****************************************************/
template <class T>
void Vector <T> ::push_back(const T &item) throw (const char *)
//void push_back(T & item) throw (const char *);

{
   // check that there is enough space for it to add
   if (numItems == cap)
   {
      // create local variables
      T* nData;
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
         }
      }
   	catch (std::bad_alloc)
      {
  			   throw "ERROR: Unable to allocate buffer";
      }

      // loop through old data
   	for(int i = 0; i < numItems; i++)
   	{
            nData[i] = data[i];
      }	
      nData[numItems] = item;
   	cap = nCap;
   	data = nData;
   	
   }
   else 
 	{
   		data[numItems] = item;
 	}
   	numItems++;
}

/*******************************************
 * VECTOR :: SUBSCRIPT OPERATOR
 *******************************************/
template <class T>
T & Vector <T> :: operator[](int index) throw (const char *)
{
   if (index > numItems)
   {
      throw "ERROR: Invalid Index";
   }
   else
      return data[index];
}

/*******************************************
 * VECTOR :: SUBSCRIPT OPERATOR
 *******************************************/
template <class T>
T & Vector <T> :: operator[](int index) const throw (const char *)
{
   if (index > numItems)
   {
      throw "ERROR: Invalid Index";
   }
   else
      return data[index];
}

#endif // VECTOR_H

