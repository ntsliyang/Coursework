#include "../splayTree.h"
#include "../cacheLRU.h"
#include "gtest/gtest.h"
#include <random>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>

template<typename Key, typename Value>
class InheritedBST : public SplayTree<Key, Value>
{
public:
	Node<Key, Value>* getRoot() { return this->mRoot; }
};

template<typename Key, typename Value>
class InheritedLRU : public cacheLRU<Key, Value>
{
public:
	InheritedLRU(int i );
	Node<Key, Value>* getRoot() { return this->mRoot; }
	void process(std::ifstream& article, cacheLRU<Key, Value>* LUN, std::vector<Key>* all_words, int* num_get, int* found, int* not_found);
};

template<typename Key, typename Value>
InheritedLRU<Key, Value>::InheritedLRU(int i)
: cacheLRU<Key, Value>(i){}

template<typename Key, typename Value>
void InheritedLRU<Key, Value>::process(std::ifstream& article, cacheLRU<Key, Value>* LUN, std::vector<Key>* all_words, int* num_get, int* found, int* not_found) {
		Key word;
		std::pair<Key, Value> to_add;
		while(article >> word){
			to_add.first = word;
			all_words->push_back(word);
			//int r = rand() % (int)all_words.size();
			num_get++;
			try
			{
				Key gotten = LUN->get(word).first;
				//cout << "word "
				//     << "/" << gotten << "/"
				//     << " successfully found" << endl;
				found++;
			}
			catch (std::logic_error &e)
			{
				LUN->put(to_add);
				//cout << e.what() << ", which is " << word << endl;
				not_found++;
			}
		}
		article.close();
}

class SplayTest : public testing::Test
{};

TEST_F(SplayTest, Test1_Shakespeare) {
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(1000);
	std::vector<std::string> all_words;
	int found = 0;
	int not_found = 0;
	int num_get = 0;
	std::ifstream article("files/t8.shakespeare.txt"); // takes in the article
	// LUN->process(article, LUN, &all_words, &num_get, &found, &not_found);
	std::string word;
		std::pair<std::string, int> to_add;
		while (article >> word){
			to_add.first = word;
			all_words.push_back(word);
			//int r = rand() % (int)all_words.size();
			num_get++;
			try
			{
				std::string gotten = LUN->get(word).first;
				//cout << "word "
				//     << "/" << gotten << "/"
				//     << " successfully found" << endl;
				found++;
			}
			catch (std::logic_error &e)
			{
				LUN->put(to_add);
				//cout << e.what() << ", which is " << word << endl;
				not_found++;
			}
		}
		article.close();

	ASSERT_NE(0, num_get);
	EXPECT_EQ(901325, num_get);

	ASSERT_NE(0, all_words.size());
	EXPECT_EQ(901325, all_words.size());

	ASSERT_NE(nullptr, LUN);
	EXPECT_EQ(1000, LUN->getSize());

	ASSERT_NE(0, found);
	EXPECT_EQ(104102, found);

	ASSERT_NE(0, not_found);
	EXPECT_EQ(797223, not_found);

	delete LUN;
}

TEST_F(SplayTest, Test2_Swami1) {
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(1000);
	std::vector<std::string> all_words;
	int found = 0;
	int not_found = 0;
	int num_get = 0;
	std::ifstream article("files/swami.poem.txt"); // takes in the article
	// LUN->process(article, LUN, &all_words, &num_get, &found, &not_found);
	std::string word;
		std::pair<std::string, int> to_add;
		while (article >> word){
			to_add.first = word;
			all_words.push_back(word);
			//int r = rand() % (int)all_words.size();
			num_get++;
			try
			{
				std::string gotten = LUN->get(word).first;
				//cout << "word "
				//     << "/" << gotten << "/"
				//     << " successfully found" << endl;
				found++;
			}
			catch (std::logic_error &e)
			{
				LUN->put(to_add);
				//cout << e.what() << ", which is " << word << endl;
				not_found++;
			}
		}
		article.close();
		
	ASSERT_NE(0, num_get);
	EXPECT_EQ(144881, num_get);

	ASSERT_NE(0, all_words.size());
	EXPECT_EQ(144881, all_words.size());

	ASSERT_NE(nullptr, LUN);
	EXPECT_EQ(1000, LUN->getSize());

	ASSERT_NE(0, found);
	EXPECT_EQ(34627, found);

	ASSERT_NE(0, not_found);
	EXPECT_EQ(110254, not_found);

	delete LUN;
}

TEST_F(SplayTest, Test3_Swami2) {
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(1000);
	std::vector<std::string> all_words;
	int found = 0;
	int not_found = 0;
	int num_get = 0;
	std::ifstream article("files/swami.poem2.txt"); // takes in the article
	// LUN->process(article, LUN, &all_words, &num_get, &found, &not_found);
	std::string word;
		std::pair<std::string, int> to_add;
		while (article >> word){
			to_add.first = word;
			all_words.push_back(word);
			//int r = rand() % (int)all_words.size();
			num_get++;
			try
			{
				std::string gotten = LUN->get(word).first;
				//cout << "word "
				//     << "/" << gotten << "/"
				//     << " successfully found" << endl;
				found++;
			}
			catch (std::logic_error &e)
			{
				LUN->put(to_add);
				//cout << e.what() << ", which is " << word << endl;
				not_found++;
			}
		}
		article.close();
		
	ASSERT_NE(0, num_get);
	EXPECT_EQ(102453, num_get);

	ASSERT_NE(0, all_words.size());
	EXPECT_EQ(102453, all_words.size());

	ASSERT_NE(nullptr, LUN);
	EXPECT_EQ(1000, LUN->getSize());

	ASSERT_NE(0, found);
	EXPECT_EQ(27542, found);

	ASSERT_NE(0, not_found);
	EXPECT_EQ(74911, not_found);

	delete LUN;
}

TEST_F(SplayTest, Test4_Swami3) {
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(1000);
	std::vector<std::string> all_words;
	int found = 0;
	int not_found = 0;
	int num_get = 0;
	std::ifstream article("files/swami.poem3.txt"); // takes in the article
	// LUN->process(article, LUN, &all_words, &num_get, &found, &not_found);
	std::string word;
		std::pair<std::string, int> to_add;
		while (article >> word){
			to_add.first = word;
			all_words.push_back(word);
			//int r = rand() % (int)all_words.size();
			num_get++;
			try
			{
				std::string gotten = LUN->get(word).first;
				//cout << "word "
				//     << "/" << gotten << "/"
				//     << " successfully found" << endl;
				found++;
			}
			catch (std::logic_error &e)
			{
				LUN->put(to_add);
				//cout << e.what() << ", which is " << word << endl;
				not_found++;
			}
		}
		article.close();
		
	ASSERT_NE(0, num_get);
	EXPECT_EQ(185023, num_get);

	ASSERT_NE(0, all_words.size());
	EXPECT_EQ(185023, all_words.size());

	ASSERT_NE(nullptr, LUN);
	EXPECT_EQ(1000, LUN->getSize());

	ASSERT_NE(0, found);
	EXPECT_EQ(51455, found);

	ASSERT_NE(0, not_found);
	EXPECT_EQ(133568, not_found);

	delete LUN;
}

TEST_F(SplayTest, Test5_EdgarAllanPoe) {
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(1000);
	std::vector<std::string> all_words;
	int found = 0;
	int not_found = 0;
	int num_get = 0;
	std::ifstream article("files/elp.poem.txt"); // takes in the article
	// LUN->process(article, LUN, &all_words, &num_get, &found, &not_found);
	std::string word;
		std::pair<std::string, int> to_add;
		while (article >> word){
			to_add.first = word;
			all_words.push_back(word);
			//int r = rand() % (int)all_words.size();
			num_get++;
			try
			{
				std::string gotten = LUN->get(word).first;
				//cout << "word "
				//     << "/" << gotten << "/"
				//     << " successfully found" << endl;
				found++;
			}
			catch (std::logic_error &e)
			{
				LUN->put(to_add);
				//cout << e.what() << ", which is " << word << endl;
				not_found++;
			}
		}
		article.close();
		
	ASSERT_NE(0, num_get);
	EXPECT_EQ(64142, num_get);

	ASSERT_NE(0, all_words.size());
	EXPECT_EQ(64142, all_words.size());

	ASSERT_NE(nullptr, LUN);
	EXPECT_EQ(1000, LUN->getSize());

	ASSERT_NE(0, found);
	EXPECT_EQ(15362, found);

	ASSERT_NE(0, not_found);
	EXPECT_EQ(48780, not_found);

	delete LUN;
}