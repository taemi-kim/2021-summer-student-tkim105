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
  string result = s;
  for (size_t i = 0; i < s.size(); i++) {
    result[i] = tolower(s[i]);
  }
  return result;
}

/* Compare two Name structures, ignoring capitalization.
   return true if left comes before right alphabetically
   using lastname as the primary comparison, breaking ties with firstname.
   return false otherwise
*/
bool operator<(const Name &left, const Name &right) {
  // TODO: implement this function and update return value
  string left_lastname = str_to_lower(left.lastname);
  string left_firstname = str_to_lower(left.firstname);
  string right_lastname = str_to_lower(right.lastname);
  string right_firstname = str_to_lower(left.firstname);
  if (left_lastname == right_lastname) { //same lastnames
    return left_firstname < right_firstname;
  }
  else {
    return left_lastname < right_lastname;
  }
  return false;
}

// WARNING: do not define a structure using the Name type as the key of
// a map before the comparison function above, only after it.

// TODO: define the other data types used to represent the phone list
typedef vector<string> PhoneNumberCollection;
map<Name, PhoneNumberCollection> phone_db;

int main(/*argc, **argv*/) { //added argc, argv is this correct? 
  // TODO: implement
  cout << "Info: " << "Welcome to the Phone Database!" << endl; //info messages
  cout << "Info: " << "Please enter a command" << endl;
  string contact;
  while(getline(cin,contact)) {
    std::stringstream ss(contact);
    char command;
    string lastname;
    string firstname;
    ss << command; //extract commamd 
      if (command == 'C') { //creates contact
	ss << lastname << firstname;
	Name newC;
	newC.lastname = lastname;
	newC.firstname = firstname;
	for (map<Name, PhoneNumberCollection>::iterator it = phone_db.begin(); it != phone_db.end(); ++it) {
	  if (it->first.firstname == newC.firstname) {
	    cout << "Error: " << "Contact already exists" << endl;
	  }
	  else {
	    phone_db.emplace(newC, PhoneNumberCollection()); //right way to call the empty vector?
	    cout << "Result: " << "Contact created" << endl;
	  }
	}
	
      }
      else if (command == 'D') { //deletes a contact
        ss << lastname << firstname;
        Name delC;
        delC.lastname = lastname;
        delC.firstname = firstname;
	for (map<Name, PhoneNumberCollection>::iterator it = phone_db.begin(); it != phone_db.end(); ++it) {
          if (it->first.firstname == delC.firstname) {
	    phone_db.erase (it);
            cout << "Result: " << "Contact deleted" << endl;
          }
          else {
            cout << "Error: " << "Contact not found" << endl;
	  }
        }

      }
      else if (command == 'L') { //list contact names
	sort(phone_db.begin(), phone_db.end(), operator<);
	for (map<Name, PhoneNumberCollection>::iterator it = phone_db.begin(); it != phone_db.end(); ++it) {
	  cout << "Result: " << it->first.lastname << ',' << it->first.firstname << endl;
	}
      }
      else if (command == 'P') { //list phone #s for a contact
	

      }
    }
 
  cout << "Result: " << endl; //result messages
  cout << "Error: " << endl; //error messages
  return 0;
}
