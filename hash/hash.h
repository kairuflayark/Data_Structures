
#ifndef HASH_H
#define HASH_H

#include <list>
#include <vector>
#include <string>
using namespace std;

template <class T>
class Hash
{
public:
	//Default constructor
	Hash(){ numItems = 0; buckets = 0; data = NULL; }
	Hash(int buckets) throw (const char *);
	Hash(const Hash<T> & rhs) throw (const char *);
	
	// deconstructor
	~Hash() { if (buckets) clear(); }
	Hash<T>  &operator=(const Hash<T> & rhs) throw (const char *);

	// returns if the hash table is empty
	bool empty() { return numItems == 0; }

	// returns the number of items in the hash table
	int size() { return numItems; }
	void clear();

	// returns the number of Buckets
	int capacity() const { return buckets; }

	bool find(T data);
	void insert(T data);
	
	// virtual function for to find the hash value
	virtual int hash(const T &data) const = 0;



private:
	vector< list<T> > data;	
	int numItems;
	int buckets;
};






/****************************************
* Non Default constructor
*
*****************************************/
template <class T>
Hash<T>::Hash(int buckets) throw (const char *)
{
	try
	{
		data.resize(buckets);
		this->buckets = buckets; 
		this->numItems = 0;
	}
	catch (bad_alloc)
	{
		throw "ERROR: Unable to allocate memory for the hash.";
	}
}

/*****************************************************************************
* Copy constructor
* copies one hash to a new hash
******************************************************************************/
template <class T>
Hash<T> :: Hash(const Hash<T> & rhs) throw (const char *)
{
	try
	{
		this->data = rhs.data;
		this->buckets = rhs.buckets; 
		this->numItems = rhs.numItems;
	}
	catch (bad_alloc)
	{
		throw "ERROR: Unable to allocate memory for the hash.";
	}
}

/*****************************************************************************
* Assignment operator
* copies one hash to another
******************************************************************************/
template <class T>
Hash<T> & Hash <T> ::operator=(const Hash<T> & rhs) throw (const char *)
{
		clear();
		try
		{
			this->data = rhs.data;
			this->buckets = rhs.buckets; 
			this->numItems = rhs.numItems;
		}
		catch (bad_alloc)
		{
			throw "ERROR: Unable to allocate memory for the hash.";
		}
		return *this;
	
}

/*****************************************************************************
* HASH::CLEAR
* clears the hash of items and buckets
******************************************************************************/
template <class T>
void Hash<T>::clear()
{
	if (data.size() > 0)
	{
		for (int i = 0; i < buckets; ++i)
		{
			data[i].clear();
		}
		data.clear();
	}
	numItems = 0;
	buckets  = 0;
} 

/*****************************************************************************
* HASH::FIND
* uses the hash function to find the location where the item would be located
******************************************************************************/
template <class T>
bool Hash<T>::find(T data)
{
	int index = hash(data);

	if (this->data[index].empty())
		return false;

	for (typename list<T>::iterator it = this->data[index].begin(); it != this->data[index].end(); it++ )
	{
		if (*it == data)
		return true;
		
	}
	return false;
}

/*****************************************************************************
* HASH::FIND
* Inserts the item into the spot designated by the hash function
******************************************************************************/
template <class T>
void Hash<T>::insert(T data)
{
	int index = hash(data);

	this->data[index].push_back(data);
	numItems++;
}





#endif
