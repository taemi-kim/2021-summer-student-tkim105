//TDQueue.h
#ifndef __TDQUEUE_H__
#define __TDQUEUE_H__

#include <iosfwd>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <queue>

template<typename T>
class TDQueue {
 public:

  //Default constructor
  TDQueue();

  //Alternate constructor
  TDQueue(T& ch);

  //Copy constructor
  TDQueue(const TDQueue& rhs);

  //Overloaded operator =
  TDQueue& operator=(const TDQueue& rhs);

  //Destructor
  ~TDQueue();

  //Overloaded operator <<
  TDQueue& operator<<(T val);

  //Overloaded operator >>
  TDQueue& operator>>(T val);

  //Overloaded operator <
  TDQueue& operator<(T val);

  //Overloaded operator >
  TDQueue& operator>(T val);

  //Overloaded operator ==
  bool operator==(const TDQueue &rhs) const;

  //Overloaded operator +
  TDQueue operator+(const TDQueue& rhs) const;

  //Overloaded output stream operator <<
  friend std::ostream& operator<<(std::ostream& os, const TDQueue& q);
  
 private:
  friend struct TDQueueTest;
   struct _Node {
    char data;    ///< A character node data                                                                      
    _Node *next;  ///< A pointer to the next node. nullptr if it is the end node                                  
    _Node *prev;  ///< A pointer to the previous node. nullptr if it is the head node                             

  };

  void clear();
  int size;
  _Node *_head;   ///< a pointer to the head node of the DQueue                                                   
  _Node *_tail;   ///< a pointer to the tail node of the DQueue      

};

#include "TDQueue.inc"
#endif //__TDQUEUE_H__
