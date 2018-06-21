/*
	响真是太棒了
	響は最高です
	Hibiki No.1

	Update #2:
	Move stress test to the end of all test cases.

	Update #1:
	Rotation operation removed since it is not garanteed height
	is maintained properly after rotation.
*/
#include "rotateBST.h"
#include <algorithm>
#include <map>
#include <ctime>
#include <cstdio>
#include <string>
#include <set>
#include <vector>
typedef long long LL;
using namespace std;
/* Begin of Parameters */
const bool showCaseTitle = true;
const bool showPassedCase = true;
const bool terminateAtFirstFailure = true;
/* End of Parameters */

FILE *flog = fopen("judge.log", "w");
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

class BST: public rotateBST<int, double> {
	typedef Node<int, double> myN;
	private:
		int checkHeight(myN *p, bool &suc) {
			if (p == NULL)
				return 0;
			int mx = max(checkHeight(p->getLeft(), suc), checkHeight(p->getRight(), suc)) + 1;
			if (mx != p->getHeight())
				suc = false;
			return mx;
		}
		bool checkSame(Node<int, double> *r1, Node<int, double> *r2) const {
		if (r1 == NULL || r2 == NULL) {
			// One of them is empty
			if ((r1 == NULL) != (r2 == NULL))
				return false;
			return true;
		}
		if (r1->getKey() != r2->getKey())
			return false;
		if (!checkSame(r1->getLeft(), r2->getLeft()))
			return false;
		if (!checkSame(r1->getRight(), r2->getRight()))
			return false;
		return true;
	}
	public:
		bool checkHeight() {
			bool suc = true;
			checkHeight(this->mRoot, suc);
			return suc;
		}
		void testRotate(int key) {
			auto it = internalFind(key);
			if (Rand() & 1) {
				leftRotate(it);
			} else {
				rightRotate(it);
			}
		}
		bool operator == (const BST& t2) const {
			return checkSame(this->mRoot, t2.mRoot);
		}
};

BST T;
map<int, double> S;
BST R1, R2;

bool bstTest(int N, int Key) {
	T.clear();
	S.clear();
	for (int i=1; i<=N; i++) {
		int typ = Rand() % 3;
		auto val = make_pair(Rand() % Key, Rand01());
		if (i <= N/10 && N > 1000)
			typ = 0;
		switch (typ) {
			case 0:
//				printf("Insert (%d, %f)\n", val.first, val.second);
				T.insert(val);
				S.insert(val);
				break;
			case 1:
//				printf("Remove %d\n", val.first);
				T.remove(val.first);
				if (S.count(val.first))
					S.erase(S.find(val.first));
				break;
			case 2: {
//				printf("Look for %d\n", val.first);
				auto tv = T.find(val.first);
				auto sv = S.find(val.first);
				if (Rand() & 1) {
					if (tv != T.end() && sv != S.end()) {
						++tv;
						++sv;
					}
				}
				if (sv == S.end()) {
					if (tv != T.end()) {
						puts("\e[38;5;196mERROR: Non-existing element found!\e[0m");
						fputs("ERROR: Non-existing element found!", flog);
						return false;
					}
				} else {
					if (tv == T.end()) {
						puts("\e[38;5;196mERROR: Expected element not found!\e[0m");
						fputs("ERROR: Expected element not found!", flog);
						return false;
					}
					if (tv->first != sv->first ||
						tv->second != sv->second) {
						printf("\e[38;5;196mERROR: Expected (%d,%f), Found (%d, %f)\e[0m\n",
							sv->first, sv->second, tv->first, tv->second);
						fprintf(flog, "ERROR: Expected (%d,%f), Found (%d, %f)\n",
							sv->first, sv->second, tv->first, tv->second);
						return false;
					}
				}
				break;
			}
		}
//		T.print();
	}
	if (!T.checkHeight()) {
		puts("\e[38;5;196mERROR: Height does not match!\e[0m");
		fputs("ERROR: Height does not match!", flog);
		return false;
	}
	return true;
}

bool equal(set<int> &v1, set<int> &v2) {
	if (v1.size() != v2.size())
		return false;
	for (auto i=v1.begin(), j=v2.begin(); i!=v1.end(); i++, j++) {
		if ((*i) != (*j))
			return false;
	}
	return true;
}

bool failTest(int N, int key) {
	R1.clear();
	R2.clear();
	int N1 = Rand() % N;
	int N2 = Rand() % N;
	set<int> V1;
	set<int> V2;
	for (int i=1; i<=N1; i++) {
		int val = Rand()%key;
		double tmp = Rand01();
//		printf("insert 1 %d\n", val);
		V1.insert(val);
		R1.insert(make_pair(val, tmp));
	}
	for (int i=1; i<=N2; i++) {
		int val = Rand()%key;
		double tmp = Rand01();
//		printf("insert 2 %d\n", val);
		V2.insert(val);
		R2.insert(make_pair(val, tmp));
	}
//	R1.print();
//	R2.print();
	bool ans = equal(V1, V2);
	bool ret = R1.sameKeys(R2);
	if (ans == ret)
		return true;
	printf("\e[38;5;196mERROR: Expected %d, Returned %d.\e[0m\n", ans, ret);
	fprintf(flog, "ERROR: Expected %d, Returned %d.\n", ans, ret);
	return false;
}


bool equalTest(int N, int key) {
	R1.clear();
	R2.clear();
	N = Rand() % N;
	vector<int> v;
	for (int i=1; i<=N; i++) {
		int val = Rand()%key;
		double tmp = Rand01();
		v.push_back(val);
		R1.insert(make_pair(val, tmp));
	}
	for (int i=0; i<(int)v.size(); i++) {
		int pos = Rand() % (i+1);
		swap(v[pos], v[i]);
	}
	for (auto e: v) {
		double tmp = Rand01();
		R2.insert(make_pair(e, tmp));
	}
	bool ret = R1.sameKeys(R2);
	if (ret) {
		R1.transform(R2);
		if (!R2.checkHeight()) {
			puts("\e[38;5;196mERROR: Height does not match!\e[0m");
			fputs("ERROR: Height does not match!", flog);
			return false;
		}
		if (R1 == R2)
			return true;
		printf("\e[38;5;196mERROR: Failed to transform BSTs.\e[0m\n");
		fprintf(flog, "ERROR: Failed to transform BSTs.\n");
		return false;
	}
	printf("\e[38;5;196mERROR: Equal BSTs are judged different.\e[0m\n");
	fprintf(flog, "ERROR: Equal BSTs are judged different.\n");
	return false;
}

bool check(const vector<int> &v) {
	switch (v[0]) {
		case 0: return bstTest(v[1], v[2]);
		case 1: return failTest(v[1], v[2]);
		case 2: return equalTest(v[1], v[2]);
		default: {
			printf("\e[38;5;196mUnrecognized data type: %d\e[0m\n", v[0]);
			fprintf(flog, "Unrecognized data type: %d\n", v[0]);
			return false;
		}
	}
}

int main(int argc, char **argv) {
	/* begin of generating data */
	vector<pair<string, vector<int> > > data;
	data.push_back({"Small Range Test #1", {0, 10, 10}});
	data.push_back({"Small Range Test #2", {0, 10, 3}});
	data.push_back({"Small Range Test #3", {0, 100, 10}});
	data.push_back({"Small Range Test #4", {0, 100, 3}});
	data.push_back({"Small Range Test #5", {0, 100, 100000000}});
	data.push_back({"Small Range Test #6", {0, 100, 10}});
	data.push_back({"Small Range Test #7", {0, 233, 100000000}});
	data.push_back({"Small Range Test #8", {0, 2333, 100000000}});
	for (int i=1; i<=1000; i++) {
		string desc = "Random RotateBST sameKeys Test #" + to_string(i);
		vector<int> param(3);
		param[0] = 1;
		param[1] = 10+i/10;
		if (Rand() & 1)
			param[2] = Rand() % i + 1;
		else
			param[2] = Rand() % 10000 + 1;
		data.push_back(make_pair(desc, param));
	}
	for (int i=1; i<=1000; i++) {
		string desc = "Equal RotateBST transform Test #" + to_string(i);
		vector<int> param(3);
		param[0] = 2;
		if (i > 900)
			param[1] = Rand() % 10000;
		else
			param[1] = 10+i/10;
		if (Rand() & 1)
			param[2] = Rand() % i + 1;
		else
			param[2] = Rand() % 10000000 + 1;
		data.push_back(make_pair(desc, param));
	}
	data.push_back({"Stress Test #1",      {0, 100000, 3}});
	data.push_back({"Stress Test #2",      {0, 100000, 100}});
	data.push_back({"Stress Test #3",      {0, 1000000, 100000000}});
	data.push_back({"Stress Test #4",      {1, 100000, 1000}});
	data.push_back({"Stress Test #5",      {1, 100000, 100000000}});
	data.push_back({"Stress Test #6",      {1, 1000000, 100000000}});
	data.push_back({"Stress Test #7",      {2, 100000, 1000}});
	data.push_back({"Stress Test #8",      {2, 100000, 100000000}});
	data.push_back({"Stress Test #9",      {2, 200000, 100000000}});
	data.push_back({"Stress Test #10",     {0, 1000000, 1000}});
	/* end of generating data */
	if (argc > 1)
		seed = atoi(argv[1]);
	else
		seed = time(0);
	printf("\e[38;5;033mReceived Seed:\e[0m %d\n", seed);
	fprintf(flog, "Received Seed: %d\n", seed);
	int passed = 0;
	puts("\e[38;5;033m===== Testing... =====\e[0m");
	fprintf(flog, "Judge details:\n");
	for (auto &test: data) {
		if (showCaseTitle)
			printf("\e[38;5;226m- Running %s\e[38;5;033m Parameters: [", test.first.c_str());
		fprintf(flog, "- Running %s Parameters: [", test.first.c_str());
		for (size_t i=0; i<test.second.size(); i++) {
			if (showCaseTitle)
				printf("%d", test.second[i]);
			fprintf(flog, "%d", test.second[i]);
			if (i < test.second.size()-1) {
				if (showCaseTitle)
					putchar(',');
				fprintf(flog, ",");
			}
		}
		if (showCaseTitle)
			puts("]...\e[0m");
		fprintf(flog, "]...\n");
		fflush(flog);
		fflush(stdout);
		size_t beg = clock();
		int prevseed = seed;
		bool res = check(test.second);
		if (res) {
			double usedt = ((double)clock()-beg)/CLOCKS_PER_SEC;
			if (showPassedCase)
				printf("\e[38;5;046mPassed.\e[38;5;033m Time:\e[0m %.3fs\n", usedt);
			fprintf(flog, "Passed. Time: %.3fs\n", usedt);
			passed++;
		} else {
			if (!showCaseTitle) {
				printf("\e[38;5;226m- Occured in %s\e[38;5;033m Parameters: [", test.first.c_str());
				for (size_t i=0; i<test.second.size(); i++) {
					printf("%d", test.second[i]);
					if (i < test.second.size()-1) {
						putchar(',');
					}
				}
				puts("].\e[0m");
			}
			if (terminateAtFirstFailure) {
				printf("\e[38;5;196mError detected. \e[38;5;033mSeed to produce this single case is:\e[0m %d.\n", prevseed);
				fprintf(flog, "ERROR: Seed to produce this single case is: %d.\n", prevseed);
				return 0;
			}
		}
	}
	if (passed == (int)data.size()) {
		printf("\e[38;5;046mAll test cases passed. (%d tests)\e[0m\n", (int)data.size());
		fprintf(flog, "All test cases passed. (%d tests)\n", (int)data.size());
	}
	else {
		printf("\e[38;5;196m%d / %d test cases failed.\e[0m\n", (int)data.size() - passed, (int)data.size());
		fprintf(flog, "%d / %d test cases failed.\n", (int)data.size() - passed, (int)data.size());
	}
	puts("Judge details saved in [judge.log].");
	fclose(flog);
	return 0;
}
