#include "TDQueue.h"
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
 * \struct TDQueueTest
 * \defgroup TDQueueTest
 * \brief Test cases for the TDQueue class
 */
struct TDQueueTest {
  // alias
  using CTDQueue = TDQueue<char>;
  using ITDQueue = TDQueue<int>;
  
  /**
   * \brief A test function for default constructor
   */
  static void DefaultConstructorTest() {
    CTDQueue *cq = new CTDQueue();
    // check if the structure is as expected
    ASSERT(cq->_head == nullptr);
    delete cq;
    
    ITDQueue *iq = new ITDQueue();
    // check if the structure is as expected
    ASSERT(iq->_head == nullptr);
    delete iq;
  }
   
  /**
   * \brief A test function for non-default constructor
   */
  static void NonDefaultConstructorTest() {
    CTDQueue *cq = new CTDQueue('A');
    // check if the structure is as expected
    ASSERT(cq->_head != nullptr);
    ASSERT(cq->_head->next == nullptr);
    ASSERT(cq->_head->data == 'A');
    delete cq;
    
    ITDQueue *iq = new ITDQueue(50);
    // check if the structure is as expected
    ASSERT(iq->_head != nullptr);
    ASSERT(iq->_head->next == nullptr);
    ASSERT(iq->_head->data == 50);
    delete iq;
  }
  
  /**
   * \brief A test function for copy constructor
   */
  static void CopyConstructorTest() {
    CTDQueue *cq = new CTDQueue('A');
    *cq << 'B' << 'C';
    CTDQueue *cr = new CTDQueue(*cq);
    // check if the structure is as expected
    ASSERT(cr->_head != nullptr);
    ASSERT(cr->_head->next != nullptr);
    ASSERT(cr->_head->data == 'A');
    ASSERT(cr->_head->next->next != nullptr);
    ASSERT(cr->_head->next->data == 'B');
    ASSERT(cr->_head->next->next->next == nullptr);
    ASSERT(cr->_head->next->next->data == 'C');
    delete cr;
    delete cq;
    
    ITDQueue *iq = new ITDQueue(50);
    *iq << 60 << 70;
    ITDQueue *ir = new ITDQueue(*iq);
    // check if the structure is as expected
    ASSERT(ir->_head != nullptr);
    ASSERT(ir->_head->next != nullptr);
    ASSERT(ir->_head->data == 50);
    ASSERT(ir->_head->next->next != nullptr);
    ASSERT(ir->_head->next->data == 60);
    ASSERT(ir->_head->next->next->next == nullptr);
    ASSERT(ir->_head->next->next->data == 70);
    delete ir;
    delete iq;
  }
  
  /**
   * \brief A test function for assignment operator
   */
  static void OperatorAssignmentTest() {
    CTDQueue *cq = new CTDQueue('A');
    *cq << 'B' << 'C';
    CTDQueue *cr = new CTDQueue('B');
    *cr = *cq;
    // check if the structure is as expected
    ASSERT(cr->_head != nullptr);
    ASSERT(cr->_head->next != nullptr);
    ASSERT(cr->_head->data == 'A');
    ASSERT(cr->_head->next->next != nullptr);
    ASSERT(cr->_head->next->data == 'B');
    ASSERT(cr->_head->next->next->next == nullptr);
    ASSERT(cr->_head->next->next->data == 'C');
    delete cr;
    delete cq;
    
    ITDQueue *iq = new ITDQueue(50);
    *iq << 60 << 70;
    ITDQueue *ir = new ITDQueue(60);
    *ir = *iq;
    // check if the structure is as expected
    ASSERT(ir->_head != nullptr);
    ASSERT(ir->_head->next != nullptr);
    ASSERT(ir->_head->data == 50);
    ASSERT(ir->_head->next->next != nullptr);
    ASSERT(ir->_head->next->data == 60);
    ASSERT(ir->_head->next->next->next == nullptr);
    ASSERT(ir->_head->next->next->data == 70);
    delete ir;
    delete iq;
  }
  
  /**
   * \brief A test function for insertion operator
   */
  static void OperatorInsertionTest() {
    // create a TDQueue A->C->B
    CTDQueue *cq = new CTDQueue();
    *cq << 'A' << 'C' << 'B';
    // check if the structure is as expected
    ASSERT(cq->_head != nullptr);
    ASSERT(cq->_head->next != nullptr);
    ASSERT(cq->_head->data == 'A');
    ASSERT(cq->_head->next->next != nullptr);
    ASSERT(cq->_head->next->data == 'C');
    ASSERT(cq->_head->next->next->next == nullptr);
    ASSERT(cq->_head->next->next->data == 'B');
    delete cq;
    
    // create a TDQueue 50->70->60
    ITDQueue *iq = new ITDQueue(50);
    *iq << 70 << 60;
    // check if the structure is as expected
    ASSERT(iq->_head != nullptr);
    ASSERT(iq->_head->next != nullptr);
    ASSERT(iq->_head->data == 50);
    ASSERT(iq->_head->next->next != nullptr);
    ASSERT(iq->_head->next->data == 70);
    ASSERT(iq->_head->next->next->next == nullptr);
    ASSERT(iq->_head->next->next->data == 60);
    delete iq;
  }
  
  /**
   * \brief A test function for extraction operator
   */
  static void OperatorExtractionTest() {
    // create a TDQueue A->C->B
    CTDQueue *cq = new CTDQueue();
    char cempty = -1;
    char cempty_copy = cempty;
    *cq >> cempty;
    ASSERT(cempty == cempty_copy);
    *cq << 'A' << 'C' << 'B';
    // deTDQueue A and B
    char a, b;
    *cq >> a >> b;
    ASSERT(a == 'B');
    ASSERT(b == 'C');
    // check if the structure is as expected
    ASSERT(cq->_head != nullptr);
    ASSERT(cq->_head->next == nullptr);
    ASSERT(cq->_head->data == 'A');
    delete cq;
    
    // create a TDQueue 50->70->60
    ITDQueue *iq = new ITDQueue();
    int iempty = 9999;
    int iempty_copy = iempty;
    *iq >> iempty;
    ASSERT(iempty == iempty_copy);
    *iq << 50 << 70 << 60;
    // deTDQueue A and B
    int i, j;
    *iq >> i >> j;
    ASSERT(i == 60);
    ASSERT(j == 70);
    // check if the structure is as expected
    ASSERT(iq->_head != nullptr);
    ASSERT(iq->_head->next == nullptr);
    ASSERT(iq->_head->data == 50);
    delete iq;
  }
  
  /**
   * \brief A test function for smaller than operator
   */
  static void OperatorSmallerTest() {
    // create a TDQueue B->C->A
    CTDQueue *cq = new CTDQueue();
    *cq < 'A' < 'C' < 'B';
    // check if the structure is as expected
    ASSERT(cq->_head != nullptr);
    ASSERT(cq->_head->next != nullptr);
    ASSERT(cq->_head->data == 'B');
    ASSERT(cq->_head->next->next != nullptr);
    ASSERT(cq->_head->next->data == 'C');
    ASSERT(cq->_head->next->next->next == nullptr);
    ASSERT(cq->_head->next->next->data == 'A');
    delete cq;
    
    // create a TDQueue 60->70->50
    ITDQueue *iq = new ITDQueue(50);
    *iq < 70 < 60;
    // check if the structure is as expected
    ASSERT(iq->_head != nullptr);
    ASSERT(iq->_head->next != nullptr);
    ASSERT(iq->_head->data == 60);
    ASSERT(iq->_head->next->next != nullptr);
    ASSERT(iq->_head->next->data == 70);
    ASSERT(iq->_head->next->next->next == nullptr);
    ASSERT(iq->_head->next->next->data == 50);
    delete iq;
  }
  
  /**
   * \brief A test function for grater than operator
   */
  static void OperatorGraterTest() {
    // create a TDQueue A->C->B
    CTDQueue *cq = new CTDQueue();
    char cempty = -1;
    char cempty_copy = cempty;
    *cq > cempty;
    ASSERT(cempty == cempty_copy);
    *cq << 'A' << 'C' << 'B';
    // deTDQueue A and B
    char a, b;
    *cq > a > b;
    ASSERT(a == 'A');
    ASSERT(b == 'C');
    // check if the structure is as expected
    ASSERT(cq->_head != nullptr);
    ASSERT(cq->_head->next == nullptr);
    ASSERT(cq->_head->data == 'B');
    delete cq;
    
    // create a TDQueue 50->70->60
    ITDQueue *iq = new ITDQueue();
    int iempty = 9999;
    int iempty_copy = iempty;
    *iq > iempty;
    ASSERT(iempty == iempty_copy);
    *iq << 50 << 70 << 60;
    // deTDQueue A and B
    int i, j;
    *iq > i > j;
    ASSERT(i == 50);
    ASSERT(j == 70);
    // check if the structure is as expected
    ASSERT(iq->_head != nullptr);
    ASSERT(iq->_head->next == nullptr);
    ASSERT(iq->_head->data == 60);
    delete iq;
  }
  
  /**
   * \brief A test function for equality operator
   */
  static void OperatorEqualityTest() {
    // create two TDQueues A->B->C
    CTDQueue *cq = new CTDQueue();
    *cq << 'A' << 'B' << 'C';
    CTDQueue *cr = new CTDQueue();
    *cr << 'A' << 'B' << 'C';
    // check if they are the same
    ASSERT(*cq == *cr);
    cq->_head->data = 'C';
    ASSERT(!(*cq == *cr));
    char ctemp;
    *cq > ctemp;
    ASSERT(!(*cq == *cr));
    delete cr;
    delete cq;
    
    // create two TDQueues 50->60->70
    ITDQueue *iq = new ITDQueue();
    *iq << 50 << 60 << 70;
    ITDQueue *ir = new ITDQueue();
    *ir << 50 << 60 << 70;
    // check if they are the same
    ASSERT(*iq == *ir);
    iq->_head->data = 70;
    ASSERT(!(*iq == *ir));
    int itemp;
    *iq > itemp;
    ASSERT(!(*iq == *ir));
    delete ir;
    delete iq;
  }
  
  /**
   * \brief A test function for concatenate operator
   */
  static void OperatorConcatenateTest() {
    CTDQueue *cq = new CTDQueue('A');
    *cq << 'B';
    CTDQueue *cr = new CTDQueue('D');
    *cr << 'C';
    CTDQueue *cs = new CTDQueue('F');
    *cs = *cq + *cr;
    // check if the structure is as expected
    ASSERT(cs->_head != nullptr);
    ASSERT(cs->_head->next != nullptr);
    ASSERT(cs->_head->data == 'A');
    ASSERT(cs->_head->next->next != nullptr);
    ASSERT(cs->_head->next->data == 'B');
    ASSERT(cs->_head->next->next->next != nullptr);
    ASSERT(cs->_head->next->next->data == 'D');
    ASSERT(cs->_head->next->next->next->next == nullptr);
    ASSERT(cs->_head->next->next->next->data == 'C');
    delete cs;
    delete cr;
    delete cq;
    
    ITDQueue *iq = new ITDQueue(50);
    *iq << 60;
    ITDQueue *ir = new ITDQueue(80);
    *ir << 70;
    ITDQueue *is = new ITDQueue(90);
    *is = *iq + *ir;
    // check if the structure is as expected
    ASSERT(is->_head != nullptr);
    ASSERT(is->_head->next != nullptr);
    ASSERT(is->_head->data == 50);
    ASSERT(is->_head->next->next != nullptr);
    ASSERT(is->_head->next->data == 60);
    ASSERT(is->_head->next->next->next != nullptr);
    ASSERT(is->_head->next->next->data == 80);
    ASSERT(is->_head->next->next->next->next == nullptr);
    ASSERT(is->_head->next->next->next->data == 70);
    delete is;
    delete ir;
    delete iq;
  }
  
  /**
   * \brief A test function for stream insertion operator
   */
  static void OperatorStreamInsertionTest() {
    // create a TDQueue A->B->C
    CTDQueue *cq = new CTDQueue();
    std::stringstream empty_css;
    empty_css << *cq;
    ASSERT(empty_css.str() == "empty queue\n");
    *cq << 'A' << 'B' << 'C';
    std::stringstream css;
    css << *cq;
    ASSERT(css.str() == "A -> B -> C\n");
    delete cq;
    
    // create a TDQueue 50->60->70
    ITDQueue *iq = new ITDQueue();
    std::stringstream empty_iss;
    empty_iss << *iq;
    ASSERT(empty_iss.str() == "empty queue\n");
    *iq << 50 << 60 << 70;
    std::stringstream iss;
    iss << *iq;
    ASSERT(iss.str() == "50 -> 60 -> 70\n");
    delete iq;
  }
};

// call our test functions in the main
int main(int, char* argv[]) {
  cout << "Testing TDQueue" << endl;
  // register a seg fault hanlder
  sprintf(programName, "%s", argv[0]);
  struct sigaction signalAction;
  memset(&signalAction, 0, sizeof(struct sigaction));
  signalAction.sa_flags = SA_SIGINFO;
  signalAction.sa_sigaction = segFaultHandler;
  sigaction(SIGSEGV, &signalAction, NULL);
  
  TDQueueTest::DefaultConstructorTest();
  TDQueueTest::NonDefaultConstructorTest();
  TDQueueTest::CopyConstructorTest();
  TDQueueTest::OperatorAssignmentTest();
  TDQueueTest::OperatorInsertionTest();
  TDQueueTest::OperatorExtractionTest();
  TDQueueTest::OperatorSmallerTest();
  TDQueueTest::OperatorGraterTest();
  TDQueueTest::OperatorEqualityTest();
  TDQueueTest::OperatorConcatenateTest();
  TDQueueTest::OperatorStreamInsertionTest();
  
  return 0;
}
