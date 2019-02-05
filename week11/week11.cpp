/***********************************************************************
* Program:
*    Week 11, Sorting
*    Brother Ercanbrack, CS 235
* Author:
*    James Call
* Summary: 
*    Driver program for the heap and merge sorts
************************************************************************/

#include <iostream>        // for CIN and COUT
#include <cstring>         // for strcmp
#include <iomanip>         // for SETW
#include "heap.h"
#include "merge.h"
#include <fstream>

using namespace std;

/********************************************************
* DISPLAY
* Displays the Sorted Heap
*********************************************************/
void display(vector<int> &data)
{
   int printCount = 0;
   vector<int>::iterator it = data.begin();
   it++;
   for (it; it != data.end(); it++)
   {
      cout << setw(3) << *it;
      printCount++;
      if (printCount == 10)
      {
         cout << endl;
         printCount = 0;
      }
   }
}
/********************************************************
* DISPLAY
* Displays the Sorted List
*********************************************************/
void display(list<int> &data)
{
   int printCount = 0;
   while (!data.empty())
   {
      cout << setw(3) << data.front();
      data.pop_front();
      printCount++;
      if (printCount == 10)
      {
         cout << endl;
         printCount = 0;
      }

   }
}

/**********************************************************************
 * MAIN
 * Gets the sort type and filename from the command line. If the sort type
 * or filename are not entered on the command line, the user will be
 * prompted for the sort type and/or filename.
 * Call the appropriate sort to sort the data contained in the vector or
 * linked list and display the sorted data to the console.
 ***********************************************************************/
int main(int argc, const char* argv[])
{
   char sortType[10];
   char fileName[50];
   int nData;
   if (argc == 1)
   {
      cout << "Which sort merge or heap? ";
      cin >> sortType;
      cout << "Enter name of file to sort: ";
      cin >> fileName;
   }
   else if (argc == 2)
   {
      strcpy(sortType,argv[1]);
      cout << "Enter name of file to sort: ";
      cin >> fileName;
   }
   else if (argc == 3)
   {
      strcpy(sortType,argv[1]);    
      strcpy(fileName,argv[2]);
   }
   
   if (strcmp(sortType, "heap") == 0)
   {
      vector<int> data;
      ifstream fin;
      fin.open(fileName);
      if (!fin)
      {
         
         cout << "Error reading file" << endl;
      }
      else
      {
         data.push_back(0);
         while(fin >> nData)
         {
            data.push_back(nData);
         }
      }
      fin.close();
      heapSort(data);
      display(data);
         // TO DO: read the file into a vector
         //        call your heapsort passing the vector as a parameter
         //        output the sorted vector to the console.
   }
   else if (strcmp(sortType, "merge") == 0)
   {
      list<int> data;
      ifstream fin;
      fin.open(fileName);
      if (!fin)
      {
         
         cout << "Error reading file" << endl;
      }
      else
      {
         while(fin >> nData)
         {
            data.push_back(nData);
         }
      }
      fin.close();
      mergeSort(data);
      display(data);
         // TO DO: read the file into a linked list
         //        call your natural merge sort
         //        output the sorted linked list to the console.
   }
   else
   {
      cout << "\nInvalid sort name - must be 'heap' or 'merge'" << endl;
   }
   
   return 0;
}
