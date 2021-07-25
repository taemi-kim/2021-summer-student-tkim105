CXX = g++
CXXFLAGS = -g -Wall -Wextra -pedantic -std=c++11

DQueueTest : DQueueTest.o DQueue.o
	$(CXX) -o DQueueTest DQueueTest.o DQueue.o

DQueueTest.o : DQueueTest.cpp DQueue.h
	$(CXX) $(CXXFLAGS) -c DQueueTest.cpp -o DQueueTest.o

DQueue.o : DQueue.cpp DQueue.h
	$(CXX) $(CXXFLAGS) -c DQueue.cpp -o DQueue.o
