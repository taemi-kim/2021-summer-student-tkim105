#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using std::string;
using std::stringstream;
using std::cin;
using std::cout;
using std::endl;


/*bool check_num(string token) {
  for (int i = 0; i < token.length(); i++) {
    if (isdigit(token[i]) == false) return false;
  }
  return true;
}*/

int main() {
  // TODO: implement
  string token;
  int intSum = 0;
  double floatSum = 0;
  int numWords = 0;
  int wordLength = 0;
  
  while (cin >> token) {
    stringstream ss(token);
    int intVal;
    string nonInt;
    double floatVal;
    if (ss >> intVal) {
      //if (ss.str().length() == token.length()) {//check if the extraction of integer consumed the entire sring
      if (ss >> nonInt) {
   	floatVal = std::stof(token);//string to float conversion
	floatSum += floatVal;
      }
      else {
	intSum += intVal;

      }
    }
      else {
	ss >> floatVal;
	floatSum += floatVal;
	
      }
    }
      
    /*else if (ss >> floatVal) {
      floatSum += floatVal;

      }*/
    else {
      numWords++;
      wordLength += token.length();
    }

    /*if (check_num) {
      numWords++;
      wordLength += token.length();
    }
    else {
      if (atoi(token) == ceil(token)) {
	intSum++;
      }
      else {
	floatSum+ */
  }

  cout << "Floating point sum: " << floatSum << endl;
  cout << "Integer sum: " << intSum << endl;
  cout << "Number of non-numeric tokens: " << numWords << endl;
  cout << "Number of characters in non-numeric tokens: " << wordLength << endl;
  
  return 0;
}
