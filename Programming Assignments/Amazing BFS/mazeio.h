/* 
mazeio.h

Author: CS 103 Course Staff

Description: Input and output routines for BFS assignment.

You shouldn't change this file.
*/

#ifndef MAZEIO_H
#define MAZEIO_H

// read maze from cin, allocate and return maze 2D array,
// fill in rows and cols
char** read_maze(int* rows, int* cols);

// print maze to cout
void print_maze(char** maze, int rows, int cols);

#endif
