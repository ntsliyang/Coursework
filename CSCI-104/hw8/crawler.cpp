#include "splayTree.h"
#include "cacheLRU.h"
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
	InheritedLRU(int i, std::vector<std::string> v);
	Node<Key, Value>* getRoot() { return this->mRoot; }
	std::vector<std::string> process(std::ifstream& ifile, std::vector<std::string> v);
	void solve(std::ifstream& ifile, std::vector<std::string> v, int idx, int i1, int i2, int i3, int i4, int i5);
	std::vector<std::string> v;
};

template<typename Key, typename Value>
InheritedLRU<Key, Value>::InheritedLRU(int i, std::vector<std::string> v)
: cacheLRU<Key, Value>(i){
	std::ifstream article("index.txt");
	v = process(article, v);
}

template<typename Key, typename Value>
std::vector<std::string> InheritedLRU<Key, Value>::process(std::ifstream& ifile, std::vector<std::string> v) {
	std::string line;
	while (getline(ifile, line)) {
		ifile >> line;
		v.push_back(line);
	}
	return v;
}

template<typename Key, typename Value>
void InheritedLRU<Key, Value>::solve(std::ifstream& ifile, std::vector<std::string> v, int idx, int i1, int i2, int i3, int i4, int i5) {
	this->v = this->process(ifile, this->v);
	std::vector<std::string> all_words;
	int found = 0;
	int not_found = 0;
	int num_get = 0;
	std::ifstream article(v[idx]); // takes in the article
	// LUN->process(article, LUN, &all_words, &num_get, &found, &not_found);
	std::string word;
		std::pair<std::string, int> to_add;
		while (article >> word){
			to_add.first = word;
			all_words.push_back(word);
			num_get++;
			try
			{
				std::string gotten = this->get(word).first;
				found++;
			}
			catch (std::logic_error &e)
			{
				this->put(to_add);
				not_found++;
			}
		}
		article.close();

	ASSERT_NE(0, num_get);
	EXPECT_EQ(i1, num_get);

	ASSERT_NE(0, all_words.size());
	EXPECT_EQ(i2, all_words.size());

	ASSERT_NE(nullptr, this);
	EXPECT_EQ(i3, this->getSize());

	ASSERT_NE(0, found);
	EXPECT_EQ(i4, found);

	ASSERT_NE(0, not_found);
	EXPECT_EQ(i5, not_found);
}

class SplayTest : public testing::Test
{};

TEST_F(SplayTest, Test1_Random1) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 0, 815, 815, 802, 13, 802);
	delete LUN;
}

TEST_F(SplayTest, Test2_Random2) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 1, 642, 642, 1433, 11, 631);
	delete LUN;
}

TEST_F(SplayTest, Test3_Random3) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 2, 701, 701, 2130, 4, 697);
	delete LUN;
}

TEST_F(SplayTest, Test4_Random4) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 3, 817, 817, 2944, 3, 814);
	delete LUN;
}

TEST_F(SplayTest, Test5_Random5) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 4, 1150, 1150, 4074, 20, 1130);
	delete LUN;
}

TEST_F(SplayTest, Test6_Random6) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 5, 989, 989, 5044, 19, 970);
	delete LUN;
}

TEST_F(SplayTest, Test7_Random7) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 6, 782, 782, 5817, 9, 773);
	delete LUN;
}

TEST_F(SplayTest, Test8_Random8) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 7, 1093, 1093, 6892, 18, 1075);
	delete LUN;
}

TEST_F(SplayTest, Test9_Random9) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 8, 776, 776, 7659, 9, 767);
	delete LUN;
}

TEST_F(SplayTest, Test10_Random10) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 9, 805, 805, 8448, 16, 789);
	delete LUN;
}

TEST_F(SplayTest, Test11_Random11) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 10, 1104, 1104, 9535, 17, 1087);
	delete LUN;
}

TEST_F(SplayTest, Test12_Random12) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 11, 1011, 1011, 10000, 10, 1001);
	delete LUN;
}

TEST_F(SplayTest, Test13_Random13) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 12, 856, 856, 10000, 0, 856);
	delete LUN;
}

TEST_F(SplayTest, Test14_Random14) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 13, 643, 643, 10000, 0, 643);
	delete LUN;
}

TEST_F(SplayTest, Test15_Random15) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 14, 858, 858, 10000, 0, 858);
	delete LUN;
}

TEST_F(SplayTest, Test16_Random16) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 15, 901, 901, 10000, 0, 901);
	delete LUN;
}

TEST_F(SplayTest, Test17_Random17) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 16, 739, 739, 10000, 0, 739);
	delete LUN;
}

TEST_F(SplayTest, Test18_Random18) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 17, 983, 983, 10000, 0, 983);
	delete LUN;
}

TEST_F(SplayTest, Test19_Random19) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 18, 881, 881, 10000, 0, 881);
	delete LUN;
}

TEST_F(SplayTest, Test20_Random20) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 19, 978, 978, 10000, 0, 978);
	delete LUN;
}

TEST_F(SplayTest, Test21_Random21) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 20, 649, 649, 10000, 0, 649);
	delete LUN;
}

TEST_F(SplayTest, Test22_Random22) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 21, 1115, 1115, 10000, 0, 1115);
	delete LUN;
}

TEST_F(SplayTest, Test23_Random23) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 22, 734, 734, 10000, 0, 734);
	delete LUN;
}

TEST_F(SplayTest, Test24_Random24) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 23, 1143, 1143, 10000, 0, 1143);
	delete LUN;
}

TEST_F(SplayTest, Test25_Random25) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 24, 795, 795, 10000, 0, 795);
	delete LUN;
}

TEST_F(SplayTest, Test26_Random26) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 25, 1251, 1251, 10000, 0, 1251);
	delete LUN;
}

TEST_F(SplayTest, Test27_Random27) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 26, 692, 692, 10000, 0, 692);
	delete LUN;
}

TEST_F(SplayTest, Test28_Random28) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 27, 802, 802, 10000, 0, 802);
	delete LUN;
}

TEST_F(SplayTest, Test29_Random29) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 28, 921, 921, 10000, 0, 921);
	delete LUN;
}

TEST_F(SplayTest, Test30_Random30) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 29, 637, 637, 10000, 0, 637);
	delete LUN;
}

TEST_F(SplayTest, Test31_Random31) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 30, 863, 863, 10000, 0, 863);
	delete LUN;
}

TEST_F(SplayTest, Test32_Random32) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 31, 1161, 1161, 10000, 0, 1161);
	delete LUN;
}

TEST_F(SplayTest, Test33_Random33) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 32, 944, 944, 10000, 0, 944);
	delete LUN;
}

TEST_F(SplayTest, Test34_Random34) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 33, 1261, 1261, 10000, 0, 1261);
	delete LUN;
}

TEST_F(SplayTest, Test35_Random35) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 34, 1005, 1005, 10000, 0, 1005);
	delete LUN;
}

TEST_F(SplayTest, Test36_Random36) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 35, 842, 842, 10000, 0, 842);
	delete LUN;
}

TEST_F(SplayTest, Test37_Random37) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 36, 1260, 1260, 10000, 0, 1260);
	delete LUN;
}

TEST_F(SplayTest, Test38_Random38) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 37, 1166, 1166, 10000, 0, 1166);
	delete LUN;
}

TEST_F(SplayTest, Test39_Random39) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 38, 952, 952, 10000, 0, 952);
	delete LUN;
}

TEST_F(SplayTest, Test40_Random40) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 39, 1142, 1142, 10000, 0, 1142);
	delete LUN;
}

TEST_F(SplayTest, Test41_Random41) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 40, 692, 692, 10000, 0, 692);
	delete LUN;
}

TEST_F(SplayTest, Test42_Random42) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 41, 1075, 1075, 10000, 0, 1075);
	delete LUN;
}

TEST_F(SplayTest, Test43_Random43) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 42, 788, 788, 10000, 0, 788);
	delete LUN;
}

TEST_F(SplayTest, Test44_Random44) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 43, 645, 645, 10000, 0, 645);
	delete LUN;
}

TEST_F(SplayTest, Test45_Random45) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 44, 1169, 1169, 10000, 0, 1169);
	delete LUN;
}

TEST_F(SplayTest, Test46_Random46) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 45, 1115, 1115, 10000, 0, 1115);
	delete LUN;
}

TEST_F(SplayTest, Test47_Random47) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 46, 959, 959, 10000, 0, 959);
	delete LUN;
}

TEST_F(SplayTest, Test48_Random48) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 47, 1086, 1086, 10000, 0, 1086);
	delete LUN;
}

TEST_F(SplayTest, Test49_Random49) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 48, 946, 946, 10000, 0, 946);
	delete LUN;
}

TEST_F(SplayTest, Test50_Random50) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 49, 697, 697, 10000, 0, 697);
	delete LUN;
}

TEST_F(SplayTest, Test51_Random51) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 50, 1039, 1039, 10000, 0, 1039);
	delete LUN;
}

TEST_F(SplayTest, Test52_Random52) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 51, 794, 794, 10000, 0, 794);
	delete LUN;
}

TEST_F(SplayTest, Test53_Random53) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 52, 1129, 1129, 10000, 0, 1129);
	delete LUN;
}

TEST_F(SplayTest, Test54_Random54) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 53, 646, 646, 10000, 0, 646);
	delete LUN;
}

TEST_F(SplayTest, Test55_Random55) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 54, 729, 729, 10000, 0, 729);
	delete LUN;
}

TEST_F(SplayTest, Test56_Random56) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 55, 724, 724, 10000, 0, 724);
	delete LUN;
}

TEST_F(SplayTest, Test57_Random57) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 56, 659, 659, 10000, 0, 659);
	delete LUN;
}

TEST_F(SplayTest, Test58_Random58) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 57, 727, 727, 10000, 0, 727);
	delete LUN;
}

TEST_F(SplayTest, Test59_Random59) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 58, 717, 717, 10000, 0, 717);
	delete LUN;
}

TEST_F(SplayTest, Test60_Random60) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 59, 893, 893, 10000, 0, 893);
	delete LUN;
}

TEST_F(SplayTest, Test61_Random61) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 60, 1009, 1009, 10000, 0, 1009);
	delete LUN;
}

TEST_F(SplayTest, Test62_Random62) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 61, 961, 961, 10000, 0, 961);
	delete LUN;
}

TEST_F(SplayTest, Test63_Random63) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 62, 770, 770, 10000, 0, 770);
	delete LUN;
}

TEST_F(SplayTest, Test64_Random64) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 63, 648, 648, 10000, 0, 648);
	delete LUN;
}

TEST_F(SplayTest, Test65_Random65) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 64, 940, 940, 10000, 0, 940);
	delete LUN;
}

TEST_F(SplayTest, Test66_Random66) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 65, 1059, 1059, 10000, 0, 1059);
	delete LUN;
}

TEST_F(SplayTest, Test67_Random67) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 66, 903, 903, 10000, 0, 903);
	delete LUN;
}

TEST_F(SplayTest, Test68_Random68) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 67, 1092, 1092, 10000, 0, 1092);
	delete LUN;
}

TEST_F(SplayTest, Test69_Random69) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 68, 1000, 1000, 10000, 0, 1000);
	delete LUN;
}

TEST_F(SplayTest, Test70_Random70) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 69, 1022, 1022, 10000, 0, 1022);
	delete LUN;
}

TEST_F(SplayTest, Test71_Random71) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 70, 1026, 1026, 10000, 0, 1026);
	delete LUN;
}

TEST_F(SplayTest, Test72_Random72) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 71, 1165, 1165, 10000, 0, 1165);
	delete LUN;
}

TEST_F(SplayTest, Test73_Random73) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 72, 1076, 1076, 10000, 0, 1076);
	delete LUN;
}

TEST_F(SplayTest, Test74_Random74) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 73, 1078, 1078, 10000, 0, 1078);
	delete LUN;
}

TEST_F(SplayTest, Test75_Random75) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 74, 986, 986, 10000, 0, 986);
	delete LUN;
}

TEST_F(SplayTest, Test76_Random76) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 75, 776, 776, 10000, 0, 776);
	delete LUN;
}

TEST_F(SplayTest, Test77_Random77) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 76, 770, 770, 10000, 0, 770);
	delete LUN;
}

TEST_F(SplayTest, Test78_Random78) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 77, 800, 800, 10000, 0, 800);
	delete LUN;
}

TEST_F(SplayTest, Test79_Random79) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 78, 919, 919, 10000, 0, 919);
	delete LUN;
}

TEST_F(SplayTest, Test80_Random80) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 79, 660, 660, 10000, 0, 660);
	delete LUN;
}

TEST_F(SplayTest, Test81_Random81) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 80, 691, 691, 10000, 0, 691);
	delete LUN;
}

TEST_F(SplayTest, Test82_Random82) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 81, 850, 850, 10000, 0, 850);
	delete LUN;
}

TEST_F(SplayTest, Test83_Random83) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 82, 656, 656, 10000, 0, 656);
	delete LUN;
}

TEST_F(SplayTest, Test84_Random84) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 83, 1224, 1224, 10000, 0, 1224);
	delete LUN;
}

TEST_F(SplayTest, Test85_Random85) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 84, 919, 919, 10000, 0, 919);
	delete LUN;
}

TEST_F(SplayTest, Test86_Random86) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 85, 1272, 1272, 10000, 0, 1272);
	delete LUN;
}

TEST_F(SplayTest, Test87_Random87) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 86, 675, 675, 10000, 0, 675);
	delete LUN;
}

TEST_F(SplayTest, Test88_Random88) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 87, 1064, 1064, 10000, 0, 1064);
	delete LUN;
}

TEST_F(SplayTest, Test89_Random89) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 88, 705, 705, 10000, 0, 705);
	delete LUN;
}

TEST_F(SplayTest, Test90_Random90) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 89, 985, 985, 10000, 0, 985);
	delete LUN;
}

TEST_F(SplayTest, Test91_Random91) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 90, 736, 736, 10000, 0, 736);
	delete LUN;
}

TEST_F(SplayTest, Test92_Random92) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 91, 1204, 1204, 10000, 0, 1204);
	delete LUN;
}

TEST_F(SplayTest, Test93_Random93) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 92, 852, 852, 10000, 0, 852);
	delete LUN;
}

TEST_F(SplayTest, Test94_Random94) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 93, 1194, 1194, 10000, 0, 1194);
	delete LUN;
}

TEST_F(SplayTest, Test95_Random95) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 94, 838, 838, 10000, 0, 838);
	delete LUN;
}

TEST_F(SplayTest, Test96_Random96) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 95, 945, 945, 10000, 0, 945);
	delete LUN;
}

TEST_F(SplayTest, Test97_Random97) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 96, 822, 822, 10000, 0, 822);
	delete LUN;
}

TEST_F(SplayTest, Test98_Random98) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 97, 730, 730, 10000, 0, 730);
	delete LUN;
}

TEST_F(SplayTest, Test99_Random99) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 98, 1278, 1278, 10000, 0, 1278);
	delete LUN;
}

TEST_F(SplayTest, Test100_Random100) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 99, 1036, 1036, 10000, 0, 1036);
	delete LUN;
}

TEST_F(SplayTest, Test101_Random101) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 100, 685, 685, 10000, 0, 685);
	delete LUN;
}

TEST_F(SplayTest, Test102_Random102) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 101, 1075, 1075, 10000, 0, 1075);
	delete LUN;
}

TEST_F(SplayTest, Test103_Random103) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 102, 982, 982, 10000, 0, 982);
	delete LUN;
}

TEST_F(SplayTest, Test104_Random104) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 103, 1077, 1077, 10000, 0, 1077);
	delete LUN;
}

TEST_F(SplayTest, Test105_Random105) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 104, 740, 740, 10000, 0, 740);
	delete LUN;
}

TEST_F(SplayTest, Test106_Random106) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 105, 981, 981, 10000, 0, 981);
	delete LUN;
}

TEST_F(SplayTest, Test107_Random107) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 106, 841, 841, 10000, 0, 841);
	delete LUN;
}

TEST_F(SplayTest, Test108_Random108) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 107, 1126, 1126, 10000, 0, 1126);
	delete LUN;
}

TEST_F(SplayTest, Test109_Random109) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 108, 1086, 1086, 10000, 0, 1086);
	delete LUN;
}

TEST_F(SplayTest, Test110_Random110) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 109, 1180, 1180, 10000, 0, 1180);
	delete LUN;
}

TEST_F(SplayTest, Test111_Random111) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 110, 854, 854, 10000, 0, 854);
	delete LUN;
}

TEST_F(SplayTest, Test112_Random112) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 111, 1248, 1248, 10000, 0, 1248);
	delete LUN;
}

TEST_F(SplayTest, Test113_Random113) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 112, 1098, 1098, 10000, 0, 1098);
	delete LUN;
}

TEST_F(SplayTest, Test114_Random114) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 113, 714, 714, 10000, 0, 714);
	delete LUN;
}

TEST_F(SplayTest, Test115_Random115) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 114, 707, 707, 10000, 0, 707);
	delete LUN;
}

TEST_F(SplayTest, Test116_Random116) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 115, 813, 813, 10000, 0, 813);
	delete LUN;
}

TEST_F(SplayTest, Test117_Random117) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 116, 797, 797, 10000, 0, 797);
	delete LUN;
}

TEST_F(SplayTest, Test118_Random118) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 117, 1115, 1115, 10000, 0, 1115);
	delete LUN;
}

TEST_F(SplayTest, Test119_Random119) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 118, 760, 760, 10000, 0, 760);
	delete LUN;
}

TEST_F(SplayTest, Test120_Random120) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 119, 869, 869, 10000, 0, 869);
	delete LUN;
}

TEST_F(SplayTest, Test121_Random121) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 120, 824, 824, 10000, 0, 824);
	delete LUN;
}

TEST_F(SplayTest, Test122_Random122) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 121, 1071, 1071, 10000, 0, 1071);
	delete LUN;
}

TEST_F(SplayTest, Test123_Random123) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 122, 1230, 1230, 10000, 0, 1230);
	delete LUN;
}

TEST_F(SplayTest, Test124_Random124) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 123, 1163, 1163, 10000, 0, 1163);
	delete LUN;
}

TEST_F(SplayTest, Test125_Random125) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 124, 629, 629, 10000, 0, 629);
	delete LUN;
}

TEST_F(SplayTest, Test126_Random126) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 125, 1115, 1115, 10000, 0, 1115);
	delete LUN;
}

TEST_F(SplayTest, Test127_Random127) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 126, 910, 910, 10000, 0, 910);
	delete LUN;
}

TEST_F(SplayTest, Test128_Random128) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 127, 904, 904, 10000, 0, 904);
	delete LUN;
}

TEST_F(SplayTest, Test129_Random129) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 128, 942, 942, 10000, 0, 942);
	delete LUN;
}

TEST_F(SplayTest, Test130_Random130) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 129, 1004, 1004, 10000, 0, 1004);
	delete LUN;
}

TEST_F(SplayTest, Test131_Random131) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 130, 938, 938, 10000, 0, 938);
	delete LUN;
}

TEST_F(SplayTest, Test132_Random132) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 131, 970, 970, 10000, 0, 970);
	delete LUN;
}

TEST_F(SplayTest, Test133_Random133) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 132, 890, 890, 10000, 0, 890);
	delete LUN;
}

TEST_F(SplayTest, Test134_Random134) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 133, 1180, 1180, 10000, 0, 1180);
	delete LUN;
}

TEST_F(SplayTest, Test135_Random135) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 134, 1203, 1203, 10000, 0, 1203);
	delete LUN;
}

TEST_F(SplayTest, Test136_Random136) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 135, 763, 763, 10000, 0, 763);
	delete LUN;
}

TEST_F(SplayTest, Test137_Random137) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 136, 872, 872, 10000, 0, 872);
	delete LUN;
}

TEST_F(SplayTest, Test138_Random138) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 137, 762, 762, 10000, 0, 762);
	delete LUN;
}

TEST_F(SplayTest, Test139_Random139) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 138, 1088, 1088, 10000, 0, 1088);
	delete LUN;
}

TEST_F(SplayTest, Test140_Random140) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 139, 1148, 1148, 10000, 0, 1148);
	delete LUN;
}

TEST_F(SplayTest, Test141_Random141) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 140, 638, 638, 10000, 0, 638);
	delete LUN;
}

TEST_F(SplayTest, Test142_Random142) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 141, 1137, 1137, 10000, 0, 1137);
	delete LUN;
}

TEST_F(SplayTest, Test143_Random143) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 142, 753, 753, 10000, 0, 753);
	delete LUN;
}

TEST_F(SplayTest, Test144_Random144) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 143, 1260, 1260, 10000, 0, 1260);
	delete LUN;
}

TEST_F(SplayTest, Test145_Random145) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 144, 1011, 1011, 10000, 0, 1011);
	delete LUN;
}

TEST_F(SplayTest, Test146_Random146) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 145, 1016, 1016, 10000, 0, 1016);
	delete LUN;
}

TEST_F(SplayTest, Test147_Random147) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 146, 1063, 1063, 10000, 0, 1063);
	delete LUN;
}

TEST_F(SplayTest, Test148_Random148) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 147, 736, 736, 10000, 0, 736);
	delete LUN;
}

TEST_F(SplayTest, Test149_Random149) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 148, 1165, 1165, 10000, 0, 1165);
	delete LUN;
}

TEST_F(SplayTest, Test150_Random150) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 149, 931, 931, 10000, 0, 931);
	delete LUN;
}

TEST_F(SplayTest, Test151_Random151) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 150, 1227, 1227, 10000, 0, 1227);
	delete LUN;
}

TEST_F(SplayTest, Test152_Random152) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 151, 906, 906, 10000, 0, 906);
	delete LUN;
}

TEST_F(SplayTest, Test153_Random153) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 152, 968, 968, 10000, 0, 968);
	delete LUN;
}

TEST_F(SplayTest, Test154_Random154) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 153, 699, 699, 10000, 0, 699);
	delete LUN;
}

TEST_F(SplayTest, Test155_Random155) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 154, 1259, 1259, 10000, 0, 1259);
	delete LUN;
}

TEST_F(SplayTest, Test156_Random156) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 155, 948, 948, 10000, 0, 948);
	delete LUN;
}

TEST_F(SplayTest, Test157_Random157) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 156, 963, 963, 10000, 0, 963);
	delete LUN;
}

TEST_F(SplayTest, Test158_Random158) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 157, 1117, 1117, 10000, 0, 1117);
	delete LUN;
}

TEST_F(SplayTest, Test159_Random159) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 158, 1233, 1233, 10000, 0, 1233);
	delete LUN;
}

TEST_F(SplayTest, Test160_Random160) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 159, 939, 939, 10000, 0, 939);
	delete LUN;
}

TEST_F(SplayTest, Test161_Random161) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 160, 904, 904, 10000, 0, 904);
	delete LUN;
}

TEST_F(SplayTest, Test162_Random162) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 161, 831, 831, 10000, 0, 831);
	delete LUN;
}

TEST_F(SplayTest, Test163_Random163) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 162, 708, 708, 10000, 0, 708);
	delete LUN;
}

TEST_F(SplayTest, Test164_Random164) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 163, 807, 807, 10000, 0, 807);
	delete LUN;
}

TEST_F(SplayTest, Test165_Random165) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 164, 842, 842, 10000, 0, 842);
	delete LUN;
}

TEST_F(SplayTest, Test166_Random166) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 165, 855, 855, 10000, 0, 855);
	delete LUN;
}

TEST_F(SplayTest, Test167_Random167) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 166, 1134, 1134, 10000, 0, 1134);
	delete LUN;
}

TEST_F(SplayTest, Test168_Random168) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 167, 875, 875, 10000, 0, 875);
	delete LUN;
}

TEST_F(SplayTest, Test169_Random169) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 168, 1137, 1137, 10000, 0, 1137);
	delete LUN;
}

TEST_F(SplayTest, Test170_Random170) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 169, 936, 936, 10000, 0, 936);
	delete LUN;
}

TEST_F(SplayTest, Test171_Random171) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 170, 853, 853, 10000, 0, 853);
	delete LUN;
}

TEST_F(SplayTest, Test172_Random172) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 171, 1025, 1025, 10000, 0, 1025);
	delete LUN;
}

TEST_F(SplayTest, Test173_Random173) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 172, 1131, 1131, 10000, 0, 1131);
	delete LUN;
}

TEST_F(SplayTest, Test174_Random174) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 173, 1169, 1169, 10000, 0, 1169);
	delete LUN;
}

TEST_F(SplayTest, Test175_Random175) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 174, 1240, 1240, 10000, 0, 1240);
	delete LUN;
}

TEST_F(SplayTest, Test176_Random176) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 175, 1222, 1222, 10000, 0, 1222);
	delete LUN;
}

TEST_F(SplayTest, Test177_Random177) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 176, 691, 691, 10000, 0, 691);
	delete LUN;
}

TEST_F(SplayTest, Test178_Random178) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 177, 752, 752, 10000, 0, 752);
	delete LUN;
}

TEST_F(SplayTest, Test179_Random179) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 178, 1174, 1174, 10000, 0, 1174);
	delete LUN;
}

TEST_F(SplayTest, Test180_Random180) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 179, 1268, 1268, 10000, 0, 1268);
	delete LUN;
}

TEST_F(SplayTest, Test181_Random181) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 180, 916, 916, 10000, 0, 916);
	delete LUN;
}

TEST_F(SplayTest, Test182_Random182) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 181, 896, 896, 10000, 0, 896);
	delete LUN;
}

TEST_F(SplayTest, Test183_Random183) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 182, 720, 720, 10000, 0, 720);
	delete LUN;
}

TEST_F(SplayTest, Test184_Random184) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 183, 1164, 1164, 10000, 0, 1164);
	delete LUN;
}

TEST_F(SplayTest, Test185_Random185) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 184, 1024, 1024, 10000, 0, 1024);
	delete LUN;
}

TEST_F(SplayTest, Test186_Random186) {
	std::vector<std::string> v;
	std::ifstream ifile("index.txt");
	InheritedLRU<std::string, int> *LUN = new InheritedLRU<std::string, int>(10000, v);
	LUN->solve(ifile, v, 185, 0, 1024, 10000, 0, 1024);
	delete LUN;
}

