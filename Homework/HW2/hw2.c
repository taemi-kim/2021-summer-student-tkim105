#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
#include "print_functions.h"

/**
 * \file hw2.c
 * \brief The main driver function of HW 2
 *
 * \details This source file implements the main function for HW 2. It checks the input command line arguments and calls the corresponding modules.
 */

int main(int argc, char* argv[]) {
  int return_code = 0;
  
  // check input arguments
  // solve maze: ./hw2 <maze_file>
  // gen maze: ./hw2 <maze_file> <width> <height> [threshold = 0.5] [seed = 0]
  if (/*TODO: Replace this stub*/1) return_code = 2; // invalid input arguments
  else {
    char* maze = NULL;
    int maze_width = 0;
    int maze_height = 0;
    if (argc == 2) { // solve maze
      // read maze file
      return_code = readMaze(argv[1], &maze, &maze_width, &maze_height);
      if (!return_code) {
        // print maze
        printMaze(maze, maze_width, maze_height);
        // solve maze
        char* sol = NULL;
        return_code = solveMaze(maze, maze_width, maze_height, &sol);
        if (!return_code) {
          // print solution
          printSolution(maze, maze_width, maze_height, sol);
        }
        // release solution memory
        releaseSolution(&sol);
      }
    }
    else { // gen maze
      // parse input arguments
      int seed = 0;
      double threshold = 0.5;
      // TODO: add your argument parsing code and input validation code here
      // remember to set the correct return_code
      
      if (!return_code) {
        // gen maze
        genMaze(&maze, maze_width, maze_height, threshold, seed);
        // print maze
        printMaze(maze, maze_width, maze_height);
        // write maze
        return_code = writeMaze(argv[1], maze, maze_width, maze_height);
      }
    }
    // release maze memory
    releaseMaze(&maze);
  }
  
  if (return_code) printError(return_code, argv);
  
  return return_code;
}
