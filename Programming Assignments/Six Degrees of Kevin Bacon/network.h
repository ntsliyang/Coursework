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
  // functions for network2
  std::vector<int> shortest_path(int from, int to);
  void print_shortest_path();
  std::vector<std::vector<int> > groups();
  void print_groups(std::vector<std::vector<int> > v);
  std::vector<int> suggest_friends(int who, int& score);
  void print_suggest_friends(std::vector<int> v);
  void BFS(int start);

 private:
 int total_users;
 std::vector<User> users;
 std::vector<User> shortest;
};


#endif