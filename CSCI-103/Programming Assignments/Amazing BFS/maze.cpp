/* 
maze.cpp

Author: Yang Li

Short description of this file:

Using BFS search to find the shortest path from
'S' to 'F'
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char **, int, int);

// main function to read, solve maze, and print result
int main()
{
    int rows, cols, result;
    char **mymaze;

    cin >> rows >> cols;

    mymaze = read_maze(&rows, &cols); // FILL THIS IN

    if (mymaze == NULL)
    {
        cout << "Error, input format incorrect" << endl;
        return 1;
    }

    result = maze_search(mymaze, rows, cols); 

    // examine value returned by maze_search and print appropriate output
    if (result == 1)
    { // path found!
        print_maze(mymaze, rows, cols);
    }
    else if (result == 0)
    { // no path :(
        cout << "No path could be found!" << endl;
    }
    else
    { // result == -1
        cout << "Invalid maze." << endl;
    }

    // ADD CODE HERE to delete all memory
    // that read_maze allocated
    for (int i = 0; i < rows; i++)
    {
        delete[] mymaze[i];
    }
    delete[] mymaze;

    return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 * -1 if invalid maze (not exactly one S and one F)
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 *************************************************/
int maze_search(char **maze, int rows, int cols)
{
    int num_S = 0;
    int num_F = 0;
    Queue q(rows * cols);
    Location curr;
    Location loc;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (maze[i][j] == 'S')
            {
                num_S++;
                curr.row = i;
                curr.col = j;
                q.add_to_back(curr);
            }

            if (maze[i][j] == 'F')
            {
                num_F++;
            }
        }
    }

    bool **visited = new bool *[rows];
    for (int i = 0; i < rows; i++) {
    	visited[i] = new bool [cols];
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            visited[i][j] = false;
        }
    }

    Location **pred = new Location *[rows];
    for (int i = 0; i < rows; i++) {
    	pred[i] = new Location [cols];
    }

    if (!(num_F == 1 && num_S == 1))
    {
        for (int i = 0; i < rows; i++) {
            delete [] visited[i];
        }
        delete [] visited;

        
        for (int i = 0; i < rows; i++) {
            delete [] pred[i];
        }
        delete [] pred;
        return -1;
    }
    else
    {
        bool flag = false; 
        // flag that helps to determine the validity of the maze
        Location next;
        int dx[] = {0, -1, 0, 1};
		int dy[] = {-1, 0, 1, 0};
        while (q.is_empty() != true && flag == false)
        {
            loc = q.remove_from_front();
            next = loc;
                for (int j = 0; j < 4; j++) {
                    next.row = loc.row + dy[j];
                    next.col = loc.col + dx[j];
                    if (next.row >= 0 && next.row < rows && 
                    	next.col >= 0 && next.col < cols) {
                        if (maze[next.row][next.col] == '.' && 
                        	visited[next.row][next.col] == false) {
                            q.add_to_back(next); 
                            // add to back of the queue;   
                            visited[next.row][next.col] = true; 
                            // mark it as visited
                            pred[next.row][next.col] = loc; 
                            // record its predecessor
                        }

                        if (maze[next.row][next.col] == 'F') {
                            flag = true;
                            pred[next.row][next.col] = loc;
                            break;
                        }
                    }
                      
                }
        }

        while (maze[loc.row][loc.col] != 'S')
        {
            maze[loc.row][loc.col] = '*';
            loc = pred[loc.row][loc.col];
        }

        for (int i = 0; i < rows; i++) {
            delete [] visited[i];
        }
        delete [] visited;

        
        for (int i = 0; i < rows; i++) {
            delete [] pred[i];
        }
        delete [] pred;

        if (flag == false) {
            return 0;
        }

        return 1;
    }
}