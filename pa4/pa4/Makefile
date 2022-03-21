#------------------------------------------------------------------------------
#  Makefile for CMPS 101 Programming Assignment 2
#
#  make                     makes Sparse
#  make ListTest            makes ListTest
#  make MatrixClient         makes MatrixClient
#  make clean               removes binaries
#  make checkFind           tests Sparse for memory leaks on in7
#  make checkClient         tests MatrixClient for memory leaks
#  make checkTest           tests MatrixTest for memory leaks
#------------------------------------------------------------------------------

BASE_SOURCES   = Matrix.c List.c
BASE_OBJECTS   = Matrix.o List.o
HEADERS        = Matrix.h List.h
COMPILE        = gcc -std=c17 -Wall -c
LINK           = gcc -std=c17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

Sparse : Sparse.o $(BASE_OBJECTS)
	$(LINK) Sparse Sparse.o $(BASE_OBJECTS)

MatrixClient : MatrixClient.o $(BASE_OBJECTS)
	$(LINK) MatrixClient MatrixClient.o $(BASE_OBJECTS)

MatrixTest : MatrixTest.o $(BASE_OBJECTS)
	$(LINK) MatrixTest MatrixTest.o $(BASE_OBJECTS)

ListTest : ListTest.o $(BASE_OBJECTS)
	$(LINK) ListTest ListTest.o $(BASE_OBJECTS)

Sparse.o : Sparse.c $(HEADERS)
	$(COMPILE) Sparse.c

MatrixClient.o : MatrixClient.c $(HEADERS)
	$(COMPILE) MatrixClient.c

MatrixTest.o : MatrixTest.c $(HEADERS)
	$(COMPILE) MatrixTest.c

ListTest.o : ListTest.c $(HEADERS)
	$(COMPILE) ListTest.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean :
	$(REMOVE) Sparse MatrixClient Sparse.o MatrixClient.o $(BASE_OBJECTS)

checkFind : Sparse
	$(MEMCHECK) Sparse in6 out6.txt

checkClient : MatrixClient
	$(MEMCHECK) MatrixClient


checkTest : MatrixTest
	$(MEMCHECK) MatrixTest

checkList : ListTest
	$(MEMCHECK) ListTest
