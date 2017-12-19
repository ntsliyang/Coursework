#include <iostream>
#include "listint.h"

using namespace std;

int main(int argc, char *argv[])
{
	int temp;
	ListInt l1;

	l1.push_back(1);
	l1.push_back(1);
	l1.remove(1);
	l1.print_list();

	return 0;
}
