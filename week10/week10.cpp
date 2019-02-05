/*****************************************************************************
 *Module:
 *    Week 10, Word Count
 *    Brother Ercanbrack, CS 235
 * Author:
 *    James Call
 * Summary:
 *    This program will implement a map to count the frequency of words in a .txt file
 *
 *****************************************************************************/

#include <map>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cctype>
#include <string> 

using namespace std;

/*****************************************************************
* FUNCTION:: GETFILENAME
*	prompts user for the file to be read
*****************************************************************/
string getFileName()
{
	string fName;
	cout << "Enter filename: ";
	cin >> fName;
	return fName;
}

/*****************************************************************
* FUNCTION:: READFILE
*	reads the file into the Map
*****************************************************************/
map<string, int> readFile(string fName)
{
	string word;
	map<string, int> words;
	int wordCount = 0;
	ifstream fin;
	fin.open(fName.c_str());
	if (!fin)
	{
	  	cout << "Error reading file" << endl;
	}
	else
	{
		while(fin >> word)
		{
			for (int i = 0; word[i]; i++)
			{
				if (ispunct(word[i]) && word[i] != '-')
					word.erase(i, 1);
				word[i] = tolower(word[i]);
			}
			words[word]++;
			wordCount++;
		}
	}
	fin.close();
	cout << "\nNumber of words processed: " << wordCount << endl; 
	return words;
}

/*****************************************************************
* FUNCTION:: TRANSFERMAP
*	transfers map from map<string, int> to Multimap<int, string>
*****************************************************************/
multimap<int, string> transferMap(map<string, int> words)
{
	multimap<int, string> sWords;
	map<string, int>::reverse_iterator rit;
	for( rit = words.rbegin(); rit != words.rend(); ++rit)
	{
		sWords.insert(pair<int, string>(rit->second, rit->first));
	}	
	return sWords;
}

/*****************************************************************
* FUNCTION:: DISPLAY
*	Displays the words and their frequencies
*****************************************************************/
void display(multimap<int, string> sWords) 
{
	int i = 0;
	if (sWords.size() > 100)
		cout << "100";
	else
		cout << sWords.size();
	cout << " most common words found and their frequencies:" << endl;
	multimap<int, string>::reverse_iterator rit;
	for(rit = sWords.rbegin(); rit != sWords.rend(); ++rit)
	{
		cout << setw(23) << rit->second << " - " << rit->first << endl;
		i++;
		if (i == 100)
			break;
	}
}


/*****************************************************************
* FUNCTION:: MAIN
* Purpose: This is the entry point and driver for the program.
*****************************************************************/
int main()
{
	string fName;
	map<string, int> words;
	multimap<int, string> sWords;
	fName = getFileName();
	words = readFile(fName);
	sWords = transferMap(words);
	display(sWords);





	return 0;
}