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
  char newChar; //dummy variable
  int size;
   
  FILE*mazeFile = fopen(filename, "r");
  fscanf(mazeFile,"%d %d\n", maze_width, maze_height);
  
  size = *maze_width * *maze_height; //derefernce for real values
  *maze = malloc(sizeof(char) * size); //to keep the values 
  
  //loop 
  for (int i = 0; i < *maze_height; i++) {
      for (int j = 0; j < *maze_width; j++) {
          fscanf(mazeFile,"%c", &(*maze)[i* *maze_width + j]); //one dim = needs dereference, prioritize deref()
      }
      fscanf(mazeFile, "%c\n", &newChar); //& = address / turning it to the pointer
  }
  
  //close input file
  fclose(mazeFile); 
  return 0;
}

// The function to write the maze to a file
int writeMaze(const char* filename, const char* maze, const int maze_width, const int maze_height) {
  // TODO: implement this function
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
  
    //Initiallize a random seed
    srand(seed);
    
    // Generate a start position 
    const int column_s = rand() % maze_width + 1;
    const int row_s = rand() % maze_height + 1;
    
    srand(seed);
    
    // Generate a end position
    const int column_e = rand() % maze_width + 1;
    const int row_e = rand() % maze_height + 1;
   
    
    for (int i = 0; i < maze_height; i++) {
        for (int j = 0; j < maze_width; j++){
            // Set the boundary walls 
            if (i == 0 || i == maze_height - 1) {
                maze[i*maze_width+j] = "#";
                break;
            } else if (j == 0 || j == maze_width - 1) {
                maze[i*maze_width+j] = "#";
                break;
                
            } else if (i == row_s && j == column_s) {
                maze[i*maze_width+j] = "@";
                break;
                
            } else if (i == row_e && j == column_e) {
                maze[i*maze_width+j] = "<";
                break;
            } 
            
            double validNum = rand() % (0 - 1) + 1;
            if (validNum >= threshold) {
                maze[i*maze_width+j] = "#";
            }else {
                maze[i*maze_width+j] = " ";
            }
                    
        }
    }
  
}

// The function to release the solution path
void releaseSolution(char** sol) {
  if (*sol) releaseChars(sol);
}

// The function to release dynamically allocated array of characters
void releaseChars(char** p) {
  // TODO: implement this function
}
