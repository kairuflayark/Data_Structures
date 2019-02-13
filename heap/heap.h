/***********************************************************************
* Program:
*    Week 11, Sorting
*    Brother Ercanbrack, CS 235
*
* Author:
*    James Call 
* Summary: 
*	 Turns a Vector from the driver into a sorted Vector through the heap method.
************************************************************************/
#include <vector>
   
using namespace std;

/**************************************************************
* PERCOLATEDOWN
* Takes an index as a parameter and fixes the heap frm that index down
***************************************************************/
template<class T>
void percolateDown(vector<T> &data, int parent, int wall)
{	
	int p = parent;
	int child = 2 * parent;
	int dataSize = data.size();
	int swap = 0;

	while (child <= dataSize)
	{
		if (child < dataSize && data[child] < data[child + 1] && child+1 < wall)
			child++;
		else if (data[p] < data[child] && child < wall)
		{
			swap = data[p];
			data[p] = data[child];
			data[child] = swap;

			p = child;
			child = child * 2;
		}
		else
			break;
	}		
}

/********************************************************************
* HEAPIFY
*  Turns the given vector into a heap
*********************************************************************/
template<class T>
void heapify(vector<T> &data, int wall)
{
	for ( int parent = data.size()/2; parent >=1; parent--)
	{
		percolateDown(data, parent, wall);
	}
}

/*************************************************************************
* This function sorts a vector using a heap sort.
* Input:  data -  Vector to be sorted.
* Output: data -  Vector sorted
**************************************************************************/
template<class T>
void heapSort(vector<T> &data)
{
  int wall = data.size() - 1;
  heapify(data, wall);


  for(wall; wall > 1; wall--)
  {
  	T temp = data[1];
  	data[1] = data[wall];
  	data[wall] = temp;
  	heapify(data, wall);
  }
}
