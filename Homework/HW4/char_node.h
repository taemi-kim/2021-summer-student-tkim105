//char_node.h

#ifndef CHAR_NODE_H
#define CHAR_NODE_H

class char_node {

 private:

  int       data;  //the payload stored in this node
  char_node* next;  //the pointer to node after this one

 public:

  //constructors
  char_node(int value): data(value), next(nullptr) { }
  char_node(int value, char_node* ptr): data(value), next(ptr) { }

  //getters
  int get_data() const         { return data; }
  char_node* get_next() const   { return next; }

  //setters
  void set_data(int value)     { data = value; }
  void set_next(char_node* ptr) { next = ptr; }

};

#endif
