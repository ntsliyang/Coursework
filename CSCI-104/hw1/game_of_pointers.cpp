#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

struct Warrior
{
	string weapon;
	int power;
};

// identify open positions in the invading army
Warrior *helper(Warrior ***invaders, int rows, int columns)
{
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			if (invaders[i][j]->weapon == "")
			{
				return invaders[i][j];
			}
		}
	}
	return NULL;
}

//Feel free to modify the parameters if you need other values
bool skirmish(Warrior ***protectors, Warrior ***invaders, int skirmish_row,
			  int rows, int columns, int &reserves, ofstream &output)
{
	if (skirmish_row >= columns)
		return false;
	else
	{
		int r = 0;
		while (r < rows)
		{
			if (invaders[skirmish_row][r]->weapon == "")
			{
				output << "No assault" << endl;
			}
			if (invaders[skirmish_row][r]->weapon != "" 
				&& protectors[r][skirmish_row]->weapon == "")
			{
				// the walls are breached and invaders are immediately winners
				return true;
			}

			if (protectors[r][skirmish_row]->weapon == "axe" 
				&& invaders[skirmish_row][r]->weapon == "sword")
			{ // invader loses their duel
				output << "Invader killed" << endl;
				// and there are open positions in the invading army
				invaders[skirmish_row][r]->weapon = "";
				invaders[skirmish_row][r]->power = -1;
			}
			else if (protectors[r][skirmish_row]->weapon == "sword" 
				&& invaders[skirmish_row][r]->weapon == "axe")
			{
				// protector loses their duel
				Warrior *result = helper(invaders, rows, columns);
				// and there are open positions in the invading army
				if (result != NULL)
				{
					*result = *(protectors[r][skirmish_row]);
					protectors[r][skirmish_row]->weapon = "";
					protectors[r][skirmish_row]->power = -1;
					output << "Protector defected" << endl;
				}
				else
				{
					protectors[r][skirmish_row]->weapon = "";
					protectors[r][skirmish_row]->power = -1;
					output << "Protector killed" << endl;
				}

				if (reserves > 0)
				{
					protectors[r][skirmish_row]->weapon = "axe";
					protectors[r][skirmish_row]->power = 100;
					reserves--;
				}
				else
				{
					protectors[r][skirmish_row]->weapon = "";
					protectors[r][skirmish_row]->power = -1;
				}
			}
			else
			{
				if (protectors[r][skirmish_row]->power >= 0 
					&& invaders[skirmish_row][r]->power >= 0)
				{
					if (protectors[r][skirmish_row]->power 
						> invaders[skirmish_row][r]->power)
					{
						output << "Invader killed" << endl;
						// and there are open positions in the invading army
						invaders[skirmish_row][r]->weapon = "";
						invaders[skirmish_row][r]->power = -1;
					}
					else if (protectors[r][skirmish_row]->power 
						< invaders[skirmish_row][r]->power)
					{
						// protector loses their duel 
						Warrior *result = helper(invaders, rows, columns);
						// and there are open positions in the invading army
						if (result != NULL)
						{
							*result = *(protectors[r][skirmish_row]);
							protectors[r][skirmish_row]->weapon = "";
							protectors[r][skirmish_row]->power = -1;
							output << "Protector defected" << endl;
						}
						else
						{
							protectors[r][skirmish_row]->weapon = "";
							protectors[r][skirmish_row]->power = -1;
							output << "Protector killed" << endl;
						}

						if (reserves > 0)
						{
							protectors[r][skirmish_row]->weapon = "axe";
							protectors[r][skirmish_row]->power = 100;
							reserves--;
						}
						else
						{
							protectors[r][skirmish_row]->weapon = "";
							protectors[r][skirmish_row]->power = -1;
						}
					}
					else
					{
						output << "Duel ends in draw" << endl;
					}
				}
			}
			r++;
		}
	}
	return false;
	//returns true if the invaders breach the walls.
}

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		cerr << "Please provide an input and output file" << endl;
		return -1;
	}

	ifstream input(argv[1]);
	ofstream output(argv[2]);

	int rows;
	int cols;
	int reserve;
	int skirmishes;

	input >> rows >> cols >> reserve >> skirmishes;
	//read the input file and initialize the values here.

	Warrior ***protectors = new Warrior **[rows];
	Warrior ***invaders = new Warrior **[cols];

	for (int i = 0; i < rows; i++)
	{
		protectors[i] = new Warrior *[cols];
	}

	for (int i = 0; i < cols; i++)
	{
		invaders[i] = new Warrior *[rows];
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			protectors[i][j] = new Warrior;
			if (i % 2 == 0)
			{
				protectors[i][j]->weapon = "axe";
			}
			else
			{
				protectors[i][j]->weapon = "sword";
			}
			protectors[i][j]->power = i * 10 + (j + 1) * 10;
		}
	}

	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			invaders[i][j] = new Warrior;
			if (i % 2 == 1)
			{
				invaders[i][j]->weapon = "axe";
			}
			else
			{
				invaders[i][j]->weapon = "sword";
			}
			invaders[i][j]->power = i * 10 + (j + 1) * 10;
		}
	}
	//initialize the protectors and invaders here.

	bool end;
	for (int i = 1; i <= skirmishes; i++)
	{
		int skirmish_row;
		input >> skirmish_row;
		//read the input file to find the value for skirmish row

		//In general, it is bad style to throw everything into your main function
		end = skirmish(protectors, invaders, 
			skirmish_row, rows, cols, reserve, output);
		if (end == true)
		{
			output << "Winner: invaders";
			break;
		}
	}
	if (end == false)
	{
		output << "Winner: protectors";
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			delete protectors[i][j];
		}
	}

	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			delete invaders[i][j];
		}
	}

	for (int i = 0; i < rows; i++)
	{
		delete[] protectors[i];
	}

	for (int i = 0; i < cols; i++)
	{
		delete[] invaders[i];
	}

	delete[] protectors;
	delete[] invaders;

	input.close();
	output.close();
	//output the winner and deallocate your memory.

	return 0;
}