#include "DQueue.h"
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <queue>

  //The default constructor
DQueue::DQueue(): size(0),_head(nullptr),_tail(nullptr) { }  //*_head? *_tail?

  //An alternate constructor
DQueue::DQueue(const char& ch) : size(1),_head(new _Node({ch,nullptr,nullptr})),_tail(_head) { }

  //A copy constructor
  DQueue::DQueue(const DQueue& rhs) : DQueue() {//use default constructor to initialize node
    _Node* cur = rhs._head; //assigning current pointer to thing I want to copy
    while (cur) {
      operator<<(cur->data);
      cur = cur->next;
    }
  }
  
  //Overloading operators
  DQueue& DQueue::operator<<(const char& ch) {
    //takes an input character
    //adds it to the tail DQueue
    //allocates memory for the new node
    //return reference to the DQueue object

    _Node* new_node = new _Node({ch,nullptr,nullptr});
    /*if(!ch) { //allocation failed
      return false;
    }*/

    if(!_head) { //if the dQueue is empty
      _head = new_node;
      _tail = new_node;
      size++; 
      return *this;
    }

    /*if(ch < _head->get_data()) {
      new_node->set_next(_head);
      _head = new_node;
      size++;
      return true;
    }
    
    cur = _head;
    while (cur->next && (cur->next->data < ch)) {
      cur = cur->next;
    }*/
    _tail->next = new_node;
    new_node->prev = _tail;
    new_node->next = nullptr;
    _tail = new_node;
    size++;
    return *this;
  }

  DQueue& DQueue::operator<(const char& ch) {
    //takes an input character
    //adds it to the head DQueue
    //allocates memory for the new node
    //updates the linkages
    //returns A reference to the DQueue object

    _Node* new_node = new _Node({ch,nullptr,nullptr});

    if(!_tail) { //if the dQueue is empty                                                                        
      _tail = new_node;
      _head = new_node;
      size++;                                                                                                     
      return *this;
    }
    /*
    if(ch > _tail->data) {
      new_node->prev = _tail;
      _tail = new_node;
      size++;
      return true;
    }

    cur	= _tail;
    while (cur->prev && (cur->prev->data > ch)) {
      cur = cur->prev;
      }*/
     _head->prev = new_node;
    new_node->next = _head;
    new_node->prev = nullptr;
    _head = new_node;
    size++;
    return *this;
  }
  
  DQueue& DQueue:: operator=(const DQueue& rhs) {
    if (this != &rhs) {
      clear(); //release current set
      _Node* cur1 = rhs._head;
      while (cur1) {
	operator<<(cur1->data);
	cur1 = cur1->next;
	/*
	add(cur->get_data()); 
        cur = cur->get_next();*/
	
      }
    }
    return *this;
  }

  //Destructor
  DQueue::~DQueue() {
    clear();

  }
  
  //Removing all items
  void DQueue::clear() {
    //deallocate all nodes in the list
    _Node* cur = _head;
    while (cur) {
      _Node* temp = cur;
      cur = cur->next;
      delete temp;
      
    }
    _head = nullptr;
    size = 0;
  }

  //Removes last element in the dQueue
  DQueue& DQueue::operator>>(char& ch) {
    _Node* cur = _tail;
    if (!cur) {
      return *this;
    }
    else {
      _Node* temp = cur; //necessary?
      ch = cur->data;
      cur->data = ' ';
      _tail = cur->prev;
      _tail->next = nullptr;
      delete temp; //or cur?
    }
    return *this;
  }

   //Removes first element in the dQueue                                                                             
  DQueue& DQueue::operator>(char& ch) {
    _Node* cur = _head;
    if (!cur) {
      return *this;
    }
    else {
      _Node* temp = cur; //necessary?                                                                             
      ch = cur->data;
      cur->data = ' ';
      _head = cur->next;
      _head->prev = nullptr;
      delete temp; //or cur?                                                                                       
    }
    return *this;
  }

bool DQueue::operator==(const DQueue &rhs) const {
    if (this != &rhs) {                                                                            
      if (rhs.size != this->size) return false;
      
      _Node* cur1 = rhs._head;
      _Node* cur2 = this->_head;
      
      while(cur1 != nullptr && cur2 != nullptr && cur1->data == cur2->data) {
	cur1 = cur1->next;
	cur2 = cur2->next;
      }
      if(cur1 == nullptr && cur2 == nullptr) { //if it reached the end of the queue
	return true;
      }
      else {return false;}
    }
    return true;
  }

DQueue DQueue::operator+(const DQueue& rhs) const {
  DQueue result(*this); //copy constructor
  _Node* cur = rhs._head;
  while(cur) {
    result << cur->data; //concatenates at the tail
    cur = cur->next;
  }
  return result;   
  }

  std::ostream& operator<<(std::ostream& os, const DQueue& q) {
    if (q.size == 0) {
      os << "empty queue\n";
    }
    else {
      DQueue::_Node* cur = q._head;
      while(cur) {
	os << cur->data;
	if (cur->next == nullptr) {
	  os << std::endl;
	}
	else {
	  os << " -> ";
	}
	cur = cur->next;
      }
    }
    return os; 
  }
