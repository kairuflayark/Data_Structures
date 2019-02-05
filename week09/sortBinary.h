/***********************************************************************
 * Module:
 *    Week 09, Sort Binary
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement the Binary Tree Sort
 ************************************************************************/

#ifndef SORT_BINARY_H
#define SORT_BINARY_H

#include "bst.h"

/*****************************************************
 * SORT BINARY
 * Perform the binary tree sort
 ****************************************************/
template <class T>
void sortBinary(T array[], int num)
{
	
	BST<T> toSort;

	for (int i = 0; i < num; i++)
		toSort.insert(array[i]);

	BSTIterator<T> it = toSort.begin();

	for (int i = 0; i < num; i++)
	{
		array[i] = *it; 
		it++;
	}
}


#endif // SORT_BINARY_H
