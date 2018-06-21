#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

void populateMap(std::map<std::string, std::string> & disneyMap);
void printFriend(std::string name, std::map<std::string, std::string> disneyMap);

int main() 
{
	std::map<std::string, std::string> disneyMap;
	populateMap(disneyMap);
	printFriend("Buzz", disneyMap);
	printFriend("Lady", disneyMap);
	printFriend("Simba", disneyMap);
	printFriend("Gaston", disneyMap);
	printFriend("Belle", disneyMap);
}

void printFriend(std::string name, std::map<std::string, std::string> disneyMap) 
{
	try 
	{
	  std::cout << name << "'s friend is: " << disneyMap.at(name);
	  std::cout << "." << std::endl;
	} 
	catch (const std::out_of_range&) 
	{
	  std::cout << name << " has no friends :(" << std::endl;
	}
}

void populateMap(std::map<std::string, std::string> & disneyMap) 
{
	disneyMap.insert(std::make_pair("Buzz", "Woody"));
	disneyMap.insert(std::make_pair("Lady", "Tramp"));
	disneyMap.insert(std::make_pair("Simba", "Nala"));
	disneyMap.insert(std::make_pair("Belle", "Beast"));
}