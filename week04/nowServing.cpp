/***********************************************************************
 * Implementation:
 *    NOW SERVING
 * Summary:
 *    This will contain the implementation for nowServing() as well as any
 *    other function or class implementations you may need
 * Author
 *    James Call
 **********************************************************************/

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>       // for STRING
#include <cassert>      // for ASSERT
#include "nowServing.h" // for nowServing() prototype
#include "deque.h"      // for DEQUE
using namespace std;


/***************************************
* DISPLAY
* The function that displays the information
*  of the person currently being served
***************************************/
void display(Person & current)
{
		// handle emergency
		if (current.emergency == true)
		{
			cout  << "\tEmergency for " 
					<< current.name
					<< " for class "
					<< current.course
					<< ". Time left: "
					<< current.minutes << endl;				
		}
		// handle regular people in the line
		else
		{
			cout  << "\tCurrently serving " 
					<< current.name
					<< " for class "
					<< current.course
					<< ". Time left: "
					<< current.minutes << endl;
		}
		current.minutes = current.minutes - 1;
}




/************************************************
 * NOW SERVING
 * The interactive function allowing the user to
 * handle help requests in the Linux lab
 ***********************************************/
void nowServing()
{
   // instructions
   cout << "Every prompt is one minute.  The following input is accepted:\n";
   cout << "\t<class> <name> <#minutes>    : a normal help request\n";
   cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
   cout << "\tnone                         : no new request this minute\n";
   cout << "\tfinished                     : end simulation\n";

   // My code here
   // create the necessary items
   Deque <Person> line;
   string first;
   Person nPerson;
   int time = 0;
   Person current;
   current.minutes = 0;
   try
	{   
	   do
	   {
	   	cin.clear();
	   	cout << "<" << time << "> ";
	   	cin >> first;
	   	// handle emergency
	   	if (first == "!!")
	   	{
	   		cin >> nPerson.course;
	   		cin >> nPerson.name;
	   		cin >> nPerson.minutes;
	   		nPerson.emergency = true;
	   		line.push_front(nPerson);
	   	}

	   	// handle customers
	   	else if (first[0] == 'C' || first[0] == 'c')
			{
	   		nPerson.course = first;
	   		cin >> nPerson.name;
	   		cin >> nPerson.minutes;
	   		nPerson.emergency = false;
	   		line.push_back(nPerson);
			}
	   	// handle no new customers
	   	else if (first == "none")
	   	{

	   	}

	   	// break loop
	   	else if (first == "finished")
	   		break;

	   	else
	   	{
	   		cout << "Invalid input. Please retry.\n";
	   		cin.ignore();
	   	}

	   	// sets the current person at the front of the line
	   	if (current.minutes == 0 && !line.empty())
	   		{
	   		current = line.front();
	   		line.pop_front();
	   		}

	   	// displays the currently served person
	   	if (current.minutes != 0)
	   		display(current);
   		time++;
   	}
   	while (first != "finished");
   }
  	catch (const char * error)
  	{
      	cout << error << endl;
   	}

   // end
   cout << "End of simulation\n";
}


