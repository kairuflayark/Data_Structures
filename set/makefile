###############################################################
# Program:
#     Week 05, SET
#     Brother Ercanbrack, CS235
# Author:
#     James Call
# Summary:
#     Create a Set ADT and implement it to create a short game of 
#		Go Fish!
# Time:
#     7.5 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week05.o goFish.o card.o
	g++ -o a.out week05.o goFish.o card.o
	tar -cf week05.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week05.o       : the driver program
#      goFish.o       : the logic for the goFish game
#      card.o         : a single playing card
##############################################################
week05.o: set.h goFish.h week05.cpp
	g++ -c week05.cpp -g

goFish.o: set.h goFish.h goFish.cpp card.h
	g++ -c goFish.cpp -g

card.o: card.h card.cpp
	g++ -c card.cpp -g
