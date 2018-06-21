#ifndef POKEDEX_H
#define POKEDEX_H

#include <string>
#include <vector>

enum PokemonType
{
  PokemonType_Grass,
  PokemonType_Fire,
  PokemonType_Water
};

struct Pokemon
{
  Pokemon(const std::string& n, const std::string& i);
  std::string name;
  std::string image;
};

class Pokedex 
{
public:
  Pokedex();
  ~Pokedex();

  /**
   * Add a pokemon to the correct map according to its type
   * Does nothing if a pokemon with the same name already exists
   */
  void insert (PokemonType type, const std::string& name, const std::string& image);

  /**
   * Returns the pokemon's image given its type and name
   */
  const std::string& getImage (PokemonType type, const std::string& name);
  
private:
  static const int PokemonTypeSize;
  std::vector<Pokemon>* mPokemons;
};

#endif
