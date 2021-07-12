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
      ss //extract 
      if (contact[0] == 'C') { //creates contact
	Name temp;
	temp.lastname = contact[1];
	temp.firstname = contact[2];
	for (map<Name, PhoneNumberCollection>::iterator it = phone_db.begin(); it != phone_db.end(); ++it) {
	  if (it->first == temp) {
	    cout << "Error: " << "Contact already exists" << endl;
	  }
	  else {
	    phone_db[temp].push_back();
	    cout << "Result: " << "Contact created" << endl;
	  }
	}
	
      }
      else if (contact[0] == 'D') { //deletes a contact
	Name temp;
        temp.lastname =	contact[1];
        temp.firstname = contact[2];
	for (map<Name, PhoneNumberCollection>::iterator it = phone_db.begin(); it != phone_db.end(); ++it) {
          if (it->first == temp) {
	    phone_db.erase (it);
            cout << "Result: " << "Contact deleted" << endl;
          }
          else {
            phone_db[temp].push_back();
            cout << "Error: " << "Contact not found" << endl;
	  }
        }

      }
      else if (contact[0] == 'L') { //list contact names
	sort(phone_db.begin(), phone_db.end(), operator<);
	for (map<Name, PhoneNumberCollection>::iterator it = phone_db.begin(); it != phone_db.end(); ++it) {
	  cout << "Result: " << it->first.lastname << ',' << it->first.firstname << endl;
	}
      }
      else if (contact[0] == 'P') { //list phone #s for a contact
	

      }
    }
 
  cout << "Result: " << endl; //result messages
  cout << "Error: " << endl; //error messages
  return 0;
}
