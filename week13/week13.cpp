/***********************************************************************
* Program:
*    Week 13, Genealogy
*    Brother Helfrich, CS 235
* Author:
*    Br. Helfrich
* Summary: 
*    This is a driver program to exercise the Hash class.  When you
*    submit your program, this should not be changed in any way.  That being
*    said, you may need to modify this once or twice to get it to work.
************************************************************************/


#include <fstream>
#include <iostream>   
#include "list.h"
#include "person.h"
#include "bst.h"
#include <string>
#include <cstring>
#include <cctype>
using namespace std;

/************************************************************
* DISPLAY
* Displays the Person to the Console
*************************************************************/
void display(Person person)
{
   cout << "        ";
	if ( person.givenName != " ")
	   cout << person.givenName << " ";
	if ( person.surname != " ")
		cout << person.surname;
	if ( person.bYear != " ")
		cout << ", b. ";
	if ( person.bDay != " ")
		cout << person.bDay << " ";
	if ( person.bMonth != " ")
		cout << person.bMonth << " ";
	if ( person.bYear != " ")
		cout << person.bYear;
}

/************************************************************
* SORTINSERT
* Finds the location in the People list for the person to be inserted
*   by comparing the Surname, given name and birth year.
*************************************************************/
void sortInsert(Person nPerson, List<Person> &people)
{        
   ListIterator<Person> it = people.begin();
   if (people.empty())
   {
      people.insert(it, nPerson);
      return;
   }  
   else
   {
      while ( it != people.end())
      {
         if((*it).uSurname < nPerson.uSurname)
         {
            it++;
         }
         else if ((*it).givenName < nPerson.givenName && (*it).uSurname == nPerson.uSurname )
         {
            it++;
         }
         else if ((*it).bYear < nPerson.bYear && (*it).givenName == nPerson.givenName && (*it).uSurname == nPerson.uSurname)
         {
            it++;
         }
         else
         {
            break;
         }
      }        
      people.insert(it, nPerson);
   }
}

/************************************************************
* READFILE
* Reads the file into a List of People, and a second list to store
*  family relationships
*************************************************************/
void readFile(List<Person> &people, char fileName[], List<Person> &families)
{

	int pLoops = 0;
   Person nPerson;
   Person bPerson;
   Person nFamily;
   Person bFamily;
	ifstream fin;
   fin.open(fileName);
   string current;
   string line;
   while (!fin)
   {     
      cout << "Error reading file" << endl;
      cout << "Re-enter filename: ";
      cin >> fileName;
      fin.open(fileName);
   }
   while(fin >> current)
   {
   	if (current[0] == '@' && current[1] == 'I')
   	{
         pLoops++;
   		current.erase(0,1);
         current.erase((current.size() - 1), 1);
   		nPerson.individual = current;
   	}
      if (current == "GIVN")
      {
     		getline(fin, current);
         current = current.substr(1);
     		nPerson.givenName = current;
     		
     	}
     	if (current == "SURN")
     	{
     		getline(fin, current);
         current = current.substr(1);
     		nPerson.surname = current;
         current[0] = toupper(current[0]);
         nPerson.uSurname = current;
     	}
     	if (current == "BIRT")
     	{
         fin >> current;
         fin >> current;
     		if (current == "DATE")
     		{
        		fin >> current;
            if ( !isalpha(current[0]) && current.size() < 3 )
            {
            	nPerson.bDay = current;

            	fin >> current;
            }
            if ( isalpha(current[0]) )
            {
            	nPerson.bMonth = current;
            	fin >> current;
            }
            if (current.size() >= 4)
            {	
            	nPerson.bYear = current;
            }
         }    		
     	}
     	if (current == "FAMS")
     	{
     	   getline(fin, current);
         current = current.substr(1);
         current.erase(0,1);
         current.erase((current.size() - 1), 1);
     	   nPerson.family1 = current;
     	}
     	if (current == "FAMC")
     	{
     	   getline(fin, current);
         current = current.substr(1);
         current.erase(0,1);
         current.erase((current.size() - 1), 1);
     	   nPerson.family2 = current;
     	}
      if (current == "SEX")
      {	
      	fin >> current;
      	nPerson.gender = current;
      }
      
        if (current == "TIME" && pLoops > 0)
      {
         sortInsert(nPerson, people);
         nPerson = bPerson;
      }
      if (current == "HUSB")
      {
         fin >> current;
         current.erase(0,1);
         current.erase((current.size() - 1), 1);
         nFamily.father = current;
      }
      if (current == "WIFE")
      {
         fin >> current;
         current.erase(0,1);
         current.erase((current.size() - 1), 1);
         nFamily.mother = current;
      }
      if (current == "CHIL")
      {
         fin >> current;
         current.erase(0,1);
         current.erase((current.size() - 1), 1);
         nFamily.individual = current;
         families.push_back(nFamily);
         nFamily = bFamily;
      }     
   }   
   fin.close();
}

/************************************************************
* MERGELIST
*  The Function merges the People List with the Family# in Family List
*************************************************************/
void mergeList(List<Person> &people, List<Person> &family)
{

   ListIterator<Person> it2 = family.begin();
   string temp;
   for (ListIterator<Person> it = people.begin(); it != people.end(); it++)
   {
      for (it2 = family.begin(); it2 != family.end(); it2++)
      {  
         temp = (*it2).individual;
         if ((*it2).individual == (*it).individual)
         {
            (*it).father = (*it2).father;
            (*it).mother = (*it2).mother;
            break;
         }
      }   
   }
}

/************************************************************
* WRITEFILE
*  This Function outputs the sorted family list to a File
*************************************************************/
void writeFile(List<Person> &people)
{
	ofstream fout;
	fout.open("sorted.dat");
	for (ListIterator<Person> it = people.begin(); it != people.end(); it++)
	{
		if ((*it).givenName != " ")
			fout << (*it).givenName;
		if ((*it).givenName != " " && (*it).surname != " ")
			fout << " ";
		if ((*it).surname != " ")
			fout << (*it).surname;
		if ((*it).bYear != " ")
			fout << ", b. ";
		if ((*it).bDay != " ")
			fout << (*it).bDay << " ";
		if ((*it).bMonth != " ")
			fout << (*it).bMonth << " ";
		if ((*it).bYear != " ")
			fout << (*it).bYear;
		fout << endl;
	}

}

/***********************************************************************
* CREATETREE
* This function takes a BinaryNode & a List of People to create the 
*  family tree
************************************************************************/
void createTree(BinaryNode<Person> *child, List<Person> &people)
{
	for (ListIterator<Person> it = people.begin(); it != people.end(); it++)
	{
		if ((*it).individual == child->data.father)
		{
			child->addLeft((*it));
			people.remove(it);
		}
		if ((*it).individual == child->data.father)
		{
			child->addRight((*it));
			people.remove(it);
		}
		if(child->pLeft != NULL && child->pRight != NULL)
		{
			break;
		}
	}
	if(child->pLeft != NULL)
	{
		createTree(child->pLeft, people);
	}
	if(child->pRight != NULL)
	{
		createTree(child->pRight, people);
	}
}

/************************************************************
* DISPLAYGENERATIONS
*  Prints the current Generation count to the console
*************************************************************/
void displayGenerations(int generations)
{
   if (generations == -2)
      cout << "The Ancestors of ";
   else if (generations == -1)
      cout << "Parents:\n";
   else if (generations == 0)
      cout << "Grandparents:\n";
   else if (generations == 1)
      cout << "Great Grandparents:\n";
   else if (generations == 2)
      cout << "2nd Great Grandparents:\n";
   else if (generations == 3)
      cout << "3rd Great Grandparents:\n";
   else
      cout << generations << "th Great Grandparents:\n";
}

/************************************************************
* LEVEL
* Displays the family Tree
*************************************************************/
void level(BinaryNode<Person> * genealogy)
{
  const int MAX = 100;
  BinaryNode<Person> *queue[MAX];
  BinaryNode<Person> *temp;
  int front = 0;
  int back = 0;
  int generations = -2;


  queue[back++] = genealogy;
  int setBack = back;
  while (front != back)
  {
    temp = queue[front];
    front = (front + 1) % MAX;
   if (front == setBack)
   {
      displayGenerations(generations);
      generations++;
   }
   if (temp != NULL)
   {
      // visit
      if (front == 1 && generations == -1)
      {
         cout << temp->data.givenName 
              << " " << temp->data.surname << ":\n";
      }
      else
      {
         display(temp->data);
      }
      // end Visit        
      queue[back] = temp->pLeft;
      back = (back + 1) % MAX;
      if (front == setBack)
      {
        setBack = back;   
      }
      queue[back] = temp->pRight;
      back = (back + 1) % MAX;

    }
  }
}

/************************************************************
* MAIN
*  The Entry point and driver for the Program
*************************************************************/
int main(int argc, const char* argv[])
{	
	List<Person> people;
   List<Person> families;
	char fileName[50];
	if (argc == 1)
	{
		cout << "Enter file to display: ";
		cin >> fileName;
	}
	else if (argc == 2)
	{
		strcpy(fileName,argv[1]);
	}

	readFile(people, fileName, families);
	writeFile(people);
   mergeList(people, families);
	BinaryNode<Person> * genealogy = new BinaryNode<Person>;
	for (ListIterator<Person> it = people.begin(); it != people.end(); it++)
	{
		if ((*it).individual == "I1")
		{
	 		genealogy->data = *it;
	 		break;
		}
	}

   
   createTree(genealogy, people);
   cout << "tree size" << genealogy->size() << endl;
   level(genealogy);

   delete [] people;
   delete [] families;





}