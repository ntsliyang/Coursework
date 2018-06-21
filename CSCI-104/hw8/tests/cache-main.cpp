#include "../cacheLRU.h"
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char **argv) {
	// Read from file
	if (argc < 2) {
		cerr << "Please provide input file!" << endl;
		return 0;
	}
	ifstream fin(argv[1]);
	if (fin.fail()) {
		cerr << "I don't understand." << endl;
		return 0;
	}
	// Size of cache
	int cacheSize = 100;
	if (argc > 2) {
		cacheSize = atoi(argv[2]);
	}
	cacheLRU<string, bool> data(cacheSize);
	cout << "Cache capacity: " << cacheSize << endl;
	// Read from file
	int N = 0;
	string cur;
	while (fin >> cur) {
		while (cur.size() && !isalnum(cur[0]))
			cur = cur.substr(1);
		while (cur.size() && !isalnum(cur.back()))
			cur.pop_back();
		if (cur.size()) {
			data.put(make_pair(cur, true));
			N++;
		}
	}
	cout << "Total number of words: " << N << endl;
	return 0;
}