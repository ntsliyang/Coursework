#include <iostream>

using namespace std;

int board[4];

// check if row, col is a valid position to place the queen
bool okayPosition(int row, int col) {
	for (int i = 0; i < row; i++)
	{
		int other_row_pos = board[i];
 
		if (other_row_pos == col || 
			other_row_pos == col - (row - i) ||
			other_row_pos == col + (row - i))
			return false;
	}
	return true;
}

bool solveNQueens(int row) {
	if (row == 4) { 
		// at this point we've hit the end of the board
		cout << "Solution: ";
		for (int i = 0; i < 4; i++) {	
			cout << board[i] << " ";
		}
		cout << endl;
		return true;
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			if (okayPosition(row, i))
			{
				board[row] = i;
				if(solveNQueens(row + 1)) return true;
			}
		}
	}
	return false;
}

int main(){
	for(int i = 0; i < 4; i++) {
		board[i] = 0;
	}
	solveNQueens(0);
	return 0;
}