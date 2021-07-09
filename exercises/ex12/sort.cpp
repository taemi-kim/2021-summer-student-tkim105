#include <iostream>
#include <cassert>
#include <vector>
#include <random>
#include <chrono>
// TODO: Make sure to include any additional necessary header files
#include <algorithm>

using std::cin;

void sort( std::vector< int > *values );

int main( void ) {
  std::vector< int > vec;
  size_t count;

  std::cout << "Enter the count: ";
  // TODO: read in the count of random numbers from the standard input.
  std::cin >> count;

  /*
  while (cin >> count) {
    vec.push_back(count);

    } */

  // TODO: initialize random number generation engine and generator
  std::default_random_engine rd_eng{static_cast<long unsigned int>(1)}; //seed: 1
  std::uniform_int_distribution<int> dist(0, 2000);
  

  // TODO: Make the "vec" vector store "count" random values
  vec.resize(count);
  for (size_t i = 0; i < count; i++) {
    //vec.push_back(dist(rd_eng));
    vec[i] =  dist(rd_eng);
  }

  // print the first 20 values
  std::cout << "input: ";
  for (size_t i = 0; i < 20 && i < vec.size(); ++i) std::cout << vec[i] << " ";
  std::cout << std::endl;
  
  // sort and measure the performance
  std::vector< int > vec2 = vec;
  std::chrono::steady_clock::time_point begin1 = std::chrono::steady_clock::now();
  sort( &vec );
  std::chrono::steady_clock::time_point end1 = std::chrono::steady_clock::now();
  
  // print the first 20 values
  std::cout << "sorted: ";
  for (size_t i = 0; i < 20 && i < vec.size(); ++i) std::cout << vec[i] << " ";
  std::cout << std::endl;
  
  for( size_t i=1 ; i<vec.size() ; i++ ) assert( vec[i-1]<=vec[i] );
  
  std::chrono::steady_clock::time_point begin2 = std::chrono::steady_clock::now();
  // TODO: Use the implementation of sort from STL to sort the contents of "vec2"
  sort(vec2.begin(),vec2.end());
  
  std::chrono::steady_clock::time_point end2 = std::chrono::steady_clock::now();
  
  for( size_t i=1 ; i<vec2.size() ; i++ ) assert( vec2[i-1]<=vec2[i] );
    
  std::cout << "Your sort time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end1 - begin1).count() << "(ms)" << std::endl;
  std::cout << "STL's sort time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end2 - begin2).count() << "(ms)" << std::endl;
  
  return 0;
}

void sort( std::vector< int > *values ) {
  // TODO: Define the sort function
  if (values->size() < 2) return;
  std::vector<int> left,right;
  size_t mid_idx = values->size()/2;
  for (size_t i = 0; i < values->size(); i++) {
    if (i < mid_idx){
      left.push_back(values->at(i));
    }
    else {
      right.push_back(values->at(i));
    }
  }

  //recursively call sort
  sort(&left);
  sort(&right);

  //sort left and right
  size_t left_idx = 0, right_idx = 0;
  for (size_t i = 0; i < values->size(); i++) {
    if (left_idx == left.size()) {
      values->at(i) = right[right_idx];
      ++right_idx;

    }
    else if (right_idx == right.size()) {
      values->at(i) = left[left_idx];
      ++left_idx;

    }
    else if (left[left_idx] < right[right_idx]) {
      values->at(i) = left[left_idx];
      ++left_idx;

    }
    else {
      values->at(i) = right[right_idx];
      ++right_idx;
      
    }
  }

}


