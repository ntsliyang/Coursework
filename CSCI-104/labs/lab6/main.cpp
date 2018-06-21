#include <iostream>
#include "order.h"

void displayMenu()
{
	Order* o = new Order();
	bool showMenu = true;
	Order* previousOrder = NULL;
	while(showMenu)
	{
		char menuSelection;
		Order* temp;
		std::cout << "\nWhat would you like to eat? Enter \'q\' to quit." << std::endl;
		std::cout << "1) Burger" << std::endl;
		std::cout << "2) Fries" << std::endl;
		std::cout << "3) Drink" << std::endl;
		std::cout << "4) Vegetables" << std::endl;
		std::cout << "5) Copy Previous Order" << std::endl;
		std::cout << "6) Display Current Order" << std::endl;
		std::cout << "7) Checkout (clears current order)" << std::endl;
		std::cin >> menuSelection;

		switch(menuSelection)
		{
			// Cases 1, 2, 3 create a new Order of a unique item, add it to the current Order,
			// 		and then free the memory the new Order.
			// Case 4 adds two Orders, but does not assign it to the current Order, thereby 
			//	doing nothing. Vegetables should never be in someone's Order. (this can be a 
			//	quick check if students have created their operator+ correctly)
			// Case 5 uses the assignment operator to assign the previously checked out order
			//		to the current order.
			// Case 6 displays the current order.
			// Case 7 reassigns the previousOrder to the current order (using the copy 
			//		constructor, and clears all items from the current order.
			case '1':
				temp = new Order ("Burger");
				*o = *o + *temp;
				delete temp;
				break;
			case '2':
				temp = new Order ("Fries");
				*o = *o + *temp;
				delete temp;
				break;
			case '3':
				temp = new Order ("Drink");
				*o = *o + *temp;
				delete temp;
				break;
			case '4':
				temp = new Order ("Vegetables");
				*o + *temp;	// adds, but does not assign
				delete temp;
				break;
			case '5':
				if(previousOrder != NULL)
					*o = *previousOrder;
				break;
			case '6':
				o->displayOrder();
				break;
			case '7':	// checkout
				if(previousOrder != NULL)
					delete previousOrder;
				previousOrder = new Order(*o);
				o->clearOrder();
				break;
			case 'q':
				showMenu = false;
				break;
			default:
				std::cout << "Did not understand your input." << std::endl;
				break;
		}
	}

	// Delete previous order if it is not null
	if(previousOrder != NULL)
		delete previousOrder;

	// Delete current order
	delete o;
}

int main()
{
	displayMenu();

	return 0;
}