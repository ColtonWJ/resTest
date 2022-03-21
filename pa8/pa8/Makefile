#------------------------------------------------------------------------------
#  Makefile for Dictionary ADT
#
#  make                      makes Order
#  make DictionaryClient     make DictionaryClient
#  make clean                removes binary files
#  make check1               runs valgrind on DictionaryClient
#  make check2               runs valgrind on Order with CLA 35
#------------------------------------------------------------------------------

Order : Order.o Dictionary.o
	g++ -std=c++17 -Wall -o Order Order.o Dictionary.o 

Order.o : Dictionary.h Order.cpp
	g++ -std=c++17 -Wall -c Order.cpp

DictionaryClient : DictionaryClient.o Dictionary.o
	g++ -std=c++17 -Wall -o DictionaryClient DictionaryClient.o Dictionary.o 

DictionaryClient.o : Dictionary.h DictionaryClient.cpp
	g++ -std=c++17 -Wall -c DictionaryClient.cpp

DictionaryTest : DictionaryTest.o Dictionary.o
	g++ -std=c++17 -Wall -o DictionaryTest DictionaryTest.o Dictionary.o

DictionaryTest.o : Dictionary.h DictionaryTest.cpp
	g++ -std=c++17 -Wall -c DictionaryTest.cpp

Dictionary.o : Dictionary.h Dictionary.cpp
	g++ -std=c++17 -Wall -c Dictionary.cpp

clean :
	rm -f Order Order.o DictionaryClient DictionaryClient.o Dictionary.o

check1 : DictionaryClient
	valgrind --leak-check=full DictionaryClient

check2 : Order
	valgrind --leak-check=full Order 

checkL : DictionaryTest
	valgrind --leak-check=full DictionaryTest
