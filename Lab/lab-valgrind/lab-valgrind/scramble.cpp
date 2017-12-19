// wscramble.cpp
// Word Scramble guessing game
// Illustrates string library functions, character arrays,
//  arrays of pointers, etc.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream>
using namespace std;

// Scramble the letters of this string randomly
void permute(char items[], int len);

// Define an array of strings (an array of char pointers, like argv)

int main(int argc, char* argv[])
{
  if (argc < 2) {
    cout << "Please enter the name of the file to read as an argument" << endl;
    return 1;
  }

  ifstream ifile("wordbank.txt");
  if (ifile.fail()){
    cout << "Couldn't open file" << endl;
    return 1;
  }
  
  int numWords;
  ifile >> numWords;
  if (ifile.fail()) {
    cout << "Unable to read the file successfully" << endl;
    return 1;
  }

  char* wordBank[numWords];
  char buffer[41];
  for (int i = 0; i < numWords; i++) {
    ifile >> buffer;
    wordBank[i] = new char[strlen(buffer) + 1];
    strcpy(wordBank[i], buffer);
  }

  srand(time(0));
  char guess[80];

  bool wordGuessed = false;
  int numTurns = 10;

  // Pick a random word from the wordBank
  int target = rand() % numWords;
  int targetLen = strlen(wordBank[target]);

  // Make a dynamically-allocated copy of the word and scramble it
  char *word = new char[targetLen + 1];
  strcpy(word, wordBank[target]);
  permute(word, targetLen);

  // An individual game continues until a word
  //  is guessed correctly or 10 turns have elapsed
  while (!wordGuessed && numTurns > 0)
  {
    cout << "Scrambled word: " << word << endl;
    cout << "What do you guess the original word is? ";
    cin >> guess;
    wordGuessed = (strcmp(guess, wordBank[target]) == 0);
    numTurns--;
  }
  if (wordGuessed)
  {
    cout << "You win!" << endl;
  }
  else
  {
    cout << "Too many turns...You lose!" << endl;
  }

  delete[] word;
  for (int i = 0; i < numWords; i++) {
    delete [] wordBank[i];
  }
  ifile.close();
  return 0;
}

// Scramble the letters. See "Knuth shuffle" on Wikipedia.
void permute(char items[], int len)
{
  for (int i = len - 1; i > 0; --i)
  {
    int r = rand() % i;
    char temp = items[i];
    items[i] = items[r];
    items[r] = temp;
  }
}
