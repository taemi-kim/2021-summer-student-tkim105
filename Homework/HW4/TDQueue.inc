template< typename T >
//Default constructor
TDQueue<T>::TDQueue(): size(0),_head(nullptr),_tail(nullptr) { }

template<typename T>
//An alternate constructor
TDQueue<T>::TDQueue(T& val) : size(1),_head(new _Node({val,nullptr,nullptr})),_tail(_head) { }

template<typename T>
//A copy constructor
TDQueue<T>::TDQueue(const TDQueue& rhs) : TDQueue() {//use default constructor to initialize node
   _Node* cur = rhs._head; //assigning current pointer to thing I want to copy
   while (cur) {
     operator<<(cur->data);
     cur = cur->next;
   }
}

template<typename T>
//Overloading operators                                                                                          
TDQueue<T>& TDQueue<T>::operator<<(T& val) {
   _Node* new_node = new _Node({val,nullptr,nullptr});
    if(!_head) { //if the dQueue is empty                                                                         
     _head = new_node;
     _tail = new_node;
     size++;
     return *this;
   }
    //updates the linkages                                                                                        
   _tail->next = new_node;
   new_node->prev = _tail;
   new_node->next = nullptr;
   _tail = new_node;
   size++;
   return *this;
  }

template<typename T>
TDQueue<T>& TDQueue<T>::operator<(T& val) {
  _Node* new_node = new _Node({val,nullptr,nullptr});
    if(!_tail) { //if the dQueue is empty                                                                         
     _tail = new_node;
     _head = new_node;
     size++;
     return *this;
  }
  //updates the linkages                                                                                         
    _head->prev = new_node;
   new_node->next = _head;
   new_node->prev = nullptr;
   _head = new_node;
   size++;
   return *this;
  }

template<typename T>
TDQueue<T>& TDQueue<T>:: operator=(const TDQueue<T>& rhs) {
   if (this != &rhs) {
    clear(); //release current set                                                                               
    _Node* cur1 = rhs._head;
    while (cur1) {
      operator<<(cur1->data);
      cur1 = cur1->next;
    }
  }
  return *this;
}

template<typename T>
//Destructor                                                                                                     
TDQueue<T>::~TDQueue() {
  clear();

}

template<typename T>
void TDQueue<T>::clear() {
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

template<typename T>
//Removes last element in the dQueue                                                                             
TDQueue<T>& TDQueue<T>::operator>>(T& val) {
  _Node* cur = _tail;
  if (!cur) {
    return *this;
  }
  else {
    _Node* temp = cur;
    val = cur->data;
    cur->data = ' ';
    _tail = cur->prev;
    _tail->next = nullptr;
    delete temp;
  }
  return *this;
}

template<typename T>
//Removes first element in the dQueue                                                                           
TDQueue<T>& TDQueue<T>::operator>(T& val) {
  _Node* cur = _head;
  if (!cur) {
    return *this;
  }
  else {
    _Node* temp = cur;                                                                              
    val = cur->data;
    cur->data = ' ';
    _head = cur->next;
    _head->prev = nullptr;
    delete temp;
    
  }
  return *this;
}

template<typename T>
bool TDQueue<T>::operator==(const TDQueue<T>& rhs) const {
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

template<typename T>
TDQueue<T> TDQueue<T>::operator+(const TDQueue<T>& rhs) const {
 TDQueue<T> result(*this); //copy constructor                                                                     
 _Node* cur = rhs._head;
 while(cur) {
   result << cur->data; //concatenates at the tail                                                                
   cur = cur->next;
  }
  return result;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const TDQueue<T>& q) {
    if (q.size == 0) {
      os << "empty queue\n";
    }
    else {
      TDQueue<T>::_Node* cur = q._head;
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