#include "maze.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * \file maze.c
 * \brief Provides maze-related functionalities
 *
 * \details This source file implements all maze-related functionalities for reading/writing/solving/generating the maze and releasing related memories.
 */

// The function to read the maze from a file
int readMaze(const char* filename, char** maze, int* maze_width, int* maze_height) {
  
  
  //open mazeFile 
  File* mazeFile = fopen(filename, "r");
  if (mazeFile == NULL) {
      //printf("Error: could not open input file\n");
      return -1;
  }
  
  //read mazeFile into an array
  arraySize = maze_width * maze_height;
  int maze[arraySize];
  int i;
  
  for (i = 0; i < arraySize; i++){
      fscanf(mazeFile, "%d", &maze[i]);
  }
  
  //handle reading errors
  if(ferror(mazeFile)){
      //printf("Error: error indicator");
      return -2
  }
  
  //close input file
  fclose(mazeFile);
  return 0; //no error
}

// The function to write the maze to a file ( why is maze constant here while it's not in readMaze)
int writeMaze(const char* filename, const char* maze, const int maze_width, const int maze_height) {
  
  return 0;
}

// The function to release the maze's data
void releaseMaze(char** maze) {
  if (*maze) releaseChars(maze);
}

// The function to solve a solution path for the maze
int solveMaze(const char* maze, const int maze_width, const int maze_height, char** sol) {
  // TODO: implement this function
  return solvePath(maze, maze_width, maze_height, 0, 0, *sol); // TODO: replace this stub
}

// The function to solve a solution path recursively
int solvePath(const char* maze, const int maze_width, const int maze_height, const int col, const int row, char* sol) {
  // TODO: implement this function
  return 0; // TODO: replace this stub
}

// The function to generate a maze
void genMaze(char** maze, const int maze_width, const int maze_height, const double threshold, const int seed) {
  // TODO: implement this function
}

// The function to release the solution path
void releaseSolution(char** sol) {
  if (*sol) releaseChars(sol);
}

// The function to release dynamically allocated array of characters
void releaseChars(char** p) {
  // TODO: implement this function
}
