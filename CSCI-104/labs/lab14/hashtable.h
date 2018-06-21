#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>

/**
Hash Table for CS104 lab 13. Only stores strings.
*/
class HashTable {
public:
	HashTable(int);
	~HashTable();

	void insert(std::string);
	bool find(std::string);
	void remove(std::string);

private:
	std::vector<std::string>** data;
	int size;
};

#endif