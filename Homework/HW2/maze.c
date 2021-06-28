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

  int firstline[2] = {maze_width, maze_height}; 
 
  //open mazeFile  
  FILE*mazeFile = fopen(filename, "w");
    
  // reading error
  if (mazeFile == NULL) {
      return -4;
  }

  // writing error
  if (ferror(mazeFile)) {
      return -5;
  }
  
  if (mazeFile) {
    //Write width and height on the top of the file
    //fwrite(firstline, sizeof(firstline), sizeof(int), mazeFile);
    fprintf(mazeFile,"%d %d\n",maze_width,maze_height);
    for (int i = 0; i < maze_height; i++) {
      for (int j = 0; j < maze_width; j++) {
          fprintf(mazeFile,"%c", (maze)[i* maze_width + j]); //one dim = needs dereference, prioritize deref()  
      }
      fprintf(mazeFile,"\n"); //& = address / turning it to the pointer                               
  }

    //Write data to the file
    // fwrite(maze, sizeof(maze), sizeof(char),  mazeFile);
      
  }
  fclose(mazeFile);
  return 0;
}

// The function to release the maze's data
void releaseMaze(char** maze) {
  if (*maze) releaseChars(maze);
    
    //deallocate the dynamically allocated array 
    free(*maze);
    maze = NULL;
}

// The function to solve a solution path for the maze
int solveMaze(const char* maze, const int maze_width, const int maze_height, char** sol) {
  *sol = malloc(sizeof(char) * maze_width * maze_height);

  int col;
  int row;
  for (int i = 0; i < maze_height; i++) {
      for (int j = 0; j < maze_width; j++) {
	(*sol)[i * maze_width + j] = 'u';
	if ((maze)[i * maze_width + j] == '@') {
	  col = j;
	  row = i;
	 
	}
      }
  }
  

  return solvePath(maze, maze_width, maze_height, col, row, *sol); // TODO: replace this stub
}

// The function to solve a solution path recursively
int solvePath(const char* maze, const int maze_width, const int maze_height, const int col, const int row, char* sol) {
  if (maze[row * maze_width + col] == '<' ) {
      return 0;
  }
  else if (maze[row * maze_width + col] == '#' || sol[row * maze_width + col] == 'v'){
    
    return 1;
    
  }
  sol[row * maze_width + col] = 'v';
 
      if (solvePath(maze, maze_width, maze_height, col - 1, row, sol) == 0) { //left
	sol[row * maze_width + col] = '*';
	return 0;
          
      }
      if (solvePath(maze, maze_width, maze_height, col + 1, row, sol)==0) { //right
	sol[row * maze_width + col] = '*';
	return 0;
          
      }
      if (solvePath(maze, maze_width, maze_height, col, row - 1, sol)==0) { //up
	sol[row * maze_width + col] = '*';
	return 0;
          
      }
      if (solvePath(maze, maze_width, maze_height, col, row + 1, sol)==0) { //down
	sol[row * maze_width + col] = '*';
	return 0;
      }
														 
      return 1;
}

// The function to generate a maze
void genMaze(char** maze, const int maze_width, const int maze_height, const double threshold, const int seed) {

  int size;
  size = maze_width * maze_height;
    *maze = malloc(sizeof(char) * size);
  
    //Initiallize a random seed
    srand(seed);
    
    // Generate a start position 
    int column_s = (rand() % (maze_width - 2)) + 1;
    int row_s = (rand() % (maze_height - 2)) + 1;
    
    
    // Generate an end position
    int column_e = (rand() % (maze_width - 2)) + 1;
    int row_e = (rand() % (maze_height - 2)) + 1;


    for (int i = 0; i < maze_height; i++) {
      for (int j = 0; j < maze_width; j++){
            // Set the boundary walls 
	  if (i == 0||i == maze_height - 1||j == 0||j == maze_width - 1) {
	   (*maze)[i*maze_width+j] = '#';

	   
	  } else if (i == row_s && j == column_s) {
	    (*maze)[i*maze_width+j] = '@';
	   
	  } else if (i == row_e && j == column_e) {
	   (*maze)[i*maze_width+j] ='<';

	  } else {
	    double validNum = (double)rand()/RAND_MAX;
	    if (validNum >= threshold) {
	      (*maze)[i*maze_width+j] = '#';
	     
	    } else {
	     (*maze)[i*maze_width+j] = ' ';

	    }
	  }
                    
        }
    }
   
  
}


// The function to release the solution path
void releaseSolution(char** sol) {
  if (*sol) releaseChars(sol);
  free(*sol);
  *sol = NULL;

}

// The function to release dynamically allocated array of characters
void releaseChars(char** p) {
  free(*p);
  *p = NULL;
 }
