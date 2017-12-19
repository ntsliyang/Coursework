#include "network.h"
#include "user.h"
#include <iomanip>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
int main(int argc, char *argv[])
{
	if (argc < 2) {
		cout << "No filename error" << endl;
	}

	Network nw;
	nw.read_friends(argv[1]);
//	nw.printall();
	int command;
	cout << "The following is the menu of options. Please choose one." << endl;
	cout << "Option 1. Add a user" << endl;
	cout << "Option 2. Add friend connection" << endl;
	cout << "Option 3. Remove friend connection" << endl;
	cout << "Option 4. Print users" << endl;
	cout << "Option 5. List friends" << endl;
	cout << "Option 6. Write to file" << endl;
	cout << "Option 7. Exit the program" << endl;
	do {
		cin >> command;
		if (command == 1) {
//			cin.ignore(256, '\n');
			string first_name;
			string last_name;
//			string name;
			int birth_year;
			int zip_code;
//			string line;
//			getline(cin, line);
//			stringstream ss(line);
//			int year;
//			int zip;
			cin >> first_name >> last_name >> birth_year >> zip_code;
//			int year = static_cast<int> (birth_year);
//			int zip = static_cast<int> (zip_code);
			string name = first_name + " " + last_name;
			nw.add_user(name, birth_year, zip_code);
		}
		else if (command == 2) {
			string first_name1;
			string last_name1;
			string first_name2;
			string last_name2;
//			string line;
//			getline(cin, line);
//			stringstream ss(line);
			cin >> first_name1 >> last_name1 >> first_name2 >> last_name2;
			string username1 = first_name1 + " " + last_name1;
			string username2 = first_name2 + " " + last_name2;
			cout << username1 << endl;
			cout << username2 << endl;
			int out = nw.add_connection(username1,username2);
			if (out == 0) {
				cin.ignore(256, '\n');
			} 
			else {
				cout << "Please input valid usernames" << endl;
			}
		}
		else if (command == 3) {
			string first_name1;
			string last_name1;
			string first_name2;
			string last_name2;
//			string line;
//			getline(cin, line);
//			stringstream ss(line);
			cin >> first_name1 >> last_name1 >> first_name2 >> last_name2;
			string username1 = first_name1 + " " + last_name1;
			string username2 = first_name2 + " " + last_name2;
			int out = nw.remove_connection(username1, username2);
			if (out == 0) {
				cin.ignore(256, '\n');
			}
			else {
				cout << "Please input valid usernames" << endl;
				return 0;
			}
		}
		else if (command == 4) {
			nw.printall();
			cin.ignore(256, '\n');
		}
		else if (command == 5) {
			string first_name;
			string last_name;
//			string line;
//			getline(cin, line);
//			stringstream ss(line);
			cin >> first_name >> last_name;
			string username = first_name + " " + last_name;
			nw.printfriends(username);
			cin.ignore(256, '\n');
		}
		else if (command == 6) {
//			char temp[100];
//			cin >> temp;
//			char* filename = new char [strlen(temp) - 1];
			string temp;
			cin >> temp;
			const char* filename = temp.c_str();
			int out = nw.write_friends(filename);
			if (out == 0) {
				cin.ignore(256, '\n');
			}
//			delete [] filename;
		}
		else {
			return 0;
		}
	} while (command >= 1 && command <= 6);

	return 0;
}