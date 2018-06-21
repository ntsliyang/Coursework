#include <iostream>
#include "llist.h"

struct Pokemon {
  int id;
  std::string name;

  Pokemon()
    : id(0), name("") { }

  Pokemon(int i, std::string n)
    : id(i), name(n) { }
};

int main() {
  LList<Pokemon> pokedex;
  pokedex.push_back(Pokemon(1, "Bulbasaur"));
  pokedex.push_back(Pokemon(4, "Charmander"));
  pokedex.push_back(Pokemon(7, "Squirtle"));

  for (int i = 0; i < pokedex.size(); i++) {
    std::cout << pokedex.get(i).name << std::endl;
  }

  LList<Pokemon>::iterator it;
  for (it = pokedex.begin(); it != pokedex.end(); ++it)
  {
  	std::cout << (*it).id << std::endl;
  }
  --it;
  for (; it != pokedex.begin(); --it)
  {
  	std::cout << it->name << std::endl;
  }
  std::cout << it->name << std::endl;

  return 0;
}
