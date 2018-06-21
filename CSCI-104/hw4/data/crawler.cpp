#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "webpage.h"
using namespace std;

struct Config {
	string index;
	string query;
	string output;
};

void loadConfig(Config& config){
	ifstream file("config.txt");
    string line;
	string temp;
	while (getline(file, line)) {
		stringstream ss(line.substr(line.find("=")+1));
		if (line.find("INDEX_FILE") != -1) {
			ss >> config.index;
		}
		else if (line.find("QUERY_FILE") != -1) {
			ss >> config.query;
		}
		else if (line.find("OUTPUT_FILE") != -1) {
			ss >> config.output;
		}
	}
}

void dfs() {

}
int main(int argc, char* argv[]) {
	Config config;
	loadConfig(config);
	ifstream index(config.index);
	ofstream output(config.output);
	

}