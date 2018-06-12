#include <iostream>
#include "listint.h"

using namespace std;

int main(int argc, char *argv[])
{
  int temp;
  ListInt l1;

  cout << "Added 1, 2, 3, and 9 to list 1" << endl;
  l1.push_back(1);
  l1.push_back(2);
  l1.push_back(3);
  l1.push_back(9);
  l1.print_list();
  cout << "List 1 size is " << l1.size() << endl;  
  temp = l1.front();
  cout << "Front item is " << temp << endl;
  cout << "After removing 1 item, size is " << l1.size() << endl;  
  cout << "Clearing the list 1" << endl;
  while(! l1.is_empty() ){
    cout << "\tRemoving: " << l1.front() << endl; 
    l1.pop_front();
  }
  cout << "Attempting to remove from empty list...let's see how you handle it" << endl;
  l1.pop_front();
  cout << "Congratulations...your program did not crash!" << endl;
  cout << "Bye, Bye!" << endl;
  return 0;
}
