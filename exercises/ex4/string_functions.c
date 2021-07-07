#include "string_functions.h"
#include <stdio.h>
#include <string.h>

int concat(const char word1[], const char word2[], char result[], int result_capacity){

//TODO: replace the following stub with a correct function body so that                     //      this function behaves as indicated in the comment above
//                                                                                                      
  int length_word1 = 0;
  int length_word2 = 0;
  while (word1[length_word1] != '\0') {
    length_word1++;
  }
  while (word2[length_word2] != '\0') {
    length_word2++;
  }
  int length_concat = length_word1 + length_word2;
  if (length_concat < result_capacity) {
    for (int i = 0; i < length_word1; i++) {
      result[i] = word1[i];
    }
    for (int j = length_word1; j < length_concat; j++) {
      for (int i = 0; i < length_word2; i++) {
        result[j] = word2[i];
      }
    }
    result[length_concat] = '\0';
    return 0;

  }
   //NOTE: you may not use the strcat or strcpy library functions in your solution                         
  return -1;
}
