#include <iostream>
#include <list>
#include <string>
#include <queue>
#include <set>

/* Restaurant Class */
class Restaurant
{
  public:
	Restaurant(std::list<Customers> customer, std::list<Employees>employee);
	~Restaurant();
	std::list<Employees> getEmployees(); // return a list of employees
	int grossMoney();					 // Compute the gross amount of money/pay employees earned
	int sizeCustomer();					 // indicate how many customers a waiter is serving.
	void setOwner(Owner o);
	Owner getOwner();
  private: 
	std::list<Customers> customer;
	std::list<Employees> employee;	
};

/* Owner Class; has-a to Restaurant Class */
class Owner
{
  public:
	Owner();  // constructor
	~Owner(); // destructor
};

/* Employee Class; has-a to Restaurant Class */
class Employees
{
  public:
	Employees(int size, double income);
	~Employees();
	virtual double getIncome() = 0;
	virtual void setIncome(double income) = 0;
	int getSizeEmployees();
	void setSizeEmployees(int size);

  private:
	int sizeEmployee; // size of employees
	double grossIncome;  // total amount of income
};

class Waiters : public Employees
{
  public:
	Waiters(std::list<int> table, int order, int size, int time);
	double getIncome();
	void setIncome(double income);
	void setOrderNumber(int order);
	int getOrderNumber();
	int getSizeCustomer();
	void setSizeCustomer(int size);
	int	getWaitingTime();
	void setWaitingTime(int time);
	void takeOrder();		
	void enterKitchen();	
	void giveOrdertoChef(); 

  private:
	std::list<int> tables; // a list of tables assigned to wait
	int orderNumber;	   // # of order
	int sizeCustomer;	  // size of customers
	int waitingTime;	   // time that the waiter returns to get the order
};

class Chefs : public Employees
{
  public:
	Chefs(std::string skill, std::queue<std::string> order);
	double getIncome();
	void setIncome(double income);
	void setSkills(std::string s);
	std::string getSkills();
	void setOrders(std::queue<std::string> o);
	std::queue<std::string> getOrders();
	void setWaitingTime(int t);
	int getWaitingTime(); // chefs indicate how long is waiting time

  private:
	std::string skills;				// different skills: faster / slower
	std::queue<std::string> orders; // queue of order assigned to cook
};

class Hosts : public Employees
{
  public:
	Hosts();
	double getIncome();
	void setIncome(double income);
};

/* Customer Class */
class Customers
{
  public:
	Customers(int size, int table);					  // constructor
	~Customers();					  // destructor
	virtual void setTip(int size) = 0; // how much to tip
	virtual double getTip() = 0;
	int getSize();					  // get the number of people in a party
	void setSize(int size_);
	int getOrderTime();
	virtual void setOrderTime(int OrderTime) = 0;
	int getEatTime();
	virtual void setEatTime(int EatTime) = 0;
	int getPayTime();
	virtual void setPayTime(int PayTime) = 0;
	int getExitTime();
	virtual void setExitTime(int ExitTime) = 0;
	// mutator and accessor methods for order/eat/pay/exit time

  protected:
	int sizeCustomer; // size of a party
	int table;		  // # of table matched to the party
	int OrderTime;	// time to take to order
	int EatTime;	  // time to eat
	int PayTime;	  // time to pay
	int ExitTime;	 // time to exit
};

class Walkins : public Customers
{
  public:
	Walkins();
	void setOrderTime(int OrderTime);
	void setEatTime(int EatTime);
	void setPayTime(int PayTime);
	void setExitTime(int ExitTime);
	void setTip(int size);
	double getTip();

  private:
	const double wtiprate1 = 0.15; // parties of 2-3 people
	const double wtiprate2 = 0.18; // parties of 4 or more people
};

class Reserved : public Customers
{
  public:
	Reserved();
	void setOrderTime(int OrderTime);
	void setEatTime(int EatTime);
	void setPayTime(int PayTime);
	void setExitTime(int ExitTime);
	void setTip(int size);
	double getTip();
};

class Celebrity : public Customers
{
  public:
	Celebrity();
	void setOrderTime(int OrderTime);
	void setEatTime(int EatTime);
	void setPayTime(int PayTime);
	void setExitTime(int ExitTime);
	void setTip(int size);
	double getTip();

  private:
	const double ctiprate = 0.25; // tip rate is 25%
	double tipfee;			// a constant amount
};