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
typedef vector<pair<string,string>> PhoneNumberCollection;
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
	    phone_db.emplace(newC, PhoneNumberCollection()); //right way to call the empty vector?
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
	for (map<Name, PhoneNumberCollection>::iterator it = phone_db.begin(); it != phone_db.end(); ++it) {
	  cout << "Result: " << it->first.lastname << ',' << it->first.firstname << endl;
	}
      }
      else if (command == 'P') { //list phone #s for a contact
	ss >> lastname >> firstname;
	PhoneNumberCollection PNC; 
	int numPhone = 0;
	Name listC;
	listC.lastname = lastname;
	listC.firstname = firstname;
	if(phone_db.find(listC) != phone_db.end()) { //check if the contact exists      
	  if (phone_db[listC].empty()) { //contact exists without phone numbers                                   
            cout << "Info: " << "There are no phone numbers for the contact" << endl;
	  }
          for (map<Name, PhoneNumberCollection>::iterator it = phone_db.begin(); it != phone_db.end(); ++it) {
            for (vector<pair<string,string>>::iterator itr = it->second.begin();
                 itr != it->second.end(); ++itr) {
              if(itr->second.length() > 0) { //proceed if phone number exist for the type                              
                cout << "Result: " << itr->first << "," << itr->second << endl;
                numPhone++;

              }
            }
            cout << "Info: " << "Found " << numPhone << " phone number(s) for this contact" << endl;
          }
	}
	else {
            cout << "Error: " << "Contact not found" << endl;
	}
      }
      else if (command == 'N') {
	ss >> lastname >> firstname >> type >> phone_number;
        PhoneNumberCollection PNC;
	Name addC;
        addC.lastname = lastname;
        addC.firstname = firstname;
	if (phone_number /*The string can only have digits or hypens and must start and end with a digit*/) {
	  cout << "Error: " << "Not a valid phone number" << endl;
	}
	if (type == "CELL" || type == "HOME" || type == "WORK" || type == "FAX" || type == "VOIP"){
	  PNC.insert(PNC.begin(),make_pair(type,phone_number));
	  if(phone_db.find(addC) != phone_db.end()) {
	    vector<pair<string,string>>::const_iterator it;
	    it = find(phone_db[addC].begin(), phone_db[addC].end(),PNC[0].first); //find if the type exists
	    if (it != phone_db[addC].end()) { //contact exists without phone numbers
	      //phone_db[addC].at(it).second = PNC[0].second; //update the phone number for the type 
	      phone_db[addC][it] = make_pair(PNC[0]);
	      cout << "Result: " << "Phone number replaced" << endl;
	    }
	    else {
	      phone_db[addC].push_back(PNC[0]); //add the new contact for the type
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
