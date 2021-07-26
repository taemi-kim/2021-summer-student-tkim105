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
  TDQueue<T>();

  //Alternate constructor
  TDQueue<T>(T& val);

  //Copy constructor
  TDQueue<T>(const TDQueue& rhs);

  //Overloaded operator =
  TDQueue<T>& operator=(const TDQueue& rhs);

  //Destructor
  ~TDQueue<T>();

  //Overloaded operator <<
  TDQueue<T>& operator<<(T& val);

  //Overloaded operator >>
  TDQueue<T>& operator>>(T& val);

  //Overloaded operator <
  TDQueue<T>& operator<(T& val);

  //Overloaded operator >
  TDQueue<T>& operator>(T& val);

  //Overloaded operator ==
  bool operator==(const TDQueue<T>&rhs) const;

  //Overloaded operator +
  TDQueue<T> operator+(const TDQueue<T>& rhs) const;

  //Overloaded output stream operator <<
  friend std::ostream& operator<<(std::ostream& os, const TDQueue<T>& q);
  
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
