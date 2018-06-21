#include <iostream>
#include "hashtable.h"

using namespace std;

int main() {
	HashTable users(10);

	users.insert("Erika");
	users.insert("Ruyan");

	users.insert("Peter");
	users.insert("Peter");
	users.insert("Peter");
	users.insert("Peter");

	users.insert("Nikhil");
	users.insert("Nisar");
	users.insert("Aaron");
	users.insert("Ashley");
	users.insert("Mark");
	users.insert("Kyle");
	users.insert("Ellen");

	cout << "Trying to find Arush: " << (users.find("Arush") ? "BAD" : "GOOD") << endl;
	cout << "Trying to find Peter: " << (users.find("Peter") ? "GOOD" : "BAD") << endl;
	cout << "Trying to find Mark: " << (users.find("Mark") ? "GOOD" : "BAD") << endl;
	cout << "Trying to find Erika: " << (users.find("Erika") ? "GOOD" : "BAD") << endl;

	users.insert("Arush");
	cout << "Trying to find Arush: " << (users.find("Arush") ? "GOOD" : "BAD") << endl;

	users.remove("Peter");
	users.remove("Mark");
	cout << "Trying to find Peter: " << (users.find("Peter") ? "BAD" : "GOOD") << endl;
}