rpg: rpg.cpp
	g++ -g -Wall -std=c++11 $^ -o $@

tests: rpg
	./rpg weapons.txt battle.txt > result.txt
	diff output.txt result.txt