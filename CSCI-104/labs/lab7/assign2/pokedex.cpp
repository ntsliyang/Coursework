#include "pokedex.h"
#include <iostream>
#include <stdexcept>

const int Pokedex::PokemonTypeSize = 3;

Pokemon::Pokemon(const std::string& n, const std::string& i)
: name(n)
, image(i)
{
}

Pokedex::Pokedex()
{
  mPokemons = new std::vector<Pokemon>[PokemonTypeSize];
}

Pokedex::~Pokedex()  
{
  delete [] mPokemons;
}

void Pokedex::insert(PokemonType type, const std::string& name, const std::string& image)
{
  for (int type = 0; type < PokemonTypeSize; ++type)
  {
    for (size_t j = 0; j < mPokemons[type].size(); ++j)
    {
      if (mPokemons[type][j].name == name)
      {
        return;
      }
    }
  }
  mPokemons[type].push_back(Pokemon(name, image));
}

const std::string& Pokedex::getImage(PokemonType type, const std::string& name)
{
  // TODO
}