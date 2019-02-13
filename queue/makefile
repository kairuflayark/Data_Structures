###############################################################
# Program:
#     Week 03, QUEUE
#     Brother Ercanbrack, CS235
# Author:
#     James Call
# Summary:
#     Create a queue class and implement it as a way to track
#			the purchase and sale of stock
# Time:
#     11 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: queue.h week03.o dollars.o stock.o
	g++ -o a.out week03.o dollars.o stock.o
	tar -cf week03.tar *.h *.cpp makefile

dollarsTest: dollars.o dollarsTest.cpp
	g++ -o dollarsTest dollars.o dollarsTest.cpp

##############################################################
# The individual components
#      week03.o       : the driver program
#      dollars.o      : the Dollars class
#      stock.o        : the logic for the stock program
##############################################################
week03.o: queue.h week03.cpp
	g++ -c -g week03.cpp

dollars.o: dollars.h dollars.cpp
	g++ -c -g dollars.cpp

stock.o: stock.h stock.cpp queue.h
	g++ -c -g stock.cpp
