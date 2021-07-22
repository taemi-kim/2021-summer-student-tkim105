#include "DQueue.h"
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;

#ifndef ASSERT
#include <csignal>  // signal handler 
#include <cstring>  // memset
#include <string>
char programName[128];

void segFaultHandler(int, siginfo_t*, void* context) {
  char cmdbuffer[1024];
  char resultbuffer[128];
#ifdef __APPLE__
  sprintf(cmdbuffer, "addr2line -Cfip -e %s %p", programName,
      (void*)((ucontext_t*)context)->uc_mcontext->__ss.__rip);
#else
  sprintf(cmdbuffer, "addr2line -Cfip -e %s %p", programName,
      (void*)((ucontext_t*)context)->uc_mcontext.gregs[REG_RIP]);
#endif
  std::string result = "";
  FILE* pipe = popen(cmdbuffer, "r");
  if (!pipe) throw std::runtime_error("popen() failed!");
  try {
    while (fgets(resultbuffer, sizeof resultbuffer, pipe) != NULL) {
      result += resultbuffer;
    }
  } catch (...) {
    pclose(pipe);
    throw;
  }
  pclose(pipe);
  cout << "Segmentation fault occured in " << result;
#ifdef __APPLE__
  ((ucontext_t*)context)->uc_mcontext->__ss.__rip += 2;  // skip the seg fault
#else
  ((ucontext_t*)context)->uc_mcontext.gregs[REG_RIP] += 2;  // skip the seg fault
#endif
}

#define ASSERT(cond) if (!(cond)) { \
    cout << "failed ASSERT " << #cond << " at line " << __LINE__ << endl; \
  } else { \
    cout << __func__ << " - (" << #cond << ")" << " passed!" << endl; \
  }
#endif

/**
 * \struct DQueueTest
 * \defgroup DQueueTest
 * \brief Test cases for the DQueue class
 */
struct DQueueTest {
  /**
   * \brief A test function for default constructor
   */
  static void DefaultConstructorTest() {
    DQueue *q = new DQueue();
    // check if the structure is as expected
    ASSERT(q->_head == nullptr);
    delete q;
  }
   
  /**
   * \brief A test function for non-default constructor
   */
  static void NonDefaultConstructorTest() {
    DQueue *q = new DQueue('A');
    // check if the structure is as expected
    ASSERT(q->_head != nullptr);
    ASSERT(q->_head->next == nullptr);
    ASSERT(q->_head->data == 'A');
    delete q;
  }
  
  /**
   * \brief A test function for copy constructor
   */
  static void CopyConstructorTest() {
    DQueue *q = new DQueue('A');
    *q << 'B' << 'C';
    DQueue *r = new DQueue(*q);
    // check if the structure is as expected
    ASSERT(r->_head != nullptr);
    ASSERT(r->_head->next != nullptr);
    ASSERT(r->_head->data == 'A');
    ASSERT(r->_head->next->next != nullptr);
    ASSERT(r->_head->next->data == 'B');
    ASSERT(r->_head->next->next->next == nullptr);
    ASSERT(r->_head->next->next->data == 'C');
    delete r;
    delete q;
    cout << "Copy constructor tests passed" << endl;
  }
  
  /**
   * \brief A test function for assignment operator
   */
  static void OperatorAssignmentTest() {
    DQueue *q = new DQueue('A');
    *q << 'B' << 'C';
    DQueue *r = new DQueue('B');
    *r = *q;
    // check if the structure is as expected
    ASSERT(r->_head != nullptr);
    ASSERT(r->_head->next != nullptr);
    ASSERT(r->_head->data == 'A');
    ASSERT(r->_head->next->next != nullptr);
    ASSERT(r->_head->next->data == 'B');
    ASSERT(r->_head->next->next->next == nullptr);
    ASSERT(r->_head->next->next->data == 'C');
    delete r;
    delete q;
  }
  
  /**
   * \brief A test function for insertion operator
   */
  static void OperatorInsertionTest() {
    // create a queue A->B->C
    DQueue *q = new DQueue();
    *q << 'A' << 'B' << 'C';
    // check if the structure is as expected
    ASSERT(q->_head != nullptr);
    ASSERT(q->_head->next != nullptr);
    ASSERT(q->_head->data == 'A');
    ASSERT(q->_head->next->next != nullptr);
    ASSERT(q->_head->next->data == 'B');
    ASSERT(q->_head->next->next->next == nullptr);
    ASSERT(q->_head->next->next->data == 'C');
    delete q;
  }
  
  /**
   * \brief A test function for extraction operator
   */
  static void OperatorExtractionTest() {
    // create a queue A->B->C
    DQueue *q = new DQueue();
    char empty = -1;
    char empty_copy = empty;
    *q >> empty;
    ASSERT(empty == empty_copy);
    *q << 'A' << 'B' << 'C';
    // dequeue C and B
    char a, b;
    *q >> a >> b;
    ASSERT(a == 'C');
    ASSERT(b == 'B');
    // check if the structure is as expected
    ASSERT(q->_head != nullptr);
    ASSERT(q->_head->next == nullptr);
    ASSERT(q->_head->data == 'A');
    delete q;
  }
  
  /**
   * \brief A test function for smaller than operator
   */
  static void OperatorSmallerTest() {
    // create a queue C->B->A
    DQueue *q = new DQueue();
    *q < 'A' < 'B' < 'C';
    // check if the structure is as expected
    ASSERT(q->_head != nullptr);
    ASSERT(q->_head->next != nullptr);
    ASSERT(q->_head->data == 'C');
    ASSERT(q->_head->next->next != nullptr);
    ASSERT(q->_head->next->data == 'B');
    ASSERT(q->_head->next->next->next == nullptr);
    ASSERT(q->_head->next->next->data == 'A');
    delete q;
  }
  
  /**
   * \brief A test function for greater than operator
   */
  static void OperatorGreaterTest() {
    // create a queue A->B->C
    DQueue *q = new DQueue();
    char empty = -1;
    char empty_copy = empty;
    *q > empty;
    ASSERT(empty == empty_copy);
    *q << 'A' << 'B' << 'C';
    // dequeue A and B
    char a, b;
    *q > a > b;
    ASSERT(a == 'A');
    ASSERT(b == 'B');
    // check if the structure is as expected
    ASSERT(q->_head != nullptr);
    ASSERT(q->_head->next == nullptr);
    ASSERT(q->_head->data == 'C');
    delete q;
  }
  
  /**
   * \brief A test function for equality operator
   */
  static void OperatorEqualityTest() {
    // create two queues A->B->C
    DQueue *q = new DQueue();
    *q << 'A' << 'B' << 'C';
    DQueue *r = new DQueue();
    *r << 'A' << 'B' << 'C';
    // check if they are the same
    ASSERT(*q == *r);
    q->_head->data = 'C';
    ASSERT(!(*q == *r));
    char temp;
    *q >> temp;
    ASSERT(!(*q == *r));
    delete r;
    delete q;
  }
  
  /**
   * \brief A test function for concatenate operator
   */
  static void OperatorConcatenateTest() {
    DQueue *q = new DQueue('A');
    *q << 'B';
    DQueue *r = new DQueue('D');
    *r << 'C';
    DQueue *s = new DQueue('F');
    *s = *q + *r;
    // check if the structure is as expected
    ASSERT(s->_head != nullptr);
    ASSERT(s->_head->next != nullptr);
    ASSERT(s->_head->data == 'A');
    ASSERT(s->_head->next->next != nullptr);
    ASSERT(s->_head->next->data == 'B');
    ASSERT(s->_head->next->next->next != nullptr);
    ASSERT(s->_head->next->next->data == 'D');
    ASSERT(s->_head->next->next->next->next == nullptr);
    ASSERT(s->_head->next->next->next->data == 'C');
    delete s;
    delete r;
    delete q;
  }
  
  /**
   * \brief A test function for stream insertion operator
   */
  static void OperatorStreamInsertionTest() {
    // create a queue A->B->C
    DQueue *q = new DQueue();
    std::stringstream empty_ss;
    empty_ss << *q;
    ASSERT(empty_ss.str() == "empty queue\n");
    *q << 'A' << 'B' << 'C';
    std::stringstream ss;
    ss << *q;
    ASSERT(ss.str() == "A -> B -> C\n");
    delete q;
  }
};

// call our test functions in the main
int main(int, char* argv[]) {
  cout << "Testing DQueue" << endl;
  // register a seg fault handler
  sprintf(programName, "%s", argv[0]);
  struct sigaction signalAction;
  memset(&signalAction, 0, sizeof(struct sigaction));
  signalAction.sa_flags = SA_SIGINFO;
  signalAction.sa_sigaction = segFaultHandler;
  sigaction(SIGSEGV, &signalAction, NULL);
  
  DQueueTest::DefaultConstructorTest();
  DQueueTest::NonDefaultConstructorTest();
  DQueueTest::CopyConstructorTest();
  DQueueTest::OperatorAssignmentTest();
  DQueueTest::OperatorInsertionTest();
  DQueueTest::OperatorExtractionTest();
  DQueueTest::OperatorSmallerTest();
  DQueueTest::OperatorGreaterTest();
  DQueueTest::OperatorEqualityTest();
  DQueueTest::OperatorConcatenateTest();
  DQueueTest::OperatorStreamInsertionTest();
  
  return 0;
}
