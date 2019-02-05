   /***********************************************************************
* Header:
*    Deque
* Summary:
*    This class contains the notion of a container: a bucket to hold
*    data for the user. This is just a starting-point for more advanced
*    constainers such as the deque, set, deque, deque, deque, and map
*    which we will build later this semester.
*
*    This will contain the class definition of:
*        Deque         : A class that holds stuff
*        DequeIterator : An interator through Deque
* Author
*    Br. Helfrich
************************************************************************/

#ifndef DEQUE_H
#define DEQUE_H

#include <cassert>

/************************************************
 * DEQUE
 * A class that holds stuff
 ***********************************************/
template <class T>
class Deque
{
public:
   // default constructor : empty and kinda useless
   Deque() :numItems(0), qFront(0), qBack(0), cap(0), data(NULL) {}

   // non-default constructor : pre-allocate
   Deque(int capacity) throw (const char *);

   // copy constructor : copy it
   Deque(const Deque & rhs) throw (const char *);

   // assignment operation
   const Deque & operator=(const Deque <T> & rhs) throw (const char *);   

   // subscript operator
   T & operator[](int index) throw (const char *);

   // subscript operator
   T & operator[](int index) const throw (const char *);
   
   // destructor : free everything
   ~Deque()        { if (cap) delete [] data; }
   
   // is the container currently empty
   bool empty() const  { return numItems == 0;         }

   // remove all the items from the container
   void clear()        { qFront = 0; qBack = 0; numItems = 0;           }

   // how many items are currently in the container?
   int size() const { return numItems; }

   // reallocate more room in data array
   void reallocate() throw (const char *);

   // add an item to end of container
   void push_back(const T & item) throw (const char *);

   void push_front(const T & item) throw (const char *);

   // remove item from deque
   void pop_front() throw (const char *);

   void pop_back() throw (const char *);

   // returns the first item
   T & front() throw (const char *);

   // retrieve value of last item in deque
   T & back() throw (const char *);

   // how large is the container
   int capacity(){  return cap;  }



private:
   T * data;         // dynamically allocated array of T
   int numItems;     // number of Items in Deque
   int qFront;       // where is the qFront of the deque
   int qBack;        // where is the qBack of the deque
   int cap;          // how many items can I put on the Deque before full?
};


/*******************************************
 * DEQUE :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Deque <T> :: Deque(const Deque <T> & rhs) throw (const char *)
{
   assert(rhs.cap >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.cap == 0)
   {
      cap = qBack = 0;
      qFront = 0;
      numItems = 0;     
      data = NULL;
 
      return;
   }
   //delete [] data;
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

   int copy = 0;
   // copy the items over one at a time using the assignment operator
   for (int i = rhs.qFront; i < (rhs.numItems + rhs.qFront); i++)
   {

      data[copy] = rhs.data[i % rhs.cap];
      copy++;
   }
   qFront = 0;
   qBack = copy;
   numItems = rhs.numItems;
   // the rest needs to be filled with the default value for T
   for (int i = qBack; i < cap; i++)
      data[i] = T();
}

/*******************************************
 * DEQUE :: ASSIGNMENT OPERATOR
 *******************************************/
template <class T>
const Deque <T> & Deque <T>::operator=(const Deque <T> & rhs) throw (const char *)
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
         data = new T[rhs.cap];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for deque";
      }
   }
   // copy the items over one at a time using the assignment operator
   int copy = 0;
   for (int i = rhs.qFront; i < (rhs.numItems + rhs.qFront); i++)
   {
      data[copy] = rhs.data[i % rhs.cap];
      copy++;
   }
   qFront = 0;
   qBack = copy;
   cap = rhs.cap;
   numItems = rhs.numItems;
   
   return *this;
}


/**********************************************
 * DEQUE : NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "capacity"
 **********************************************/
template <class T>
Deque <T> :: Deque(int capacity) throw (const char *)
{
   assert(capacity >= 0);
   
   // do nothing if there is nothing to do
   if (capacity == 0)
   {
      this->cap = this->qBack = 0;
      qFront = 0;
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
      throw "ERROR: Unable to allocate a new buffer for deque";
   }

      
   // copy over the stuff
   this->cap = capacity;
   this->qFront = 0;
   this->qBack = 0;
   numItems = 0;

   // initialize the container by calling the default constructor
   for (int i = 0; i < capacity; i++)
      data[i] = T();
}


/****************************************************
* DEQUE :: POP_FRONT
* Remove item from front of container
*****************************************************/
template <class T>
void Deque <T> ::pop_front() throw (const char *)
{
   if (!empty())
   {
   	numItems--;
      qFront = (qFront + 1) % cap;
   }
   else
   {
      throw "ERROR: unable to pop from the front of empty deque";
   }
}


/****************************************************
* DEQUE :: POP_BACK
* Remove item from front of container
*****************************************************/
template <class T>
void Deque <T> ::pop_back() throw (const char *)
{
   if (!empty())
   {
   	numItems--;
      qBack = qBack - 1;
      if (qBack < 0)
      	qBack = qBack + cap;
   }
   else
   {
      throw "ERROR: unable to pop from the back of empty deque";
   }
}




/****************************************************
* DEQUE :: PUSH
* Insert an item on the top of the container
*****************************************************/
template <class T>
void Deque <T> ::push_back(const T &item) throw (const char *)
//void push_back(T & item) throw (const char *);

{   
   if(numItems == cap)
   {
      reallocate();
   }
   // check that there is enough space for it to add 
   
   data[qBack] = item;
   qBack = (qBack + 1) % cap;
   numItems++;
}

/****************************************************
* DEQUE :: PUSH_FRONT
* Insert an item on the front of the container
*****************************************************/
template <class T>
void Deque <T> ::push_front(const T &item) throw (const char *)
{
	 if(numItems == cap)
   {
      reallocate();
   }
   // check that there is enough space for it to add 
   qFront = qFront - 1;
   if (qFront < 0)
   	qFront = cap - 1;
   data[qFront] = item;
   numItems++;
}



/****************************************************
* DEQUE :: FRONT
* Returns the value of the top item on a deque
*****************************************************/
template <class T>
T & Deque <T> ::front() throw (const char *)
{
   if (numItems == 0)
   {
      throw "ERROR: unable to access data from an empty deque";
   }
   else
   {
      return data[qFront];
   }
}

/****************************************************
* DEQUE :: BACK
* Returns the value of the top item on a deque
*****************************************************/
template <class T>
T & Deque <T> ::back() throw (const char *)
{
   if (numItems == 0)
   {
      throw "ERROR: unable to access data from an empty deque";
   }
   else
   {  
      return data[(qBack- 1 + cap) % cap];
   }
}


/****************************************************
* DEQUE :: REALLOCATE
* Returns the value of the top item on a deque
*****************************************************/
template <class T>
void Deque <T> ::reallocate() throw (const char *)
{
   T * nData;
   int nCap;
   int copy = 0;   
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
         for (int i = qFront; i < (numItems + qFront); i++)
         {
            nData[copy] = data[i%cap];
            copy++;
         }
      }

   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for deque";
   }     

   delete [] data;
   qFront = 0;
   qBack = copy;
   cap = nCap;
   data = nData;     

}

#endif // DEQUE_H

