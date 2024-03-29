
/*
This program illustrates the utility of nested container classes.  


TODO: Read in words from standard input until end of file
occurs, and populate the map<string, int> named counters so that each
entry has a key which is a word collected and the corresponding value
is the number of times that word appears in the file.  The code to
output the contents of the counters map is already present in this file.



TODO: Run through the counters map you populated above,
and copy over the data into a new map called words_by_freq, but
rearrange your data so that each entry in the new map has an integer
key, and has an entire vector as its value.  The vector will hold all
strings with the frequency indicated by key.
You can think of the words_by_freq map as a notebook of information,
where each entry is a page, and at the top of the page, you wrote
an integer frequency, and on the rest of the page, you've written
a list of all the words you encountered with that frequency.


TODO: Using const_iterators, write code to output the contents
of the words_by_freq map, arranged by frequency.  So, if the input words were:

and Mama called the doctor and the doctor said no more monkeys

Then the output would be:
Frequency: 1
Mama
called
monkeys
more
no
said

Frequency: 2
and
doctor
the

*/

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm> //added

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::map;
using std::vector;
using std::find; //added

int main() {

  map<string, int> counters; // We'll store each word and an associated counter

  //TODO:  fill in code here to populate counters before it gets output
  string word;
  /*int freq;
  map<string, int>::const_iterator it;
  
  while (cin >> word >> freq) {//so we don't have to do this because the entry itself is a pair?
    counters[word] = freq;

    }*/

  while (cin >> word) {
    counters[word]++; //why can we directly use this and advance the content? r

  }

  
  // Loop through the map and print contents, making use of the iterator
  // it to successively point to each entry in the map in turn.
  // We use it->first and it->second to get current key and value.
  cout << endl;
  for (map<string, int>::const_iterator it = counters.cbegin();
       it != counters.cend();
       ++it) {
    cout << "word " << it->first << " has " << it->second
	 << " occurrences" << endl;

  }

  
  //TODO:  fill in code here to populate words_by_freq
  //Note that this map has int keys and values which are vectors of strings.
  map<int, vector<string> > words_by_freq;
  
  for (map<string, int>::const_iterator it = counters.cbegin();
       it != counters.cend();
       ++it) {
    words_by_freq[it->second].push_back(it->first);
    
  }


  
  // TODO: write code here to output the contents of the
  // words_by_freq map, arranged by frequency.
  for (map<int, vector<string>>::const_iterator WItr = words_by_freq.cbegin();
       WItr != words_by_freq.cend();
       ++WItr) {
    cout << "Frequency: " << WItr->first << endl;
    for(size_t i = 0; i < WItr->second.size(); i++) {
	cout << WItr->second.at(i) << endl;
	
      } 


  }


  

  

  return 0;
}
