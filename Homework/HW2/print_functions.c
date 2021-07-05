#include "print_functions.h"
#include <stdio.h>

/**
 * \file print_functions.c
 * \brief Provides print-related functionalities
 *
 * \details This source file implements all print-related functionalities for printing the maze, solution, and errors
 */

// The function to print the maze
void printMaze(const char* maze, const int maze_width, const int maze_height) {
  for (int i = 0; i < maze_height; i++) {
        for (int j = 0; j < maze_width; j++) {
            printf("%c", maze[i * maze_width + j]);
         
        } 
      printf("\n");
    } 
}

// The function to print the maze's solution
void printSolution(const char* maze, const int maze_width, const int maze_height, const char* sol) {
  for (int i = 0; i < maze_height; i++) {
      for (int j = 0; j < maze_width; j++) {
	if (sol[i*maze_width+j] == '*') {
	  printf("%c", sol[i*maze_width+j]);

	}
	else {
	  printf("%c", maze[i*maze_width+j]);
	  
	}
      
      } 
      printf("\n");
  } 
  printf("\n");
  
}

// The function to print the error message
void printError(const int return_code, char* argv[]) {
  if (return_code==1) {
    fprintf(stdout, "Info: No solution found for %s\n", argv[1]);

  }
}
