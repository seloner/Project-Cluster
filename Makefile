OBJS 	= main.o readFunctions.o vector.o printFunctions.o  initialization.o metrics.o assignment.o curves.o dtw.o update.o combinations.o
SOURCE	= main.cpp readFunctions.cpp vector.cpp printFunctions.cpp initialization.cpp metrics.cpp assignment.cpp curves.cpp dtw.cpp update.cpp combinations.cpp
HEADER  = readFunctions.h vector.h printFunctions.h initialization.h clusterStructs.h metrics.h assignment.h curves.h dtw.h update.h combinations.h
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
printFunctions.o: printFunctions.cpp
	$(CC)  $(FLAGS) printFunctions.cpp

initialization.o: initialization.cpp
	$(CC)  $(FLAGS) initialization.cpp
assignment.o: assignment.cpp
	$(CC)  $(FLAGS) assignment.cpp

vector.o: vector.cpp
	$(CC)  $(FLAGS) vector.cpp
curves.o: curves.cpp
	$(CC)  $(FLAGS) curves.cpp
update.o: update.cpp
	$(CC)  $(FLAGS) update.cpp

metrics.o: metrics.cpp
	$(CC)  $(FLAGS) metrics.cpp
dtw.o: dtw.cpp
	$(CC)  $(FLAGS) dtw.cpp
combinations.o: combinations.cpp
	$(CC)  $(FLAGS) combinations.cpp
clean:
	rm -f $(OBJS) $(OUT)

# do a bit of accounting
count:
	wc $(SOURCE) $(HEADER)
