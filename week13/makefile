###############################################################
# Program:
#     Week 13, Genealogy
#     Brother Ercanbrack, CS235
# Author:
#     James Call
# Summary:
#     this code reads a user provided .ged file and creates a 
#		sorted file of their ancestors, as well as displaying the 
#       family tree.
#		I have been dealing with String::assign() segfault as well
#		as an string operator== segfault that I have been unable to solve
# Time:
#     23 Hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: list.h bnode.h bst.h node.h stack.h person.h week13.o
	g++ -o a.out week13.o 
	tar -cf week13.tar *.h *.cpp makefile

##############################################################
# The individual components
#      lesson08.o     : the driver program
##############################################################
week13.o: bnode.h bst.h list.h node.h stack.h person.h week13.cpp 
	g++ -c week13.cpp -g

