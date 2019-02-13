###############################################################
# Program:
#     Week 07, LIST
#     Brother Ercanbrack, CS235
# Author:
#     James Call
# Summary:
#     The creation of a list function, and the implementation in a
#        fibonacci number
# Time:
#     28 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: list.h week07.o fibonacci.o
	g++ -o a.out week07.o fibonacci.o
	tar -cf week07.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week07.o       : the driver program
#      fibonacci.o    : the logic for the fibonacci-generating function
#      <anything else?>
##############################################################
week07.o: list.h week07.cpp node.h
	g++ -c -g week07.cpp

fibonacci.o: fibonacci.h fibonacci.cpp list.h node.h
	g++ -c -g fibonacci.cpp

