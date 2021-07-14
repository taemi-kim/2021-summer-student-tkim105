#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <cctype>
#include <sstream>
#include <algorithm>

using std::vector;
using std::string;
using std::map;
using std::cout;
using std::cin;
using std::endl;
using std::pair;
using std::stringstream;
using std::sort;
using std::find;

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

int main() { 
  // TODO: implement
  cout << "Info: " << "Welcome to the Phone Database!" << endl; //info messages
  cout << "Info: " << "Please enter a command" << endl;
  string contact;
  while(getline(cin,contact)) {
    stringstream ss(contact);
    char command;
    string lastname;
    string firstname;
    string type;
    string phone_number;;
    ss >> command; //extract commamd 
      if (command == 'C') { //creates contact
	ss >> lastname >> firstname;
	Name newC;
	newC.lastname = lastname;
	newC.firstname = firstname;
	if(phone_db.find(newC) != phone_db.end()) {
	  cout << "Error: " << "Contact already exists" << endl;
	}
	else {
	    phone_db.emplace(newC, PhoneNumberCollection(5)); 
	    cout << "Result: " << "Contact created" << endl;
	  }
      }
      else if (command == 'D') { //deletes a contact
        ss >> lastname >> firstname;
        Name delC;
        delC.lastname = lastname;
        delC.firstname = firstname;
        if(phone_db.find(delC) != phone_db.end()) {
	   phone_db.erase(delC);
           cout << "Result: " << "Contact deleted" << endl;
          }
          else {
            cout << "Error: " << "Contact not found" << endl;
	  }
      }
      else if (command == 'L') { //list contact names
	//sort(phone_db.begin(), phone_db.end(), operator<);
	int numContact = 0;
	for (map<Name, PhoneNumberCollection>::iterator it = phone_db.begin(); it != phone_db.end(); ++it) {
	  cout << "Result: " << it->first.lastname << ',' << it->first.firstname << endl;
	  numContact++;
	}
	cout << "Info: " << "There are " << numContact << " contact(s)" << endl;
      }
      else if (command == 'P') { //list phone #s for a contact
	ss >> lastname >> firstname;
	//PhoneNumberCollection PNC; 
	int numPhone = 0;
	Name listC;
	listC.lastname = lastname;
	listC.firstname = firstname;
	if(phone_db.find(listC) != phone_db.end()) { //check if the contact exists      
	  PhoneNumberCollection &PNC = phone_db[listC];
	  //for (int indx = 0; indx < 5; indx++) 
	  if (PNC[0] == "" && PNC[1] == "" && PNC[2] == "" && PNC[3] == "" && PNC[4] == "") { //contact exists without phone numbers
	    cout << "Info: " << "There are no phone numbers for the contact" << endl;
	  }
	  else{
	    for (int indx = 0; indx < 5; indx++) {
	      if(PNC[indx].length() > 0) { //proceed if phone number exist for the type
		string type;
		if (indx == 0) type = "CELL";
		if (indx == 1) type = "HOME";
		if (indx == 2) type = "WORK";
		if (indx == 3) type = "FAX";
		if (indx == 4) type = "VOIP";
		cout << "Result: " << type << "," << PNC[indx] << endl;
		numPhone++;
              }
            }
	    cout << "Info: " << "Found " << numPhone << " phone number(s) for this contact" << endl;
          }
	  //cout << "Info: " << "Found " << numPhone << " phone number(s) for this contact" << endl;
	}
	else {
            cout << "Error: " << "Contact not found" << endl;
	}
      }
      else if (command == 'N') {
	ss >> lastname >> firstname >> type >> phone_number;
        Name addC;
        addC.lastname = lastname;
        addC.firstname = firstname;
	int length = phone_number.length();
	//invalid phone number
	if (!isdigit(phone_number[0]) || !isdigit(phone_number[length-1])) {
	  cout << "Error: " << "Not a valid phone number" << endl;
	  continue;
	}
	for (string::iterator sit = phone_number.begin(); sit != phone_number.end(); ++sit) {
	  if (!isdigit(*sit) && *sit != '-') {
	    cout << "Error: " << "Not a valid phone number" << endl;
	    continue;
	  }
	} // do I need to add 'else'?  
	
	if (type == "CELL" || type == "HOME" || type == "WORK" || type == "FAX" || type == "VOIP"){
	  int indx = 0;
	  if (type == "CELL") indx = 0;
	  if (type == "HOME") indx = 1;
	  if (type == "WORK") indx = 2;
	  if (type == "FAX") indx = 3;
	  if (type == "VOIP") indx = 4;
	  if(phone_db.find(addC) != phone_db.end()) {
	    PhoneNumberCollection &PNC = phone_db[addC];
	    if (PNC[indx] != "") {
	      PNC[indx] = phone_number;
              cout << "Result: " << "Phone number replaced" << endl;
	    }
	    else {
	      PNC[indx] = phone_number;; //add the new contact for the type                                 
              cout << "Result: " << "Phone number added" << endl;
	    }
	  }
	  else {
	    cout << "Error: " << "Contact not found" << endl;
	  }
	}
	else {
	  cout << "Error: " << "Invalid phone number type" << endl;
	}
      }
      cout << "Info: " << "Please enter a command" << endl;
  }
  return 0;
}
