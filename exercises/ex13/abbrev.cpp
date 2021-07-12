#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstddef>
#include <cctype>

using std::string;
using std::stringstream;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::cerr;
using std::cout;

string abbreviate(const string &word);

int main(int argc, char **argv) {
  // TODO: implement

  //print out error messages
  if (argc != 3) {
    cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;

  }

  ifstream in(argv[1]);
  if (!in.is_open()) {
    cerr << "Cannot open file: " << argv[1] << endl;
    return -1;
    
  }

  ofstream out(argv[2]);
  if (!out.is_open()) {
    cerr << "Cannot open file: " << argv[2] << endl;
    return -1;

  }

  //string processing
  string line;
    while (getline(in, line)) { //read by line
    stringstream ss(line);
    string word;
    while (ss >> word) { //read in words in the line
      cout << "input: " << word << endl;
      for (size_t i = 0; i < word.size(); i++) {
	if (word[i] == 'A' || word[i] == 'a' || word[i] == 'E' || word[i] == 'e' || word[i] == 'I' || word[i] == 'i' || word[i] == 'O' || word[i] == 'o' || word[i] == 'U' || word[i] == 'u') {

	bool prev_is_vowel (word){
	  bool status = false;
	  if (word[i-1] == 'A' || word[i-1] == 'a' || word[i-1] == 'E' || word[i-1] == 'e' || word[i-1] == 'I' ||word[i-1] == 'i' || word[i-1] == 'O' || word[i-1] == 'o' || word[i-1] == 'U' || word[i-1] == 'u') {
	    status = true;
	  }
	return status;
      }
	  if (prev_is_vowel == true) {
	    //prev_is_vowel = true;
	    word.erase(i-1);
	    word[i] = '\'';

	  }	  
	}
	else {
	  //prev_is_vowel = false;
	  word[i] = '\'';

	}
      }
      cout << "Output: " << word << endl;
      out << word << " ";
      
    }
  }
    

  return 0;
}

string abbreviate(const string &word) {


}
