###############################################################
# Program:
#     Lesson 04, DEQUE
#     Brother Helfrich, CS235
# Author:
#     <Jacob Casperson & Justin Stucki>
# Summary:
#     <This program demonstrates how a deque works using a
#      series of test functions and a program that emulates
#      a waiting list>
# Time:
#     <12.5 hrs>
###############################################################

##############################################################
# The main rule
##############################################################
a.out: deque.h lesson04.o nowServing.o
	g++ -o a.out lesson04.o nowServing.o
	tar -cf lesson04.tar *.h *.cpp makefile

##############################################################
# The individual components
#      lesson04.o     : the driver program
#      nowServing.o   : the logic for the now serving program
##############################################################
lesson04.o: deque.h lesson04.cpp
	g++ -c lesson04.cpp

nowServing.o: nowServing.h nowServing.cpp deque.h
	g++ -c nowServing.cpp
