#ifndef LISTINT_H
#define LISTINT_H

struct IntItem {
  int val;
  IntItem *next;
};

class ListInt {
 public:
  // Initialize an empty list
  ListInt();

  // Destructor (free all memory for each item) 
 ~ListInt();

  // Returns true if the list is empty
  bool is_empty();

  // Returns the number of items in the list
  int size();

  // Prints each integer item in the list 
  // (separated by a space)
  void print_list();

  // Add a new integer, new_val, to the back of the list
  void push_back(int new_val);

  // Add a new integer, new_val, to the front of the list
  // pushing every other item back one
  void push_front(int new_val);

  // Remove the front item it there is one
  void pop_front();

  // Return the item value at the front of the list
  int front();

  // delete duplicates in the list and return the head
  void deleteDuplicates();

  // count nodes in the list 
  int countNodes();

  /*******************************************
   * Uncomment the following 2 prototypes
   *  if you want to implement them
   *******************************************/
  /// Finds the IntItem struct in the list that
  ///  has the value specified by find_val or NULL
  ///  if it doesn't exist in the list
  //IntItem *find(int find_val);

  void remove(int del_val);


  /*******************************************
   * This function is for more advanced courses
   *  that cover operator overloading
   *******************************************/
  //ListInt& operator+(const ListInt &rhs);

 private:

  IntItem *head;
};

#endif
