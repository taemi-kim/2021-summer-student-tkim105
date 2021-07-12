#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>

using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;
using std::sort;
using std::vector;

struct Bucket {
  char letter;
  unsigned count;

};
bool compare_buckets(const Bucket &left, const Bucket &right) {
  if (left.count < right.count) return true;
  return false;

}//should I define bool here? 


int main(int argc, char **argv) {
  // TODO: implement
  //std::cin << argv[1]; // does this read one character at a time?
  if (argc < 2) {
    cerr << "Invalid argument" << endl;
  }
  
  vector<Bucket> hist {};
  hist.resize(26);//one Bucket per letter - should I use dynamic  memory allocation? 
  std::cin >> argv[1];
  char c;
  while (std::cin.get(c)) {
    if(isalpha(c)) {
      c = tolower(c);
      Bucket temp;
      temp.letter = c;
      temp.count++;
      hist.push_back(temp);//does this automatically handle duplicates?

    }

  }

  sort(hist.begin(), hist.end(), compare_buckets);

  //for(vector<Bucket>hist::iterator it = hist.begin(); it != hist.end(); ++it) {
  for(size_t i = 0; i < hist.size(); i++) {
  cout << hist[i].letter << ": " << hist[i].count << endl;
  //cout << it->letter << ": " << it->count << endl;
    
  }
  return 0;
}
