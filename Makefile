OBJS 	= main.o readFunctions.o vector.o
SOURCE	= main.cpp readFunctions.cpp	vector.cpp
HEADER  =readFunctions.h	vector.h
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
vector.o: vector.cpp
	$(CC)  $(FLAGS) vector.cpp
clean:
	rm -f $(OBJS) $(OUT)

# do a bit of accounting
count:
	wc $(SOURCE) $(HEADER)
