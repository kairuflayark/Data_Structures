   /***********************************************************************
* Header:
*    Queue
* Summary:
*    This class contains the notion of a container: a bucket to hold
*    data for the user. This is just a starting-point for more advanced
*    constainers such as the queue, set, queue, queue, deque, and map
*    which we will build later this semester.
*
*    This will contain the class definition of:
*        Queue         : A class that holds stuff
*        QueueIterator : An interator through Queue
* Author
*    Br. Helfrich
************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include <cassert>

/************************************************
 * QUEUE
 * A class that holds stuff
 ***********************************************/
template <class T>
class Queue
{
public:
   // default constructor : empty and kinda useless
   Queue() :numItems(0), qFront(0), qBack(0), cap(0), data(NULL) {}

   // non-default constructor : pre-allocate
   Queue(int capacity) throw (const char *);

   // copy constructor : copy it
   Queue(const Queue & rhs) throw (const char *);

   // assignment operation
   const Queue & operator=(const Queue <T> & rhs) throw (const char *);   

   // subscript operator
   T & operator[](int index) throw (const char *);

   // subscript operator
   T & operator[](int index) const throw (const char *);
   
   // destructor : free everything
   ~Queue()        { if (cap) delete [] data; }
   
   // is the container currently empty
   bool empty() const  { return numItems == 0;         }

   // remove all the items from the container
   void clear()        { qFront = 0; qBack = 0; numItems = 0;           }

   // how many items are currently in the container?
   int size() const { return numItems; }

   // reallocate more room in data array
   void reallocate() throw (const char *);

   // add an item to end of container
   void push(const T & item) throw (const char *);

   // remove item from queue
   void pop() throw (const char *);

   // returns the first item
   T & front() throw (const char *);

   // retrieve value of last item in queue
   T & back() throw (const char *);

   // how large is the container
   int capacity(){  return cap;  }



private:
   T * data;         // dynamically allocated array of T
   int numItems;     // number of Items in Queue
   int qFront;       // where is the qFront of the queue
   int qBack;        // where is the qBack of the queue
   int cap;          // how many items can I put on the Queue before full?
};


/*******************************************
 * QUEUE :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Queue <T> :: Queue(const Queue <T> & rhs) throw (const char *)
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
 * QUEUE :: ASSIGNMENT OPERATOR
 *******************************************/
template <class T>
const Queue <T> & Queue <T>::operator=(const Queue <T> & rhs) throw (const char *)
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
         throw "ERROR: Unable to allocate a new buffer for queue";
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
 * QUEUE : NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "capacity"
 **********************************************/
template <class T>
Queue <T> :: Queue(int capacity) throw (const char *)
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
      throw "ERROR: Unable to allocate a new buffer for queue";
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
* QUEUE :: POP
* Remove item from container
*****************************************************/
template <class T>
void Queue <T> ::pop() throw (const char *)
{
   if (!empty())
   {
   	numItems--;
      qFront = (qFront + 1) % cap;
   }
   else
   {
      throw "ERROR: attempting to pop from an empty queue";
   }
}


/****************************************************
* QUEUE :: PUSH
* Insert an item on the top of the container
*****************************************************/
template <class T>
void Queue <T> ::push(const T &item) throw (const char *)
//void push(T & item) throw (const char *);

{
   
   if (qBack >= cap && numItems != cap)
   {
      qBack = 0;

   }
   
   if(numItems == cap)
   {
      reallocate();
   }
   // check that there is enough space for it to add 
   
   data[qBack] = item;
   numItems++;
   qBack++;

}

/****************************************************
* QUEUE :: FRONT
* Returns the value of the top item on a queue
*****************************************************/
template <class T>
T & Queue <T> ::front() throw (const char *)
{
   if (numItems == 0)
   {
      throw "ERROR: attempting to access an item in an empty queue";
   }
   else
   {
      return data[qFront];
   }
}

/****************************************************
* QUEUE :: BACK
* Returns the value of the top item on a queue
*****************************************************/
template <class T>
T & Queue <T> ::back() throw (const char *)
{
   if (numItems == 0)
   {
      throw "ERROR: attempting to access an item in an empty queue";
   }
   else
   {  
      return data[qBack - 1];
   }
}


/****************************************************
* QUEUE :: REALLOCATE
* Returns the value of the top item on a queue
*****************************************************/
template <class T>
void Queue <T> ::reallocate() throw (const char *)
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
      throw "ERROR: Unable to allocate a new buffer for queue";
   }     

   delete [] data;
   qFront = 0;
   qBack = copy;
   cap = nCap;
   data = nData;     

}

#endif // QUEUE_H

