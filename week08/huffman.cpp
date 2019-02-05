/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    James Call
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#include "huffman.h"       // for HUFFMAN() prototype
//#include "bnode.h"
#include <fstream>
#include <list>
#include <deque>

using namespace std;


bool operator<(const HuffTree & t1, const HuffTree & t2)
{

	return t1.bNode->data.first < t2.bNode->data.first;
}


/*******************************************
 * HUFFMAN
 * Driver program to exercise the huffman generation code
 *******************************************/
void huffman(std::string fileName)
{
	list <HuffTree>  tree;
	int loop = 0;
 	deque <string> letterTrack;
	float freq;
	string letter;
	try
	{
		// reads the file
		ifstream fin;
		fin.open(fileName.c_str());
		if (!fin)
		{
		   	cout << "Error reading file" << endl;
		   	return;
		}
		else
		{
			while(fin >> letter)
			{
				letterTrack.push_back(letter);
				fin >> freq;
				floStr data(freq, letter);
				HuffTree nTree(data);
				tree.push_back(nTree);
			}
		}
		fin.close();

		// creates the Huffman Tree
		HuffTree one;
		while (tree.size() > 1)
		{
			tree.sort();
			one = tree.front();
			tree.pop_front();
			HuffTree nTree(one.bNode, tree.front().bNode );
			tree.push_back(nTree);
			tree.pop_front();
		}
	}
	catch (const char * error)
   {
      cout << error << endl;
   }

	//Creates & displays the Huffman Code
	deque<char> huff;
	while (letterTrack.size() > 0)
	{
		cout << letterTrack.front() << " = ";
		encode(tree.front().bNode, letterTrack.front(), huff);
		while(huff.size() > 0)
		{
			cout << huff.front();
			huff.pop_front();
		}
		letterTrack.pop_front();
		cout << endl;
	}

	tree.front().deleteHuffTree();

   return;
}

/********************************************************
* HuffTree :: HuffTree
* Non-default constructor that creates a Hufftree from 
*			a floStr (Pair <float, string)
********************************************************/
HuffTree::HuffTree(floStr nData)
{ 
	try
	{
		pBranch nBNode = new branch(nData);		
		bNode = nBNode;	 
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: unable to allocate a node";
	}

}

/********************************************************
* HuffTree :: HuffTree
* Non-default constructor that creates a Hufftree from two nodes
********************************************************/
HuffTree :: HuffTree(pBranch t1, pBranch  t2)
{
	float freq;
	string letters;
	freq = t1->data.first + t2->data.first;
	letters = t1->data.second + t2->data.second;
	floStr data(freq, letters);
	try
	{
		pBranch nBranch = new branch(data);
		nBranch->addRight(t2);
		nBranch->addLeft(t1);
		bNode = nBranch;
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: unable to allocate a node";
	}
	

}


/********************************************************************
* ENCODE
* creates the Huffman Code
*********************************************************************/
bool encode(pBranch cBranch, string letter, deque<char> &huff)
{	

	if (cBranch->pRight != NULL)
	{
		if (encode(cBranch->pRight, letter, huff) == true)
		{
			huff.push_front('1');
			return true;
		}
	}
	if (cBranch->pLeft != NULL)
	{
		if (encode(cBranch->pLeft, letter, huff) == true)
		{
			huff.push_front('0');
			return true;
		}
	}
	if (cBranch->data.second == letter)
		return true;
	else return false;
}