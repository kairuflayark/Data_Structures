/***********************************************************************
 * Header:
 *    NOW SERVING
 * Summary:
 *    This will contain just the prototype for nowServing(). You may
 *    want to put other class definitions here as well.
 * Author
 *    <your names here>
 ************************************************************************/

#ifndef NOW_SERVING_H
#define NOW_SERVING_H

#include "deque.h"     // for DEQUE
#include <string>

struct Person
{
	std::string course;
	std::string name;
	int minutes;
	bool emergency;
};
// the interactive nowServing program
void nowServing();
void display(Deque <Person> & line);

#endif // NOW_SERVING_H

