/***********************************************************************
 * Header:
 *    INSERTION SORT
 * Summary:
 *    This will contain just the prototype for insertionSortTest(). You may
 *    want to put other class definitions here as well.
 * Author
 *    <your names here>
 ************************************************************************/

#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "node.h"

/***********************************************
 * INSERTION SORT
 * Sort the items in the array
 **********************************************/
template <class T>
void sortInsertion(T array[], int num)
{
	Node <T> * sort;
	Node <T> * begin;
	begin = NULL;
	//std::cerr << sort->data;
	for (int i = 0; i < num; i++)
	{
		sort = NULL;
		// place data in the front if necessary
		if (begin == NULL || array[i] < begin->data)
		{
			insert(array[i], begin, true);
		}
		else
		{	
			// find location in list for data
			for (Node <T> * p = begin; sort == NULL; p = p->pNext)
			{
				if (p->data < array[i] && !p->pNext)
					sort = p;
				else if (p->data < array[i] && p->pNext->data > array[i])
					sort = p;
			}

			insert(array[i], sort);
		}
	}
	// transfer sorted list to the array
	int i = 0;
	while(begin != NULL)
	{
		array[i] = begin->data;
		begin = begin->pNext;
		i++;
	}
	freeData(begin);
}

#endif // INSERTION_SORT_H

