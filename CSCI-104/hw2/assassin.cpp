#include "lliststr.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
	LListStr* list = new LListStr();
	string line;
	string file;
	if (argc == 2) {
		file = argv[1];
	}
	else {
		cin >> file;
	}
	ifstream myfile(file);
	
	if (myfile.fail()) {
		cout << "please input proper files" << endl;
		return 0;
	}
	while (getline(myfile, line)) {
		stringstream ss(line);
		string operation;
		int index;
		string name;
		ss >> operation;
		if (ss.fail()) continue;
		if (operation != "ADD" && operation != "REPLACE" && operation != "ACT") continue;
		if (operation == "ADD") {
			ss >> index;
			if (ss.fail()) continue;
			ss >> name;
			if (ss.fail()) continue;
			else {
				list->insert(index, name);
			}
		}
		else if (operation == "REPLACE") {
			ss >> index;
			if (ss.fail()) continue;
			ss >> name;
			if (ss.fail()) continue;
			else {
				list->set(index, name);
			}
		}
		else if (operation == "ACT") {
			ss >> index;
			if (ss.fail()) continue;
			else {
				if (list->size() == 1) continue;
				if (list->size() > 1) {
					if (list->get(index) != "") {
					// if this is a valid location
						if (list->size() == index + 1) {
							// if the index is not the tail item of the list
							cout << "Assassinated: " << list->get(0) << endl;
							list->remove(0);
						}
						else {
							// if the index is the tail item of the list
							cout << "Assassinated: " << list->get(index + 1) << endl;
							list->remove(index + 1);
						}
					}
					// if there is only one player, then do not modify the game state
				}
			}
		}
	}
	if (list->size() == 1) {
		cout << "Winner: " << list->get(0) << endl;
	}
	else {
		cout << "Remaining Players: " << list->size() << endl;
		for (int i = 0; i < list->size(); i++) {
			cout << list->get(i) << endl;
		}
	}

	delete list;
	return 0;
}