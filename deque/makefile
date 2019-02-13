###############################################################
# Program:
#     Week 04, DEQUE
#     Brother Ercanbrack, CS235
# Author:
#     James Call
# Summary:
#     Create a Deque and implement it into a Now serving line
# Time:
#  	  3 hours  
###############################################################

##############################################################
# The main rule
##############################################################
a.out: deque.h week04.o nowServing.o
	g++ -o a.out week04.o nowServing.o
	tar -cf week04.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week04.o       : the driver program
#      nowServing.o   : the logic for the now serving program
##############################################################
week04.o: deque.h week04.cpp
	g++ -c week04.cpp

nowServing.o: nowServing.h nowServing.cpp deque.h
	g++ -c nowServing.cpp
 