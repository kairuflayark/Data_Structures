/***********************************************************************
* Header:
*    Node
* Summary:
*    This class contains the notion of a Node for use in creating a linked 
*		list
*
*	 This will contain the class definition of:
*        Node         : A class that forms the base of a linked list
*
* Author
*    James Call
************************************************************************/


#include <iostream>    
using namespace std;

#ifndef NODE_H
#define NODE_H


/**********************************************************************
* NODE
* A class that holds the data of a linked list
***********************************************************************/
template <class T>
class Node
{
public:

	//default constructor
	Node() { pNext = NULL; }

	// non-default constructor for data
	Node( T nData) {data = nData; pNext = NULL;}
	//Node( T nData, Node<T>* pNext) {data = nData; this->pNext = pNext; }

	// variables
	T data;					// stores data
	Node<T>* pNext;		// pointer to the next node in list
};


/**********************************
* COPY
* Non-member function that copies the linked list
**********************************/
template <class T>
Node<T>* copy(Node<T>* node)
{
	Node<T> * p = new Node <T>;
	if (node->pNext == NULL)
	{
		p->data = node->data;
		return p;
	}
	else
	{
		p->data = node->data;
		p->pNext = copy(node->pNext);
		return p;
	}
}

/*********************************
* INSERT
* Non-member function that inserts data into the linked list
*********************************/
template <class T>
void insert(const T nData, Node<T>* &before, bool toHead = false)
{
	Node<T> * p = new Node <T>;
	p->data = nData;
	// check for list being NULL
	if (!before)
	{
		p->pNext = NULL;
		before = p;
	}
	// if insert was to head of list
	else if(toHead)
	{
		p->pNext = before;
		before = p;
	}
	else
	{
		p->pNext = before->pNext;
		before->pNext = p;
	}
}

/*********************************
* FIND
* Non-member function to find location of data in the linked list
*********************************/
template <class T>
Node <T> * find( Node<T>* first, const T data)
{
	Node<T> * ptr = first;
	while(ptr != NULL && ptr->data != data)
	{
		ptr = ptr->pNext;
	}
	return ptr;
}


/********************************
* OPERATOR <<
* Outs the data in the list
********************************/
template <class T>
ostream & operator << (ostream & out, Node <T> * pHead )
{
	for (Node <T> * p = pHead; p; p = p->pNext)
	{
		out << p->data;
		if (p->pNext)
			out << ", ";
	}
	return out;
}


/********************************
* FREEDATA
* Non-member function that deletes the list
********************************/
template <class T>
void freeData(Node<T> * &node)
{	
	if(!node)
		return;
	// if at the end of the list
	if (node->pNext == NULL)
	{
		delete node;
		node = NULL;
		return;
	}
	// Use recurrsion to walk through the list
	else
	{
		freeData(node->pNext);
		delete node;
		node = NULL;
		return;
	}
}

#endif
