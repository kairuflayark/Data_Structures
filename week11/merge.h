/***********************************************************************
* Program:
*    Week 11, Sorting
*    Brother Ercanbrack, CS 235
*
* Author:
*   James Call  
* Summary: 
*	Turns a list into a sorted list.
************************************************************************/
#include <list>
   
using namespace std;

/*********************************************************************
* SPLIT
* Splits the data according to the Natural Merge sort
**********************************************************************/
template<class T>
void split(list<T> &data, list<T> &f1, list<T> &f2)
{
	f1.clear();
	f2.clear();
	while(!data.empty())
	{
		do
		{
			f1.push_back(data.front());
			data.pop_front();
		}
		while(!data.empty() && (f1.back() <= data.front() || f1.empty()));

		if ( data.empty())
			break;

		do
		{
			f2.push_back(data.front());
			data.pop_front();
		}
		while (!data.empty() && (f2.back() <= data.front() || f2.empty()));
	}
}

/**********************************************************************
* MERGE
* Merges the data according to the natural merge sort
***********************************************************************/
template<class T>
void merge(list<T> &data, list<T> &f1, list<T> &f2)
{
	data.clear();
	while (!f1.empty() || !f2.empty())
	{
		if(f1.empty())
		{
			data.push_back(f2.front());
			f2.pop_front();
		}
		else if(f2.empty())
		{
			data.push_back(f1.front());
			f1.pop_front();
		}
		else
		{
			if (f1.front() <= f2.front())
			{
				data.push_back(f1.front());
				f1.pop_front();
			}
			else
			{
				data.push_back(f2.front());
				f2.pop_front();
			}
		}
	}
}



/*************************************************************************
* This function sorts a linked list using a Natural Merge Sort.
* Input:  data -  linked list of data to be sorted.
* Output: data -  sorted linked list
**************************************************************************/
template<class T>
void mergeSort(list<T> &data)
{
	list<T> f1;
	list<T> f2;
	bool sorted = false;
	while (!sorted)
	{
		split(data, f1, f2);
		if (f2.empty())
			sorted = true;
	
		merge(data, f1, f2);
	
	}
}

