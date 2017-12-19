/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) PA
 * Name: Yang Li
 * USC email: yli546@usc.edu
 * Comments (if available)
 * 
 *
 ******************************************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

/**
 * Global arrays to be used as look-up tables, if desired.
 * It is up to you if and how you want to use these 
 */
const char suit[4] = {'H', 'S', 'D', 'C'};
const char *type[13] =
	{"2", "3", "4", "5", "6", "7",
	 "8", "9", "10", "J", "Q", "K", "A"};
const int value[13] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};


/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */
 void shuffle(int cards[]) {
	for (int i = 0; i < NUM_CARDS; i++) {
		cards[i] = i;
	}
	// fill the array with number from 0 to 51
	for (int i = NUM_CARDS-1; i >= 1; i--) {
		int j = rand() % (i+1); 
		int temp = cards[j];
		cards[j] = cards[i];
		cards[i] = temp;
	}
	// shuffle cards according to Fisher-Yates / Durstenfeld shuffle algorithm
}


/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 */
void printCard(int id)
{
	/******** You complete ****************/
	cout << type[id % 13] << '-' << suit[id / 13];
}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
*/
int cardValue(int id)
{
	/******** You complete ****************/
	return value[id % 13];
}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.  
 * Should use printCard() to print out each card.
*/ 
void printHand(int hand[], int numCards)
{
	/******** You complete ****************/
	for (int i = 0; i < numCards; i++) {
		printCard(hand[i]);
		cout << ' ';
	}
	// print the hand of cards that all before numCards 

	cout << endl;
}

/**
 * Should return the total score of the provided hand.  
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
*/
int getBestScore(int hand[], int numCards)
{
	/******** You complete ****************/
	int sum = 0; 
	for (int i = 0; i < numCards; i++) {
		sum += cardValue(hand[i]);
	}
	// calculate the sum of cards

	for (int i = 0; i < numCards; i++) {
		if (sum > 21 && cardValue(hand[i]) == 11) {
			sum -= 10;
		}
	}
	// handle the value of aces when sum is larger than 21

	return sum;
}

/**
 * Main program logic for the game of 21
 */
int main(int argc, char *argv[])
{
	//---------------------------------------
	// Do not change this code -- Begin
	//---------------------------------------
	if (argc < 2)
	{
		cout << "Error - Please provide the seed value." << endl;
		return 1;
	}
	
	int seed = atoi(argv[1]);
	srand(seed);

	int dhand[9];
	int phand[9];
	int cards[NUM_CARDS];
	char command;
	// command stands for 'hit' or 'stay'
	char yes_no;

	
	while (true) {
		for (int i = 0; i < NUM_CARDS; i++) {
			cards[i] = i;
		}

		shuffle(cards);

		phand[0] = cards[0];
		dhand[0] = cards[1];
		phand[1] = cards[2];
		dhand[1] = cards[3];
		// deal the shuffled cards in an alternating fashion

		int count_dhand = 2;
		int count_phand = 2;
		int cards_initial = 3;
		int dhand_initial = 1;
		int phand_initial = 1;
		// initialize some variables to represent 'numCards' for dealer and player

		cout << "Dealer: " << "? ";
		printCard(cards[3]);
		cout << endl;
		cout << "Player: ";
		printHand(phand, 2);
		// print the initial state for player and dealer


		while (true) {
			if (getBestScore(phand, count_phand) == 21) {
				while (getBestScore(dhand, count_dhand) < 17) {
					count_dhand++;
					dhand_initial++;
					cards_initial++;
					dhand[dhand_initial] = cards[cards_initial];
				}
				// when dealer has a value of less than 17,
				// he / she would still need to draw cards
				if (getBestScore(dhand, count_dhand > 21)) {
					cout << "Dealer busts" << endl;
				}
				cout << "Dealer: ";
				printHand(dhand, count_dhand);
				cout << "Win " << getBestScore(phand, count_phand);
				cout << ' ' << getBestScore(dhand, count_dhand);
				cout << endl;
				break;
			}
			// if player initially has cards' value equal to 21,
			// he / she would not need to hit or stay


			cout << "Type 'h' to hit and 's' to stay:" << endl;
			cin >> command;
			if (command == 'h') {
				count_phand++;
				phand_initial++;
				cards_initial++;
				phand[phand_initial] = cards[cards_initial];
				if (getBestScore(phand, count_phand) > 21) {
					cout << "Player: "; 
					printHand(phand, count_phand);
					cout << endl;
					cout << "Player busts" << endl;
					cout << "Lose " << getBestScore(phand, count_phand); 
					cout << ' ' << getBestScore(dhand, count_dhand);
					cout << endl;
					break;
				}

				else if (getBestScore(phand, count_phand) < 21) {
					cout << "Player: ";
					printHand(phand, count_phand);
					cout << endl;
				}

			}

			else if (command == 's') {
				while (getBestScore(dhand, count_dhand) < 17) {
					count_dhand++;
					dhand_initial++;
					cards_initial++;
					dhand[dhand_initial] = cards[cards_initial];
				}
				// when dealer has a score of less than 17, 
				// he / she would still need to draw cards
				cout << "Dealer: ";
				printHand(dhand, count_dhand);
				if (getBestScore(dhand, count_dhand) > 21) {
					cout << "Dealer busts" << endl;
					cout << "Win " << getBestScore(phand, count_phand) << ' '; 
					cout << getBestScore(dhand, count_dhand) << endl;
					break;
				}
				// if dealer has cards' value larger than 21, it would bust first
				else if (getBestScore(dhand, count_dhand) > getBestScore(phand, count_phand)) {
					cout << "Lose " << getBestScore(phand, count_phand) << ' '; 
					cout << getBestScore(dhand, count_dhand) << endl;
					break;
				}
				else if (getBestScore(dhand, count_dhand) == getBestScore(phand, count_phand)) {
					cout << "Tie " << getBestScore(phand, count_phand) << ' ';
					cout << getBestScore(dhand, count_dhand) << endl;
					break;
				}
				else {
					cout << "Win " << getBestScore(phand, count_phand) << ' ';
					cout << getBestScore(dhand, count_dhand) << endl;
					break;
				}
				// compare the value between dealer's cards and player's cards
			}			
		}
					
		cout << "Play again? [y/n]" << endl;
		cin >> yes_no;
		if (yes_no == 'y') {
			continue;
		}
		else {
			return 0;
		}
	}

	//---------------------------------------
	// Do not change this code -- End
	//---------------------------------------

	/******** You complete ****************/

	return 0;
}
