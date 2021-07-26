CXX = g++
CXXFLAGS = -g -Wall -Wextra -pedantic -std=c++11

DQueueTest : DQueueTest.o DQueue.o
	$(CXX) -o DQueueTest DQueueTest.o DQueue.o

TDQueueTest : TDQueueTest.o TDQueue.o
	$(CXX) -o TDQueueTest TDQueueTest.o TDQueue.o

DQueueTest.o : DQueueTest.cpp DQueue.h
	$(CXX) $(CXXFLAGS) -c DQueueTest.cpp -o DQueueTest.o

DQueue.o : DQueue.cpp DQueue.h
	$(CXX) $(CXXFLAGS) -c DQueue.cpp -o DQueue.o

TDQueueTest.o : TDQueueTest.cpp TDQueue.h
	$(CXX) $(CXXFLAGS) -c TDQueueTest.cpp -o TDQueueTest.o

TDQueue.o : TDQueue.inc TDQueue.h
	$(CXX) $(CXXFLAGS) -c TDQueue.inc -o TDQueue.o
