/*****************************************************
Name: Yang Li
Email: yli546@usc.edu
Description: Create the constructors and destructors
for the Network class, and set out different functions
for this class
*****************************************************/

#ifndef NETWORK_H
#define NETWORK_H
#include "user.h"
#include <string>
#include <vector>
#include <sstream>

class Network {
 public:
  Network();
  ~Network();
  int read_friends(const char *filename);
  int write_friends(const char *filename);
  void add_user(std::string username, int yr, int zipcode);
  void printall(); 
  // helper function to print all the users
  void printfriends(std::string username); 
  // helper function to print the friends of a selected user 
  int add_connection(std::string name1, std::string name2);
  int remove_connection(std::string name1, std::string name2);
  int get_id(std::string username);

 private:
 int total_users;
 std::vector<User> users;
};


#endif