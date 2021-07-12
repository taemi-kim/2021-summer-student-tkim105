#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <cctype>

using std::vector;
using std::string;
using std::map;
using std::cout;
using std::cin;
using std::endl;

// define a Name type
typedef struct {
  string lastname, firstname;
} Name;

/* Create a lower-case version of a string.
   param s is the original string
   return a lower-case equivalent
*/
string str_to_lower(const string &s) {
  // TODO: implement this function and update return value
  return "";
}

/* Compare two Name structures, ignoring capitalization.
   return true if left comes before right alphabetically
   using lastname as the primary comparison, breaking ties with firstname.
   return false otherwise
*/
bool operator<(const Name &left, const Name &right) {
  // TODO: implement this function and update return value
  return false;
}

// WARNING: do not define a structure using the Name type as the key of
// a map before the comparison function above, only after it.

// TODO: define the other data types used to represent the phone list

int main() {
  // TODO: implement

  return 0;
}
