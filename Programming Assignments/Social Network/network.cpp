/*****************************************************
Name: Yang Li
Email: yli546@usc.edu
Description: Based on "user.h" and "network.h", define
different functions connecting different users
*****************************************************/

#include "user.h"
#include "network.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

Network::Network() {
}

Network::~Network() {
}

int Network::read_friends(const char* filename) {
	string first_name;
	string last_name;
	string name;
	int id;
	int birth_year;
	int zip_code;
	string line;
	ifstream ifile (filename);
	if (ifile.fail()) {
		return -1;
	}
	else {
		// use getline and stringstream to read the basic information
		// related to all the users in the friend lists
		getline(ifile, line);
		stringstream ss6(line);
		ss6 >> total_users;
		for (int i = 0; i < total_users; i++) {
			getline(ifile, line);
			stringstream ss1(line);
			ss1 >> id;
			getline(ifile, line);
			stringstream ss2(line);
			ss2 >> first_name >> last_name;
			name = first_name + " " + last_name;
			getline(ifile, line);
			stringstream ss3(line);
			ss3 >> birth_year;
			getline(ifile, line);
			stringstream ss4(line);
			ss4 >> zip_code;
			int x;
			getline(ifile, line);
			stringstream ss5(line);
			vector<int> temp;
			while (ss5 >> x) {
				temp.push_back(x);
			}
			User user_temp(id, name, birth_year, zip_code, temp);
			users.push_back(user_temp);
		}
		ifile.close();
		return 0;
	}
}

int Network::write_friends(const char* filename) {
	ofstream ofile (filename);
	if (ofile.fail()) {
		return -1;
	}
	else {
		ofile << total_users << endl;
		for (int i = 0; i < total_users; i++) {
			// print out the basic information related to
			// all the users in the friend list
			ofile << users[i].get_id() << endl;
			ofile << '\t' << users[i].get_user_name() << endl;
			ofile << '\t' << users[i].get_birth_year() << endl;
			ofile << '\t' << users[i].get_zip_code() << endl; 
			ofile << '\t';
			vector<int> tmp;
			tmp = users[i].get_ids();
			for (int j = 0; j < tmp.size(); j++) {
				ofile << tmp[j] << ' ';
			}
			ofile << endl; 
		}
		ofile.close();
		return 0;
	}
}

void Network::add_user(string username, int yr, int zipcode) {
	vector<int> friends;
	User u1(total_users, username, yr, zipcode, friends);
	users.push_back(u1);
	total_users++;

}
// vector<User> users;
// users.push_back(u1);
// users[users.size() - 1].push_back(...)


// vector<*User> users;
// users->push_back(u1);
// ...


void Network::printall() {
	// print the formatted friend list of all users
	cout << "ID" << "      " << "Name" << setw(20);
	cout << "Year" << setw(8) << "Zip"<< endl;
	for (int k = 0; k < 60; k++) {
		cout << "=";
	}
	cout << endl;
	for (int i = 0; i < total_users; i++) {
		stringstream convert;
		convert << i;
		string idx = convert.str();
//		cout << idx << endl;
//		string idx = i.str();
		string counter = idx + ".";
		string username = users[i].get_user_name();
		cout << counter << setw(4 + counter.size() + username.size());
		cout << users[i].get_user_name();
//		int len = username.size();
		cout << setw(28-username.size()-4) << users[i].get_birth_year();
		cout << setw(10) << users[i].get_zip_code() << endl;
	
	}
}

void Network::printfriends(string username) {
	// print the formatted friend list of the selected user
	for (int i = 0; i < total_users; i++) {
		if (username == users[i].get_user_name()) {
			int id = get_id(username);
			vector<int> friends = users[id].get_ids();
			cout << "ID" << "      " << "Name" << setw(20);
			cout << "Year" << setw(8) << "Zip"<< endl;
			for (int k = 0; k < 60; k++) {
				cout << "=";
			}
			cout << endl;
			for (int j = 0; j < friends.size(); j++) {
				int ids = friends[j];
				stringstream convert;
				convert << ids;
				string idx = convert.str();
				string counter = idx + ".";
				string user_name = users[ids].get_user_name();
				cout << counter << setw(4 + counter.size() + user_name.size());
				cout << users[ids].get_user_name();
				cout << setw(28 - user_name.size()-4) << users[ids].get_birth_year();
				cout << setw(10) << users[ids].get_zip_code() << endl;
			}
			return;
		}
	}
	cout << "Please input a valid username" << endl;
	return;

}

int Network::add_connection(string name1, string name2) {
	// if two input usernames are the same, simply output -1
	if (name1 == name2) {
		cout << "Please input two different usernames" << endl;
		return -1;
	}

	int a = -1;
	int b = -1;
	for (int i = 0; i < total_users; i++) {
		if (name1 == users[i].get_user_name()) {
			a = i;
		}

		if (name2 == users[i].get_user_name()){
			b = i;
		}
	}

	// if the input user does not exist, simply output -1
	if (a == -1 || b == -1) {
		return -1;
	}
	users[a].add_friend(b);
	users[b].add_friend(a);
	return 0;
}

int Network::remove_connection(string name1, string name2) {
	// if two input usernames are the same, simply output -1
	if (name1 == name2) {
		cout << "Please input two different usernames" << endl;
		return -1;
	}

	int a = -1;
	int b = -1;
	for (int i = 0; i < total_users; i++) {
		if (name1 == users[i].get_user_name()) {
			a = i;
		}

		if (name2 == users[i].get_user_name()){
			b = i;
		}
	}

	// if the input user does not exist, simply output -1
	if (a == -1 || b == -1) {
		return -1;
	}
	users[a].delete_friend(b);
	users[b].delete_friend(a);
	return 0;

}

int Network::get_id(string username) {
	for (int i = 0; i < total_users; i++) {
		if (username == users[i].get_user_name()) {
			return users[i].get_id();
		}
	}

	return -1;
}