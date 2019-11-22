#include <string>
OBJS 	= main.o readFunctions.o vector.o printFunctions.o  initialization.o metrics.o
SOURCE	= main.cpp readFunctions.cpp vector.cpp printFunctions.cpp initialization.cpp metrics.cpp
HEADER  = curveStructs.h readFunctions.h vector.h printFunctions.h initialization.h clusterStructs.h metrics.h
OUT  	= cluster
FLAGS   = -g -c
CC	= g++

all: $(OBJS)
	$(CC)  -g $(OBJS) -o $(OUT)
# create/compile the individual files >>separately<<
main.o: main.cpp
	$(CC)  $(FLAGS) main.cpp
readFunctions.o: readFunctions.cpp
	$(CC)  $(FLAGS) readFunctions.cpp
initialization.o: initialization.cpp
	$(CC)  $(FLAGS) initialization.cpp
vector.o: vector.cpp
	$(CC)  $(FLAGS) vector.cpp
metrics.o: metrics.cpp
	$(CC)  $(FLAGS) main.cpp	
printFunctions.o: printFunctions.cpp
	$(CC)  $(FLAGS) printFunctions.cpp
clean:
	rm -f $(OBJS) $(OUT)

# do a bit of accounting
count:
	wc $(SOURCE) $(HEADER)
