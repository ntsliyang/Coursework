#include <iostream>
#include "listint.h"

using namespace std;

// Initialize an empty list
ListInt::ListInt()
{
  cout << "***Creating ListInt object" << endl;
  head = NULL;
}

// Destructor (free all memory for each item)
ListInt::~ListInt()
{
  cout << "***Deleteing ListInt object" << endl;
  IntItem *tmp;
  // Add your code here to delete all IntItem structures in the list
  // only have destructor when you have a pointer that points to a dynamically-allocated stuff
  while (!is_empty())
  {
    pop_front();
  }
}

// Returns true if the list is empty
bool ListInt::is_empty()
{
  return (head == NULL);
}

// Returns the number of items in the list
int ListInt::size()
{
  int cnt = 0;
  IntItem *temp = head;
  while (head != NULL && temp != NULL)
  {
    // head != NULL in case of empty list
    // temp != NULL in case of 越界
    cnt++;
    temp = temp->next;
  }
  return cnt;
}

// Prints each integer item in the list (separated by a space)
void ListInt::print_list()
{
  IntItem *temp = head;
  while (temp)
  {
    cout << temp->val << ' ';
    temp = temp->next;
  }
  cout << endl;
}

// Add a new integer, new_val, to the back of the list
void ListInt::push_back(int new_val)
{
  IntItem *new_item = new IntItem;
  new_item->val = new_val;
  new_item->next = 0;
  if (head == NULL)
  {
    head = new_item;
  }
  else
  {
    IntItem *temp = head;
    while (temp->next)
    {
      temp = temp->next;
    }
    temp->next = new_item;
  }
}

// Add a new integer, new_val, to the front of the list
// pushing every other item back one
void ListInt::push_front(int new_val)
{
  IntItem *new_item = new IntItem;
  new_item->val = new_val;
  new_item->next = head;
  head = new_item;
}

// Remove the front item if there is opne
void ListInt::pop_front()
{
  if (!is_empty())
  { // only remove if list is not empty
    IntItem *temp = head->next;
    delete head;
    head = temp;
  }
}

// Return the item value at the front of the list
int ListInt::front()
{
  if (head != NULL)
    return head->val;
  else
    return -1;
}

void ListInt::deleteDuplicates()
{
  IntItem *temp = head;
  IntItem *tmp;
  while (temp != NULL && temp->next != NULL)
  {
    tmp = temp;
    while (tmp != NULL && tmp->next != NULL)
    {
      if (temp->val == tmp->next->val)
      {
        IntItem *tp = tmp->next;
        tmp->next = tmp->next->next;
        delete tp;
      }
      else
      {
        tmp = tmp->next;
      }
    }
    temp = temp->next;
  }
}

int ListInt::countNodes()
{
  IntItem *temp = head;
  int cnt = 0;
  while (head != NULL && temp != NULL)
  {
    temp = temp->next;
    cnt++;
  }
  return cnt;
}

// IntItem *ListInt::find(int find_val)
// {

// }

void ListInt::remove(int del_val)
{
  IntItem* temp = head;
  while (temp != NULL) {
    if (temp->val == del_val) {
      IntItem* tmp = temp;
      if (temp->next != NULL) {
        temp = temp->next;
        delete tmp;
      }
      else {
        temp->next = NULL;
        return;
      }
    }
    else if (temp->next != NULL) {
      if (temp->next->val == del_val) {
        IntItem* tp = temp->next;
        if (temp->next->next != NULL) {
          temp->next = temp->next->next;
          delete tp;
        }
        else {
          temp->next->next = NULL;
        }
      }
    }
    else {
      temp = temp->next;
    }
  }
}

// ListInt &ListInt::operator+(const ListInt &rhs)
// {

// }
