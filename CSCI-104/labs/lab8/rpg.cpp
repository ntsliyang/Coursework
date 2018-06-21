#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <cstdlib>

int sampleValue(const std::vector<int>& values)
{
	return values[std::rand() % values.size()];
}

void loadWeaponData(std::ifstream& weaponFile, 
	std::map<std::string, std::vector<int> >& weapons)
{
	std::string word;
	int value = 0;
	while (weaponFile >> word && weaponFile >> value)
	{
		// TODO
		if (weapons.find(word) != weapons.end()) {
			weapons.find(word)->second.push_back(value);
		}
		else {
			std::vector<int> w(1,value);
			weapons.insert(std::pair<std::string, std::vector<int> >(word, w));
		}
	}
}

int getWeaponDamage(const std::string& word, 
	std::map<std::string, std::vector<int> >& weapons)
{
	// TODO
	if (weapons.find(word) != weapons.end()) {
		return sampleValue((weapons.find(word))->second);
	}
	else {
		return 0;
	}
}

void processBattle(std::ifstream& battleFile, 
	std::map<std::string, std::vector<int> >& weapons)
{
	std::string word;
	while (battleFile >> word)
	{
		std::cout << word << " " << getWeaponDamage(word, weapons) << std::endl;
	}
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cerr << "./search weapon.txt battle.txt" << std::endl;
		return 1;
	}

	std::ifstream weaponFile(argv[1]);
	std::ifstream battleFile(argv[2]);

	if (!weaponFile.is_open() || !battleFile.is_open())
	{
		std::cerr << "Files failed to open" << std::endl;
		return 1;
	}

	std::srand(578);

	std::map<std::string, std::vector<int>> weapons;
	loadWeaponData(weaponFile, weapons);
	processBattle(battleFile, weapons);

	weaponFile.close();
	battleFile.close();
	return 0;
}