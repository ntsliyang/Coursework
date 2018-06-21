#include "../cacheLRU.h"
#include <string>

void testPublicFunctions()
{
	cacheLRU<std::string, int> cache(5);
	cache.put(std::pair<const std::string, int>("a", 5));
	cache.put(cache.get("a"));
}

int main(int argc, char* argv[])
{
	testPublicFunctions();
	return 0;
}