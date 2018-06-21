#include <string>
#include <vector>

class Order
{
public:
		Order();
		Order(const std::string& name);
		Order(const Order &o);
		~Order();
		void displayOrder() const;
		void clearOrder();
		Order& operator=(const Order &rhs);
		Order operator+(const Order &rhs) const;

private:
	struct Item
	{
		Item(const std::string& n, int c);
		std::string name;
		int count;
	};

private:
		std::vector<Item*> mItems;
};