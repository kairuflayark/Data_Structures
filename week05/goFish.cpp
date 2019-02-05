/***********************************************************************
* Program:
*    Assignment 01, Go Fish
*    Brother Helfrich, CS 235
* Author:
*    James Call
* Summary: 
*    This is all the functions necessary to play Go Fish!
*
*    Estimated:  3.0 hrs   
*    Actual:     3.0 hrs
*      Remembering how to read from a file.
************************************************************************/

#include <iostream>
#include <fstream>
#include "set.h"
#include "card.h"
#include "goFish.h"
using namespace std;

/**********************************************************************
 * GO FISH
 * The function which starts it all
 ***********************************************************************/
void goFish()
{
	Set <Card> hand;
	Card guess;
	Card intoHand;
	int round = 1;
	int match = 0;
	

	ifstream fin("/home/cs235e/week05/hand.txt");
	if (fin.fail())
	      cout << "Error reading file" << endl;
	else
	{
		while (fin >> intoHand)
	    {
	    	hand.insert(intoHand);
	    }
	    fin.close();
	}


	cout << "We will play 5 rounds of Go Fish.  "
		 << "Guess the card in the hand\n";
	while (round <= 5)
	{
		cout << "round " << round <<": ";
		cin  >> guess;
		if (hand.find(guess) == -1)
			cout << "\tGo Fish!\n";
		else
		{
			match++;
			cout << "\tYou got a match!\n";
			hand.erase(hand.find(guess));
		}
		round++;
	}
	cout << "You have " << match << " matches!\n"
		  << "The remaining cards: ";


	for (SetIterator <Card> it = hand.begin(); it != hand.end(); ++it)
   {
    	if (it !=hand.begin())
    		cout << ", ";
    	cout << *it;
   }
   cout << "\n";
	return;
}
