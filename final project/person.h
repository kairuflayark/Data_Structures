
#include <string>
#include <cstring>
#include <cctype>
using namespace std;

#ifndef PERSON_H
#define PERSON_H


/************************************************************
* PERSON
* A class to contain a person in an attempt to solve my 
* string::assign() issues.  With no Luck.
**************************************************************/
class Person
{
public:
	Person();
	Person(const Person & rhs); 
	Person & operator=(const Person & rhs);

   string surname;
   string uSurname;
   string givenName;
   string bDay;
   string bMonth;
   string bYear;
   string individual;
   string family1;
   string family2;
   string gender;
   string father;
   string mother;


};

/************************************************************
* PERSON::Default Constructor
* initializes the Person Class
*************************************************************/
Person::Person()
{
	surname = " ";
	uSurname = " ";
	givenName = " ";
	bDay = " ";
	bMonth = " ";
	bYear = " ";
	individual = " ";
	family1 = " ";
	family2 = " ";
	gender = " ";
	father = " ";
	mother = " ";

}

/************************************************************
* PERSON::COPY CONSTRUCTOR
* 
*************************************************************/
Person::Person(const Person & rhs)
{
   surname = rhs.surname;
   uSurname = rhs.uSurname;
   givenName = rhs.givenName;
   bDay = rhs.bDay;
   bMonth = rhs.bMonth;
   bYear = rhs.bYear;
   individual = rhs.individual;
   family1 = rhs.family1;
   family2 = rhs.family2;
   gender = rhs.gender;
   father = rhs.father;
   mother = rhs.mother;
}

/************************************************************
* PERSON:: ASSIGNMENT OPERATOR
*
*************************************************************/
Person & Person::operator=(const Person & rhs)
{
   surname = rhs.surname;
   uSurname = rhs.uSurname;
   givenName = rhs.givenName;
   bDay = rhs.bDay;
   bMonth = rhs.bMonth;
   bYear = rhs.bYear;
   individual = rhs.individual;
   family1 = rhs.family1;
   family2 = rhs.family2;
   gender = rhs.gender;
   father = rhs.father;
   mother = rhs.mother;
   return *this;
}


#endif