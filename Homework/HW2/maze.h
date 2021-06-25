#ifndef __MAZE_H__
#define __MAZE_H__

/**
 * \file maze.h
 * \brief Provides maze-related functionalities
 *
 * \details This header file declares all maze-related functionalities for reading/writing/solving/generating the maze and releasing related memories.
 */

/**
 * \brief The function to read the maze from a file
 *
 * \details This function takes four parameters: a constant c-string that is the file to read, a pointer to the maze (which is a pointer to an array of characters), and two integer pointers to the maze's width and height. The function reads the file, allocates memory for the maze, and fill in maze's data, width and height. It returns 0 on succeed, -1 if failed to open the file to read, or -2 if encountering any read error.
 * 
 * \param[in] filename      A constant c-string, which is the input filename
 * \param[out] maze         A pointer to the maze, which is a pointer of an array of characters that represents the maze's data
 * \param[out] maze_width   A pointer to an integer, which is the maze's width
 * \param[out] maze_height  A pointer to an integer, which is the maze's height
 *
 * \return  The return code of the function
 * \retval  0  if succeed (no errors)
 * \retval  -1 if failed to open the file to read
 * \retval  -2 if encountering any read error
 */
int readMaze(const char* filename, char** maze, int* maze_width, int* maze_height);

/**
 * \brief The function to write the maze to a file
 *
 * \details This function takes four parameters: a constant c-string that is the file to write, a constant pointer to the maze (which is a pointer to an array of characters), and two constant integer that are the maze's width and height. The function writes the maze's data, width and height to the specified file. It returns 0 on succeed, -4 if failed to open the file to write, or -5 if encountering any write error.
 * 
 * \param[in] filename      A constant c-string, which is the input filename
 * \param[in] maze          A constant pointer to the maze, which is a pointer of an array of characters that represents the maze's data
 * \param[in] maze_width    A constant integer, which is the maze's width
 * \param[in] maze_height   A constant integer, which is the maze's height
 *
 * \return  The return code of the function
 * \retval  0  if succeed (no errors)
 * \retval  -4 if failed to open the write to read
 * \retval  -5 if encountering any write error
 */
int writeMaze(const char* filename, const char* maze, const int maze_width, const int maze_height);

/**
 * \brief The function to release the maze's data
 *
 * \details This function takes a parameter that is a pointer to the maze (which is a pointer to an array of characters). It calls releaseChars function to release the dynamically allocated memory of the maze's data and reset the pointer to NULL.
 * 
 * \param[in,out] maze      A pointer to the maze, which is a pointer of an array of characters that represents the maze's data
 */
void releaseMaze(char** maze);

/**
 * \brief The function to solve a solution path for the maze
 *
 * \details This function takes four parameters: a constant pointer to the maze (which is a pointer to an array of characters), two constant integers that are the maze's width and height, and a pointer to the solution path (which is a pointer to an array of characters). The function allocates memory for the solution path, and calls solvePath to find a solution path for the maze. It returns 0 if a solution path is found; otherwise return 1.
 * 
 * \param[in]   maze          A constant pointer to the maze, which is a pointer of an array of characters that represents the maze's data
 * \param[in]   maze_width    A constant integer, which is the maze's width
 * \param[in]   maze_height   A constant integer, which is the maze's height
 * \param[out]  sol           A pointer to the solution path, which is a pointer of an array of characters that represents the maze's data
 *
 * \return  The return code of the function
 * \retval  0  if a solution path is found
 * \retval  1  if no solution path is found
 */
int solveMaze(const char* maze, const int maze_width, const int maze_height, char** sol);

/**
 * \brief The function to solve a solution path recursively
 *
 * \details This function takes six parameters: a constant pointer to the maze (which is a pointer to an array of characters), two constant integers that are the maze's width, two constant integers that are the current column and row positions, and a pointer to the current solution path (which is a pointer to an array of characters stores the information from the start position to the current position). The function checks if the current path is a solution path. It returns 0 if a solution path is found; otherwise it extends the current path to its neighbor (following this order: left, right, up, down) and recursively calls solvePath to find a solution path.  If no solution path is found, it returns 1.
 * 
 * \param[in]     maze          A constant pointer to the maze, which is a pointer of an array of characters that represents the maze's data
 * \param[in]     maze_width    A constant integer, which is the maze's width
 * \param[in]     maze_height   A constant integer, which is the maze's height
 * \param[in]     col           A constant integer, which is the current column position
 * \param[in]     row           A constant integer, which is the current row position
 * \param[in,out] sol           A pointer to the solution path, which is a pointer of an array of characters that represents the current path from start position to current position
 *
 * \return  The return code of the function
 * \retval  0  if a solution path is found
 * \retval  1  if no solution path is found
 */
int solvePath(const char* maze, const int maze_width, const int maze_height, const int col, const int row, char* sol);

/**
 * \brief The function to generate a maze
 *
 * \details This function takes five parameters: a pointer to the maze (which is a pointer to an array of characters), two constant integers that are the maze's width, a constant double that is a threshold to determine whether a position is a wall, and a constant integer that specifies the seed for C pseudorandom number generator. The function allocates memory for the maze based on the input maze's size and it generates the start and target positoins, and the maze's walls using C pseudorandom number initialized by the input seed. The wall generation is determined by the input threshold.
 * 
 * \param[out]  maze          A pointer to the maze, which is a pointer of an array of characters that represents the maze's data
 * \param[in]   maze_width    A constant integer, which is the maze's width
 * \param[in]   maze_height   A constant integer, which is the maze's height
 * \param[in]   threshold     A constant double, which is the threshold used to determine if a wall should be generated
 * \param[in]   seed          A constant integer, which is the seed for C pseudorandom number generator
 */
void genMaze(char** maze, const int maze_width, const int maze_height, const double threshold, const int seed);

/**
 * \brief The function to release the solution path
 *
 * \details This function takes a parameter that is a pointer to the solution path (which is a pointer to an array of characters). It calls releaseChars function to release the dynamically allocated memory of the solution path and reset the pointer to NULL.
 * 
 * \param[in,out] sol         A pointer to the solution path, which is a pointer of an array of characters that represents the maze's data
 */
void releaseSolution(char** sol);

/**
 * \brief The function to release dynamically allocated array of characters and resets the pointer to NULL
 *
 * \details This function takes a parameter that is a pointer to the solution path (which is a pointer to an array of characters). It releases the dynamically allocated memory of array of characters and resets the pointer to NULL.
 * 
 * \param[in,out] p           A pointer to a dynamically allocated array of characters
 */
void releaseChars(char** p);

#endif // __MAZE_H__