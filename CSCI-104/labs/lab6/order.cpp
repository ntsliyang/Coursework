#include "order.h"
#include <iostream>

Order::Item::Item(const std::string& n, int c)
: name(n)
, count(c)
{
}

// Constructor
Order::Order()
{
}

// Constructor which allocates one item
Order::Order(const std::string& name)
{
	mItems.push_back(new Item(name, 1));
}

// Copy Constructor - Part 3
Order::Order(const Order &rhs)
{
	// TODO
}

Order::~Order()
{
	clearOrder();
}

// Prints all items and their amounts.
void Order::displayOrder() const
{
	std::cout << "The current order is: " << std::endl;

	// Check if empty
	if(mItems.empty())
	{
		std::cout << "Empty" << std::endl;
		return;
	}

	// Display each item and its amount
	for (size_t i = 0; i < mItems.size(); ++i)
	{
		std::cout << mItems[i]->name << " " << mItems[i]->count << std::endl;
	}
}

// Deletes all items in variable ITEMS. - Part 2
void Order::clearOrder()
{
	// TODO
}

// Assigns Order RHS values to the current Order's values - Part 4
Order& Order::operator=(const Order &rhs)
{
	// Starter code: self-assignment can cause unseen problems. It won't
		// happen in this program, but let's get you in the habit early.
	if(this == &rhs)
		return *this;

	// TODO
	return *this;
}

/* 
Part 4
This operator should create a new Order that represents the
combined outcome of the current Order and the Order passed in via
parameter.
Note: It should not directly modify the current Order, but return
a copy of the combined Order instead. 
*/
Order Order::operator+(const Order &rhs) const
{
	// Starter code: operator+ should not modify THIS, so we make a copy
	Order result(*this);

	// TODO

	return result;
}