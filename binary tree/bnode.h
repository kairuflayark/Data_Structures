#ifndef BNODE_H
#define BNODE_H

#include <iostream> 
#include <cassert>

/*****************************************************************
 * BINARY NODE
 * A single node in a binary tree.  Note that the node does not know
 * anything about the properties of the tree so no validation can be done.
 *****************************************************************/
template <class T>
class BinaryNode
{
public:

BinaryNode(){ pLeft = NULL; pRight = NULL; pParent = NULL; }
BinaryNode(T data){ pLeft = NULL; pRight = NULL; pParent = NULL; this->data = data; }
   // return size (i.e. number of nodes in tree)
   int size() const
   {
            return 1 +
               (pLeft== NULL? 0 : pLeft->size()) +
               (pRight == NULL ? 0 : pRight->size());
   }
   
   // add a node to the left/pRight
   void addLeft (BinaryNode <T> * pNode);
   void addRight(BinaryNode <T> * pNode);

   // create a node and add it to the left/right
   void addLeft (const T & t) throw (const char *);
   void addRight(const T & t) throw (const char *);


   
   // since no validation is done, everything is public
   BinaryNode <T> * pLeft;
   BinaryNode <T> * pRight;
   BinaryNode <T> * pParent;
   T data;
};

/***************************************************
* BINARY NODE :: ADDLEFT
* sets the Node to the pLeft
****************************************************/
template <class T>
void BinaryNode<T>::addLeft(BinaryNode <T> * pNode)
{
	this->pLeft = pNode;
	if (pNode != NULL)
	{
		pNode->pParent = this;
	}
}

/***************************************************
* BINARY NODE :: ADDRIGHT
* sets the Node to the pRight
****************************************************/
template <class T>
void BinaryNode<T>::addRight(BinaryNode <T> * pNode)
{
	this->pRight = pNode;
	if (pNode != NULL)
	{
		pNode->pParent = this;
	}
}

/***************************************************
* BINARY NODE :: ADDLEFT
* Creates Node & sets it to the pLeft
****************************************************/
template<class T>
void BinaryNode<T>::addLeft (const T & t) throw (const char *)
{
	BinaryNode<T> * lNode;
	try
	{
		lNode = new BinaryNode<T>;
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: unable to allocate a node";
	}
	lNode->data = t;
	this->pLeft = lNode;
	lNode->pParent = this;
}

/***************************************************
* BINARY NODE :: ADDRIGHT
* Creates Node & sets it to the pLeft
****************************************************/
template <class T>
void BinaryNode<T>::addRight(const T & t) throw (const char*)
{
	BinaryNode<T> * rNode;
	try
	{
		rNode = new BinaryNode<T>;
	}
	catch (std:: bad_alloc)
	{
		throw "ERROR: unable to allocate a node";
	}
	rNode->data = t;
	this->pRight = rNode;
	rNode->pParent = this;
}

/***************************************************
* DELETE BINARY TREE
* Deletes the Binary Tree down from a given Node
****************************************************/
template <class T>
void deleteBinaryTree(BinaryNode <T> * pNode)
{
	if( pNode == NULL)
		return;
	if (pNode->pLeft != NULL)
		deleteBinaryTree(pNode->pLeft);
	if (pNode->pRight != NULL)
		deleteBinaryTree(pNode->pRight);
	delete pNode;
	pNode = NULL;
}

/***************************************************
* OSTREAM OPERATOR
* Outs the binary tree in a prefix form 
****************************************************/
template <class T>
std::ostream & operator << (std::ostream & out, const BinaryNode <T> * pNode)
{
	if (pNode->pLeft != NULL)
		out << pNode->pLeft;
	out << pNode->data << ' ';
	if (pNode->pRight != NULL)
		out << pNode->pRight;
	return out;

}

#endif // BNODE_H
