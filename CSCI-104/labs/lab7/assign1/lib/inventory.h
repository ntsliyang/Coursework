#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <string>

struct Item
{
	Item(std::string n, int a) : name(n), amount(a){}
	std::string name;
	int amount;
};

class Inventory : private std::vector<Item> {
public:
	Inventory();

	/* Add an item to the inventory with the given name and amount. */
	void addItem(std::string, int);
	/* Remove all items with this name from the inventory 
	   while preserving the order of other items in the inventory.*/
	void removeItem(std::string);
	/* Return the number of items with this name from the inventory. */
	int getNumItems(std::string);

	/* Print all the items in this format:
		name amount
		name amount
		name amount
	*/
	void printAllItems();
};

#endif