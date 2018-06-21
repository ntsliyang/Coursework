#include "splayTree.h"
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <string>
using namespace std;
typedef long long LL;

int seed;
const int maxRand = 998244353, multi = 12900001, add = 13800013;
inline void incSeed() {
	seed = ((LL)seed * multi + add) % maxRand;
}
int Rand() {
	incSeed();
	return seed;
}

double Rand01() {
	incSeed();
	return (double)seed / maxRand;
}

class InheritedSplay : public SplayTree<int, double> {
	public:
	Node<int, double>* getRoot() {
		return this->mRoot;
	}
	void printRoot() {
		BinarySearchTree<int, double>::printRoot(this->mRoot);
	}	
	void print(Node<int, double>* node);
};

map<int, double> S;

void InheritedSplay::print(Node<int, double>* node) {
    if(!node) 
        return;
	std::cout << node->getKey() << std::endl;
	if(node->getLeft())
        print(node->getLeft());
    if(node->getRight())
        print(node->getRight());
}
void splayTest(InheritedSplay* spt, int N, int Key) {
	spt->clear();
	for (int i = 0; i < N; i++) {
		int typ = Rand() % 3;
		int key = Rand() % Key;
		auto val = make_pair(key, Rand01());
		if (i <= N/10 && N > 1000)
			typ = 0;
		switch (typ) {
			case 0:
//				printf("Insert (%d, %f)\n", val.first, val.second);
				spt->insert(val);
				S.insert(val);
				break;
			case 1:
//				printf("Remove %d\n", val.first);
				spt->remove(val.first);
				if (S.count(val.first))
					S.erase(S.find(val.first));
				break;
			case 2: {
//				printf("Delete Min Leaf\n");
				spt->deleteMinLeaf();
				break;
			}
		}
	}
	spt->printRoot();
}

int main(int argc, char* argv[]) {
	freopen("output.txt", "w", stdout);
	// vector<pair<string, vector<int> > > data;
	// data.push_back({"Small Range Test #1", {0, 10, 10}});
	// data.push_back({"Small Range Test #2", {0, 10, 3}});
	// data.push_back({"Small Range Test #3", {0, 100, 10}});
	// data.push_back({"Small Range Test #4", {0, 100, 3}});
	// data.push_back({"Small Range Test #5", {0, 100, 100000000}});
	// data.push_back({"Small Range Test #6", {0, 100, 10}});
	// data.push_back({"Small Range Test #7", {0, 233, 100000000}});
	// data.push_back({"Small Range Test #8", {0, 2333, 100000000}});
	// vector<int, int> data;
	InheritedSplay* spt = new InheritedSplay;
	for (int i = 1; i <= 10; i++) {
		cout << "Running Small Range Test #" + to_string(i) << endl;
		int N1 = Rand() % 10;
		int N2 = Rand() % 12321;
		splayTest(spt, N1, N2);
		cout << endl;
		cout << endl;
	}

	for (int i = 1; i <= 10; i++) {
		cout << "Running Stress Test #" + to_string(i) << endl;
		int N1 = Rand() % 100000;
		int N2 = Rand() % 999823;
		splayTest(spt, N1, N2);
		cout << endl;
		cout << endl;
	}


	
	delete spt;
	return 0;
}

/*
1. remove when it's empty
2. remove unfound elements 
3. insert repetitive element
4. find repetitively the same element 
*/