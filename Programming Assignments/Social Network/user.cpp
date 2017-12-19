/*****************************************************
Name: Yang Li
Email: yli546@usc.edu
Description: Based on "user.h", define different functions
for the user class
*****************************************************/

#include "user.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


// initialize all the basic information related to an individual user
User::User(int id, string name, int year, int zip, vector<int> friends) {
	_id = id;
	_name = name;
	_year = year;
	_zip = zip;
	_friends = friends;
}

User::~User() {

}

void User::add_friend(int id) {
	for (int i = 0; i < _friends.size(); i++) {
		if (_id == _friends[i]) {
			return; 
		}
	}
	_friends.push_back(id);
}

void User::delete_friend(int id) {
	for (int i = 0; i < _friends.size(); i++) {
		if (id == _friends[i]) {
			_friends.erase(_friends.begin() + i);
			return;
		}
	}
}

// accessor methods 
string User::get_user_name() {
	return _name;
}

int User::get_id() {
	return _id;
}

int User::get_birth_year() {
	return _year;
}

int User::get_zip_code() {
	return _zip;
}

vector<int> User::get_ids() {
	return _friends;
}