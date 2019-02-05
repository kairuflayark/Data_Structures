/***********************************************************************
 * Module:
 *    Week 12, Spell Check
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/

#ifndef SPELL_CHECK_H
#define SPELL_CHECK_H

#include "hash.h"

/****************************************
 * S HASH
 * A simple hash of integers
 ****************************************/
class SHash : public Hash <string>
{
public:
   SHash(int numBuckets)    throw (const char *) : Hash <string> (numBuckets) {}
   SHash(const SHash & rhs) throw (const char *) : Hash <string> (rhs)        {}

   // hash function for integers is simply to take the modulous
   int hash(const string & word) const;
};

void spellCheck();

#endif // SPELL_CHECK_H
