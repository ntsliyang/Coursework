#include "webpage.h"
#include <iostream>
using namespace std;

void printstringset(set<string> s) {
	for (auto it = s.begin(); it != s.end(); it++) {
		cout << (*it) << ' ';
	}
	cout << endl;
}

int main(int argc, char* argv[]) {
	WebPage* wp;
	set<WebPage*> wpset;
	ifstream index(argv[1]);
	if (index.fail()) {
		cout << "please provide proper input files" << endl;
		return -1;
	}
	string line;
	while (getline(index, line)) {
		ifstream ifile(line); // ifile refers to a single file 
		if (ifile.fail()) {
			cout << "Invalid query" << endl;
			return -1;
		}
		string line2;
		while (getline(ifile, line2)) {
			cout << line2 << endl;
			wp->wordsParse(line2); // parse the words and outlinks
		}
		wpset.insert(wp); // insert individual webpage into the set 
		ifile.close(); // close the single file
	}

	for (auto it = wpset.begin(); it != wpset.end(); it++) {
		(*it)->inlinksParse(wpset, (*it));
	}
	
	for (auto it = wpset.begin(); it != wpset.end(); it++) {
		printstringset((*it)->getInlinks()); // WebPage* it
		printstringset((*it)->getOutlinks()); // WebPage* it
		printstringset((*it)->getWords()); // WebPage* it
	}

	index.close();
	return 0;
}