/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <iostream>
#include "pair.h"
#include "bnode.h"
#include <list>
#include <deque>
#include <string>
using namespace std;

typedef Pair<float, string> floStr;
typedef BinaryNode<floStr> * pBranch;
typedef BinaryNode<floStr>  branch;


class HuffTree
{
public:
	// default constructor
	HuffTree(){ bNode = NULL;}

	// non-default constructor (floStr)
	HuffTree(floStr nData);	
	// Non-default constructor ( 2 nodes)
	HuffTree(pBranch t1, pBranch t2);

	// deletes the final tree
	void deleteHuffTree(){ deleteBinaryTree(bNode); }
	

	// bNode of data type type pair
	pBranch bNode;

};

// 
void huffman(std::string fileName);

// displays the huffman code
bool encode(pBranch cBranch, string letter, deque<char> &huff);

// comparison operator for Hufftree sort
bool operator<(const HuffTree & t1, const HuffTree & t2);

//bool (&) compare(const HuffTree & t1, const HuffTree & t2);

#endif // HUFFMAN_h
