#include <iostream>
#include <fstream>
#include <string>
#include <set> 
#include <unordered_map>
#include <queue> // priority_queue
#include <vector>
#include <climits>
using namespace std;

struct Node {
	string name; // 
	int g; // length of path from start node to current node 
	int h; // heuristic value 
	Node* pred;
	bool visited;
	Node(string name, int g, int h, Node* pred, bool visited): name(name),
	g(g), h(h), pred(pred), visited(visited) {}
};

struct compare {
	bool operator () (const Node &lhs, const Node &rhs) const {
		if ((lhs.g + lhs.h) < (rhs.g + rhs.h)) return false; // make the move with smallest f-value.
		else if ((lhs.g + lhs.h) > (rhs.g + rhs.h)) return true;
		else {
			// choose the one with the smallest h-value 
			if (lhs.h < rhs.h) return false;
			else if (lhs.h > rhs.h) return true;
			else { // the node that has the smallest value in binary
				return (lhs.name > rhs.name);
			}
		}
	}
}; // comparator for breaking ties

int count(string str, char target) {
	int cnt = 0;
	for (unsigned int i = 0; i < str.length(); i++) {
		if (target == str[i]) {
			cnt++;
		}
	}
	return cnt;
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cout << "please provide two parameters" << endl;
		return 1;
	}
	string start(argv[1]); // start node's name
	ifstream ifile(argv[2]); // permitted.txt 
	if (ifile.fail()) {
		cout << "please provide a valid permitted file" << endl;
		return 1;
	}
	int n;
	ifile >> n; // number of nodes
	vector<Node*> perm;
	string line, goal;
	for (unsigned int i = 0; i < start.length(); i++) {
		goal.append("1");
	} // formulate the name of ending node
	while (getline(ifile, line)) {
		Node* temp = new Node(line, INT_MAX/2, count(line, '0'), NULL, false);
		perm.push_back(temp);
	} // set of all permissible nodes 
	priority_queue<Node, vector<Node>, compare> pq;
	unordered_map<string, Node*> m; // Node object mapped to its name
	for (auto i = perm.begin(); i != perm.end(); ++i) {
		m.insert(make_pair(((*i)->name), (*i)));
	} // create the map
	int expansion = 0; 
	m[start]->g = 0;
	bool flag = false;
	pq.push(*m[start]); 
	while (!pq.empty()) {
		Node v = pq.top();
		if (v.h == 0) {
			flag = true;
			break;
		} // find the end node
		// break the while loop
		pq.pop();	
		if (m[v.name]->visited == false) {
			expansion++; // increment expansion
			m[v.name]->visited = true; // mark as discovered
		}
		else {
			continue;
		}
		vector<Node*> outlinks;
		for (unsigned int i = 0; i < v.name.length(); i++) {
			if (v.name[i] == '0') {
				string tmp = v.name.substr(0, i) + '1' + v.name.substr(i+1);
				if (m.find(tmp) != m.end() && m.find(tmp)->second->visited == false) {
					outlinks.push_back(m[tmp]);	
				}
			}
			else if (v.name[i] == '1') {
				string tmp = v.name.substr(0, i) + '0' + v.name.substr(i+1);
				if (m.find(tmp) != m.end() && m.find(tmp)->second->visited == false) {
					outlinks.push_back(m[tmp]);
				}
			}
		}
		for (auto i = outlinks.begin(); i != outlinks.end(); ++i) {
			if ((*i)->pred == NULL || v.g + 1 < (*i)->g) {
				(*i)->g = v.g + 1;
				(*i)->pred = m[v.name];
				pq.push(**i);
			}
		}
	}

	if (flag == false) {
		cout << "No transformation" << endl;
	}
	else {
		vector<string> output;
		Node* temp = m[goal];
		while (temp) {
			output.push_back(temp->name);
			temp = temp->pred;
		}

		for (int i = output.size() - 1; i >= 0; i--) {
			cout << output[i] << endl;
		}
	}
	cout << "expansions = " << expansion << endl;

	for (auto i = perm.begin(); i != perm.end(); ++i) {
		delete *i;
	} // delete all the permissble nodes 
	// delete s; // delete the starting node
	// delete e; // delete the ending node
	ifile.close();
	return 0;
}