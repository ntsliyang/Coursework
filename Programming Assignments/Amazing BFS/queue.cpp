/* 
queue.cpp

Author: Yang Li

Short description of this file:

define data member functions within the constructor Queue
*/

#include "queue.h"

// constructor. maxlen must be as large as the total number
// of Locations that will ever be entered into this Queue.
// this is complete, you don't need to change it.
Queue::Queue(int maxlen) {
   contents = new Location[maxlen];
   head = 0;
   tail = 0;
}

// destructor. releases resources. C++ will call it automatically.
// this is complete, you don't need to change it.
Queue::~Queue() {
   delete[] contents;
}

// insert a new Location at the end/back of our list   
void Queue::add_to_back(Location loc) {
   tail++;
   contents[tail] = loc;
   // FILL THIS IN
}

// return and "remove" the oldest Location not already extracted
Location Queue::remove_from_front() {
	head++;
	return contents[head];
   // FILL THIS IN
}

// is this Queue empty? (did we extract everything added?)
// this is complete, you don't need to change it.
bool Queue::is_empty() {
   return head == tail;
}
