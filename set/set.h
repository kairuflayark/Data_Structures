/***********************************************************************
* Header:
*    Set
* Summary:
*    This class contains the notion of a container: a bucket to hold
*    data for the user. This is just a starting-point for more advanced
*    constainers such as the set, set, stack, queue, deque, and map
*    which we will build later this semester.
*
*    This will contain the class definition of:
*        Set         : A class that holds stuff
*        SetIterator : An interator through Set
* Author
*    Br. Helfrich
************************************************************************/

#ifndef SET_H
#define SET_H

#include <cassert>

// forward declaration for SetIterator
template <class T>
class SetIterator;

/************************************************
 * SET
 * A class that holds stuff
 ***********************************************/
template <class T>
class Set
{
public:
   // default constructor : empty and kinda useless
   Set() : numItems(0), cap(0), data(NULL) {}

   // non-default constructor : pre-allocate
   Set(int capacity) throw (const char *);

   // copy constructor : copy it
   Set(const Set & rhs) throw (const char *);

   // assignment operation
   const Set & operator=(const Set <T> & rhs) throw (const char *); 

   // intersection operator
   Set  operator&&(Set <T> & set2) throw (const char*);  

   // Union operator
   Set  operator||(Set <T> & set2) throw (const char*);
   
   // subscript operator
   T & operator[](int index) throw (const char *);

   // subscript operator
   T & operator[](int index) const throw (const char *);
   
   // destructor : free everything
   ~Set()        { if (cap) delete [] data; }
   
   // is the container currently empty
   bool empty() const  { return numItems == 0;         }

   // remove all the items from the container
   void clear()        { numItems = 0;                 }

   // how many items are currently in the container?
   int size() const    { return numItems;              }

   // add an item to the container
   void insert(const T & item) throw (const char *);
   
   // adds and item to the end for the operators
   void addToEnd(const T & item) throw (const char *);

   // finds the index of the wanted item, otherwise returns -1
   int find(const T & item);
   
   // how large is the container
   int capacity(){ return cap; }

   // erases an item form the index
   void erase(int index);

    // reallocate more room in data array
   void reallocate() throw (const char *);

   // return an iterator to the beginning of the list
   SetIterator <T> begin() { return SetIterator<T>(data); }

   // return an iterator to the end of the list
   SetIterator <T> end() { return SetIterator<T>(data + numItems);}
   
private:
   T * data;          // dynamically allocated array of T
   int numItems;      // how many items are currently in the Set?
   int cap;           // how many items can I put on the Set before full?
};

/**************************************************
 * SET ITERATOR
 * An iterator through Set
 *************************************************/
template <class T>
class SetIterator
{
  public:
   // default constructor
  SetIterator() : p(NULL) {}

   // initialize to direct p to some item
  SetIterator(T * p) : p(p) {}


   // not equals operator
   bool operator != (const SetIterator & rhs) const
   {
      return rhs.p != this->p;
   }

   // equal operator
   bool operator ==(const SetIterator & rhs) const
   {
      return rhs.p == this->p;
   }

   // dereference operator
   T & operator * ()
   {
      return *p;
   }

   // prefix increment
   SetIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   SetIterator <T> operator++(int postfix)
   {
      SetIterator tmp(*this);
      p++;
      return tmp;
   }

   // assignment operator
   const SetIterator <T> operator=(const SetIterator & rhs)
   {
      this->p = rhs.p;
   }

  private:
   T * p;
};



/*******************************************
 * SET :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Set <T> :: Set(const Set <T> & rhs) throw (const char *)
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
 * SET :: ASSIGNMENT OPERATOR
 *******************************************/
template <class T>
const Set <T> & Set <T>::operator=(const Set <T> & rhs) throw (const char *)
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
         throw "ERROR: Unable to allocate a new buffer for Set.";
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
  	return *this;
}


/**********************************************
 * SET : NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "capacity"
 **********************************************/
template <class T>
Set <T> :: Set(int capacity) throw (const char *)
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
      throw "ERROR: Unable to allocate a new buffer for Set.";
   }

      
   // copy over the stuff
   this->cap = capacity;
   this->numItems = 0;

   // initialize the container by calling the default constructor
   for (int i = 0; i < capacity; i++)
      data[i] = T();
}


/****************************************************
* SET :: INSERT
* Insert an item in a sorted manner
*****************************************************/
template <class T>
void Set <T> ::insert(const T &item) throw (const char *)
{
   // check to see if the item is already in the set
	if (find(item) == -1)
   {
   	int sert = 0;
      // check for sufficent memory
		if(numItems == cap)
   	{
      	reallocate();
   	}
      // sort items and insert into an array
   	if (!empty())
   	{
			while (item > data[sert] && sert < numItems)
	   	{
	   		sert++;
	   	}
	   	for (int l = numItems - 1; l >= sert; --l)
			{
				data[l + 1] = data[l];
			}
		}
		data[sert] = item;
		numItems++;

   }
}

/*****************************************************
* SET :: ADD TO END
* Adds and item to the end of an array during operators
*****************************************************/
template <class T>
void Set <T> ::addToEnd(const T & item) throw (const char *)
{
   if (numItems == cap)
      reallocate();
   data[numItems] = item;
   numItems++;
}


/*******************************************
* SET :: FIND
* Finds the index of and item and returns -1 if not present
********************************************/
template <class T>
int Set <T> ::find(const T & item)
{
	int iBegin = 0;
	int iEnd = numItems - 1;
	int iMiddle;
   // find
	while (iBegin <= iEnd)
	{
		iMiddle = (iBegin + iEnd) / 2;
		if (item == data[iMiddle])
			return iMiddle;
		if (item < data[iMiddle])
			iEnd = iMiddle - 1;
		else
			iBegin = iMiddle + 1;
	}
	
	return -1;
}

/*******************************************
* SET :: ERASE
* removes an item from the set and writes over it
********************************************/
template <class T>
void Set <T> ::erase(int index)
{
	for (int i = index; i < numItems - 1; ++i)
	{
		data[i] = data[i + 1];
	}
	numItems--;
}





/*******************************************
 * SET :: SUBSCRIPT OPERATOR
 *******************************************/
template <class T>
T & Set <T> :: operator[](int index) throw (const char *)
{
   if (index > numItems)
   {
      throw "ERROR: Invalid Index";
   }
   else
      return data[index];
}

/*******************************************
 * SET :: SUBSCRIPT OPERATOR
 *******************************************/
template <class T>
T & Set <T> :: operator[](int index) const throw (const char *)
{
   if (index > numItems)
   {
      throw "ERROR: Invalid Index";
   }
   else
      return data[index];
}

/****************************************************
* Set :: REALLOCATE
* Reallocates space if needed
*****************************************************/
template <class T>
void Set <T> ::reallocate() throw (const char *)
{
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
   
   //delete [] data;
   cap = nCap;
   data = nData;     

}

/*************************************
* SET :: INTERSECTION OPERATOR
* returns a set of the similar items from two sets
*************************************/
template <class T>
Set <T>  Set <T>:: operator&&(Set <T> & set2) throw (const char *)
{
   int iSet1 = 0;
   int iSet2 = 0;
   Set<T> nSet;

   while( iSet1 < numItems || iSet2 < set2.size())
   {
      if (iSet1 == numItems)
         return nSet;
      else if (iSet2 == set2.size())
         return nSet;
      else if (data[iSet1] == set2.data[iSet2])
      {
         nSet.addToEnd(data[iSet1]);
         iSet1++;
         iSet2++;
      }
      else if (data[iSet1] < set2.data[iSet2])
         iSet1++;
      else
         iSet2++;
   }
   return nSet;
}

/****************************************
* SET :: UNION OPERATOR
* Returns a set of the dissimilar objects in two sets
****************************************/
template <class T>
Set <T> Set <T>:: operator||(Set <T> & set2) throw (const char *)
{
   int iSet1 = 0;
   int iSet2 = 0;
   Set<T> nSet;

   while (iSet1 < numItems || iSet2 < set2.size())
   {
      if (iSet1 == numItems)
         nSet.addToEnd(set2.data[iSet2++]);
      else if(iSet2 == set2.size())
         nSet.addToEnd(data[iSet1++]);
      else if (data[iSet1] == set2.data[iSet2])
      {
         nSet.addToEnd(data[iSet1]);
         iSet1++;
         iSet2++;
      }
      else if (data[iSet1] < set2.data[iSet2])
         nSet.addToEnd(data[iSet1++]);
      else 
         nSet.addToEnd(set2.data[iSet2++]);
   }
   
   return nSet;
}

#endif // SET_H

