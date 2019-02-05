/***********************************************************************
 * Module:
 *    Week 12, Spell Check
 *    Brother Ercanbrack, CS 235
 * Author:
 *    James Call
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "spellCheck.h"
using namespace std;
/****************************************************
* Hash(string word)
* Takes the ASCII value of the Word modulatedby capacity to find the hash value
*   this was the best value between complexity of the algorithem, and the wasted space in the hash table that I created
*****************************************************/
int SHash::hash(const string & word) const
   {
		int hashValue = 0;

		for (int i = 0; i < word.size(); i++)
		{
			hashValue += word[i];
		}
		return hashValue % capacity();
	}

/*****************************************
 * SPELL CHECK
 * Prompt the user for a file to spell-check
 ****************************************/
void spellCheck()
{
	SHash check(3000);
	string word;
	int outCount = 0;
	string tempWord;
	string fileName;
	ifstream fin;
   fin.open("/home/cs235/week12/dictionary.txt");
   if (!fin)
   {
        
      cout << "Error reading file" << endl;
   }
   else
   {
      while(fin >> word)
      {
         check.insert(word);
      }
   }
   fin.close();
   cout << "What file do you want to check? ";
   cin >> fileName;
   fin.open(fileName.c_str());
	if (!fin)
	{
	  	cout << "Error reading file" << endl;
	}
	else
	{
		while(fin >> word)
		{
			tempWord = word;
			for (int i = 0; tempWord[i]; i++)
			{
				tempWord[i] = tolower(tempWord[i]);
			}
			if (!check.find(tempWord))
			{
				if (outCount == 0)
					cout << "Misspelled: ";
				if (outCount > 0)
					cout << ", ";
				cout << word;
				outCount++;
			}
		}
		if (outCount == 0)
			cout << "File contains no spelling errors";
		cout << endl;
	}
}
