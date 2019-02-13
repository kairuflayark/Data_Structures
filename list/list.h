/***********************************************************************
* Header:
*    List
* Summary:
*    This class contains the notion of a List for use in storing
*			data
*
*	 This will contain the class definition of:
*        List         : A class that that stores data using pointers
*
* Author
*    James Call
************************************************************************/

#include "node.h"
#include <iostream>    
using namespace std;

#ifndef LIST_H
#define LIST_H

// forward declaration of iterator
template <class T>
class ListIterator;



template <class T>
class List
{
public:

   // default constuctor
   List(){ nBegin = NULL; numItems = 0; nEnd = NULL; }

   // copy constuctor
   List(const List & rhs) throw (const char *);

   // destructor
   ~List(){ if (nBegin) {freeData(nBegin); return; } }

   // assignment operator
   const List & operator=(const List <T> & rhs) throw (const char *);

   // checks if list is empty
   bool empty(){ return numItems == 0; }
   
   // clear list
   void clear(){ freeData(nBegin); numItems = 0; nBegin = NULL; nEnd = NULL; }

   // returns the size of the list
   int size(){ return numItems; }

   // pushes item onto end of the list
   void push_back(const T & data){ insert(end(), data); }

   // pushes item onto front of the list
   void push_front(const T & data){ insert(begin(), data); }

   // returns the front item
   T & front() throw (const char *);

   // returns the back item
   T & back() throw (const char *);

   // inserts item to provided iterator location
   ListIterator<T> insert( ListIterator<T> it, const T &data) throw (const char *);

   // removes item from provided iterator location
   void remove(ListIterator<T> toDelete) throw (const char *);

   // creates an iterator pointing to beginning of the list
   ListIterator<T> begin(){ return ListIterator<T>(nBegin); }

   // creates an iterator pointing to the end of the list
   ListIterator<T> rbegin(){ return ListIterator<T>(nEnd); }

   // creates an iterator pointing to past the end of the list
   ListIterator<T> end(){ return ListIterator<T>(NULL); }

   // creates an iterator pointing to the past the front of the list
   ListIterator<T> rend(){ return ListIterator<T>(NULL); }

   // deletes the list
   void freeData(Node<T> * &node);



private:
   Node <T>* nBegin;
   Node <T>* nEnd;
   int numItems;

};


/**************************************************
 * List ITERATOR
 * An iterator through List
 *************************************************/
template <class T>
class ListIterator
{
   friend ListIterator<T> List<T> ::insert( ListIterator<T> p, const T &data) throw (const char *);

   friend void List<T> ::remove(ListIterator<T> toDelete) throw (const char *);

  	public:
   // default constructor
  	ListIterator() : p(NULL) {}

   // initialize to direct p to some item
  	ListIterator(Node<T> * p) : p(p) {}

   // retreves the data for use
   T & getData(){ return p->data; }

   // sets the data
   void setData(const T & data) { p->data = data; }

   // not equals operator
   bool operator != (const ListIterator & rhs) const
   {
      return rhs.p != this->p;
   }

   // equal operator
   bool operator ==(const ListIterator & rhs) const
   {
      return rhs.p == this->p;
   }

   // dereference operator
   T & operator * ()
   {
      return p->data;
   }

   // prefix increment
   ListIterator <T> & operator ++ ()
   {
      p = p->pNext; 
      return *this;
   }

   // postfix increment
   ListIterator <T> operator++(int postfix)
   {
      ListIterator<T> tmp(*this);
      p = p->pNext;
      return tmp;
   }

   ListIterator <T> & operator -- ()
   {
      p = p->pPrev; 
      return *this;
   }

   ListIterator <T> operator--(int postfix)
   {
      ListIterator<T> tmp(*this);
      p = p->pPrev;
      return tmp;
   }

   // assignment operator
   const ListIterator <T> operator=(const ListIterator<T> & rhs)
   {
      this->p = rhs.p;
   }


  private:
   Node<T> * p;
};

/**************************************************
 * LIST :: COPY CONSTRUCTOR
 * copies the list
 *************************************************/
template <class T>
List <T> :: List(const List <T> & rhs) throw (const char *)
{
	cerr << "\ncopy constuctor\n";
   try
   {
      nBegin = copy(rhs.nBegin);
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
   for (Node <T> * p = nBegin; p; p = p->pNext)
   {
      nEnd = p;
   }
   numItems = rhs.numItems;
}

/**************************************************
 * LIST :: ASSIGNMENT OPERATOR
 * copies list to different list
 *************************************************/
template <class T>
const List <T> & List <T>::operator=(const List <T> & rhs) throw (const char *)
{
	cerr << "\nassignment constuctor\n";
   if (this->nBegin)
      freeData(this->nBegin);
   try
   {
      this->nBegin = copy(rhs.nBegin);
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
   for (Node <T> * p = this->nBegin; p; p = p->pNext)
   {
      this->nEnd = p;
   }
   this->numItems = rhs.numItems;
   return *this;
}


/**************************************************
 * LIST:: FRONT
 * Returns the front item
 *************************************************/
template <class T>
T & List<T> ::front() throw (const char *)
{
   if (numItems == 0)
      throw "ERROR: unable to access data from an empty list";
   else
      return nBegin->data;
}

/**************************************************
 * LIST:: BACK
 * Returns the back item
 *************************************************/
template <class T>
T & List<T> ::back() throw (const char *)
{
   if (numItems == 0)
      throw "ERROR: unable to access data from an empty list";
   else
      return nEnd->data;
}

/**************************************************
 * LIST:: INSERT
 * inserts data into the place before the provided iterator
 *************************************************/
template <class T>
ListIterator<T> List<T> ::insert( ListIterator<T> it, const T &data) throw (const char *)
{
   try
   {
      Node<T>* tmp = new Node<T>(data);
      if (nBegin == NULL) // insert to empty list
      {
         nBegin = tmp;
         nEnd = tmp;
      }
      else if (it.p == NULL) // insert to end of list
      { 
         nEnd->pNext = tmp;
         tmp->pPrev = nEnd;
         nEnd = tmp;
      }
      else
      {
         tmp->pNext = it.p;
         tmp->pPrev = it.p->pPrev;
         it.p->pPrev = tmp;
         if (it.p == nBegin) // if at beginning
            nBegin = tmp;
         else // everything else
            tmp->pPrev->pNext = tmp;
      }
      numItems++;
      return ListIterator<T>(tmp);
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
}

/**************************************************
 * LIST:: REMOVE
 * Removes the item at the provided iterator
 *************************************************/
template <class T>
void List<T> :: remove(ListIterator<T> toDelete) throw (const char *)
{
   // check for tail
   if(toDelete.p->pNext == NULL)      
   {
      toDelete.p->pPrev->pNext = NULL;
      nEnd = toDelete.p->pPrev; 
   } // check for head
   else if (toDelete.p->pPrev == NULL)
   {
      toDelete.p->pNext->pPrev = NULL;
      nBegin = toDelete.p->pNext;
   } 
   else	// everything else
   {
      toDelete.p->pNext->pPrev = toDelete.p->pPrev;
      toDelete.p->pPrev->pNext = toDelete.p->pNext;
   }
   delete toDelete.p;
}

/********************************
* LIST :: FREEDATA
* function that deletes the list
********************************/
template <class T>
void List<T>::freeData(Node<T> * &node)
{	
	if(!node)
		return;
	// if at the end of the list
	// Use recurrsion to walk through the list
	else
	{
		if (node->pNext)
		{
			freeData(node->pNext);
		}
	delete node;
	node = NULL;
	return;
	}
}


#endif