###############################################################
# Program:
#     Week 09, Binary Search Tree
#     Brother Ercanbrack, CS235
# Author:
#     James Call
# Summary:
#     this code contains a Binary search tree and an implementation
#		of it in a sorting function
# Time:
#     6.5 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week09.o
	g++ -o a.out week09.o 
	tar -cf week09.tar *.h *.cpp makefile

##############################################################
# The individual components
#      lesson08.o     : the driver program
##############################################################
week09.o: bnode.h bst.h stack.h week09.cpp sortBinary.h
	g++ -c week09.cpp

