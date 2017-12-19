/*****************************************************
Name: Yang Li
Email: yli546@usc.edu
Description: Create constructors and desctrutors for 
the user class, and set out different functions for 
this class
*****************************************************/

#ifndef USER_H
#define USER_H
#include <string>
#include <vector>

class User {
 public:
 User(int id, std::string name, int year, int zip, std::vector<int> friends);
 ~User();
 void add_friend(int id);
 void delete_friend(int id);
 // accessor methods
 std::string get_user_name();
 int get_id(); 
 int get_birth_year();
 int get_zip_code();
 std::vector<int>& get_ids();
  // data members for network2
 int depth;
 int pred;
 int suggestion_score;
// int set_member;

 private:
 int _id;
 std::string _name;
 int _year;
 int _zip;
 std::vector<int> _friends;
};


#endif