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
	int command;
	cout << "The following is the menu of options. Please choose one." << endl;
	cout << "Option 1. Add a user" << endl;
	cout << "Option 2. Add friend connection" << endl;
	cout << "Option 3. Remove friend connection" << endl;
	cout << "Option 4. Print users" << endl;
	cout << "Option 5. List friends" << endl;
	cout << "Option 6. Write to file" << endl;
	cout << "Option 7. Compute the shortest distance between two users" << endl;
	cout << "Option 8. List sets of Users in each set" << endl;
	cout << "Option 9. List suggested friends" << endl;
	do {
		cin >> command;
		if (command == 1) {
			string first_name;
			string last_name;
			int birth_year;
			int zip_code;
			cin >> first_name >> last_name >> birth_year >> zip_code;
			string name = first_name + " " + last_name;
			nw.add_user(name, birth_year, zip_code);
		}
		else if (command == 2) {
			string first_name1;
			string last_name1;
			string first_name2;
			string last_name2;
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
			cin >> first_name >> last_name;
			string username = first_name + " " + last_name;
			nw.printfriends(username);
			cin.ignore(256, '\n');
		}
		else if (command == 6) {
			string temp;
			cin >> temp;
			const char* filename = temp.c_str();
			int out = nw.write_friends(filename);
			if (out == 0) {
				cin.ignore(256, '\n');
			}
		}
		else if (command == 7) {
			string first_name1;
			string last_name1;
			string first_name2;
			string last_name2;
			cin >> first_name1 >> last_name1 >> first_name2 >> last_name2;
			string username1 = first_name1 + " " + last_name1;
			string username2 = first_name2 + " " + last_name2;
			if (username1 == username2) {
				cout << "Distance: 0" << endl;
				cout << username1 << endl;
			}
			else {
				int id1 = nw.get_id(username1);
				int id2 = nw.get_id(username2);
				vector<int> v = nw.shortest_path(id1, id2);
				for (int i = 0; i < v.size(); i++) {
					cout << v[i] << ' ';
				}
				cout << endl;
				nw.print_shortest_path();
				cin.ignore(256, '\n');
			}
		}
		else if (command == 8) {
			vector<vector<int> > v = nw.groups();
			nw.print_groups(v);
			cin.ignore(256, '\n');
		}
		else if (command == 9) {
			string first_name;
			string last_name;
			cin >> first_name >> last_name;
			string username = first_name + " " + last_name;
			int id = nw.get_id(username);
			int score;
			vector<int> friend_ids = nw.suggest_friends(id, score);
			nw.print_suggest_friends(friend_ids);
			cin.ignore(256, '\n'); 
		}

		else {
			return 0;
		}
	} while (command >= 1 && command <= 9);

	return 0;
}