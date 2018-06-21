#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

struct Warrior {
    string weapon;
    int power;
};

//Feel free to modify the parameters if you need other values
bool skirmish(Warrior*** protectors, Warrior*** invaders, int skirmish_row,
		      int rows, int columns, int &reserves, ofstream &output){
    //returns true if the invaders breach the walls.
}

int main(int argc, char* argv[])
{
    if (argc < 3) {
	   cerr << "Please provide an input and output file" << endl;
	   return -1;
    }

    ifstream input(argv[1]);
    ofstream output(argv[2]);

    int rows;
    int cols;
    int reserve;
    int skirmishes;

    //read the input file and initialize the values here.

    Warrior ***protectors;
    Warrior ***invaders;

    //initialize the protectors and invaders here.

    for (int i=1; i <= skirmishes; i++){
        int skirmish_row;
        
        //read the input file to find the value for skirmish row
        
        //In general, it is bad style to throw everything into your main function
        bool end = skirmish(protectors, invaders, skirmish_row, rows, cols, reserve, output);
    }

    //output the winner and deallocate your memory.
    
    return 0;
}
