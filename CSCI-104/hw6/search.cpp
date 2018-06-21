#include "webpage.h"
#include "setutility.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
using namespace std;

void printstring(string str, ofstream &output);
set<WebPage *> expand(set<string> &s, map<string, WebPage *> &m);
void search(string command, stringstream &ss, ofstream &output,
			set<WebPage *> &wpset, map<string, WebPage *> &m, double probability, int n);
void printandlinks(string command, stringstream &ss, ofstream &output,
				   map<string, WebPage *> &m);
map<string, string> loadConfig(string str);
bool more_weight(WebPage *a, WebPage *b);
void PageRank(set<WebPage *> &CandSet, map<string, WebPage *> &m, double probability, int n, ofstream& output);

void printstring(string str, ofstream &output)
{
	for (unsigned int i = 0; i < str.length(); i++)
	{
		output << str[i];
	}
	output << endl;
} // function to print the string

vector<string> split(string line)
{
	vector<string> temp;
	stringstream ss(line);
	string line2;
	while (ss >> line2)
	{
		temp.push_back(line2);
	}
	return temp;
} // split each query line to vector

set<WebPage *> expand(set<string> &s, map<string, WebPage *> &m)
{
	set<WebPage *> CandSet;
	for (auto j = s.begin(); j != s.end(); ++j)
	{
		if (m[*j])
		{
			CandSet.insert(m[*j]);
			for (auto k = (m[*j])->getOutlinks().begin(); k != (m[*j])->getOutlinks().end(); ++k)
			{
				if (m[*k])
					CandSet.insert(m[*k]);
			}
			for (auto k = (m[*j])->getInlinks().begin(); k != (m[*j])->getInlinks().end(); ++k)
			{
				if (m[*k])
					CandSet.insert(m[*k]);
			}
		}
	}
	return CandSet;
} // Expand the Set of candidate search results

void search(string command, stringstream &ss, ofstream &output,
			set<WebPage *> &wpset, map<string, WebPage *> &m, double probability, int n)
{
	string keyword;
	map<string, set<string>> m1;
	set<WebPage *> CandSet;
	while (ss >> keyword)
	{
		for (unsigned int i = 0; i < keyword.length(); i++)
		{
			keyword[i] = tolower(keyword[i]);
		} // convert keyowrd to all lowercases
		set<string> s;
		for (auto i = wpset.begin(); i != wpset.end(); i++)
		{
			if ((*i)->getWords().count(keyword) != 0)
			{
				s.insert((*i)->getName());
			}
		} // get the set of webpages that contain the keyword
		m1.insert(pair<string, set<string>>(keyword, s));
	}
	if (command == "AND")
	{
		set<string> in = intersectWebPage(m1);
		CandSet = expand(in, m);
		PageRank(CandSet, m, probability, n, output);
		// output << CandSet.size() << endl;
		// for (auto i = CandSet.begin(); i != CandSet.end(); i++)
		// {
		// 	output << (*i)->getName() << endl;
		// }
	}
	else if (command == "OR")
	{
		set<string> un = unionWebPage(m1);
		CandSet = expand(un, m);
		PageRank(CandSet, m, probability, n, output);
		// output << CandSet.size() << endl;
		// for (auto i = CandSet.begin(); i != CandSet.end(); i++)
		// {
		// 	output << (*i)->getName() << endl;
		// }
	}
}

void printandlinks(string command, stringstream &ss, ofstream &output,
				   map<string, WebPage *> &m)
{
	string f;
	string anotherword;
	if (ss >> f && m.count(f) != 0)
	{
		if (ss >> anotherword)
		{
			output << "Invalid query" << endl;
		} // if there is anotherword in the stringstream, return as an invalid query
		else if (command == "PRINT")
		{
			output << f << endl;
			printstring(m.at(f)->getContents(), output);
		}
		else if (command == "INCOMING")
		{
			output << m.at(f)->getInlinks().size() << endl;
			auto k = m.at(f)->getInlinks();
			for (auto i = k.begin(); i != k.end(); i++)
			{
				printstring(*i, output);
			}
		}
		else if (command == "OUTGOING")
		{
			output << m.at(f)->getOutlinks().size() << endl;
			auto k = m.at(f)->getOutlinks();
			for (auto i = k.begin(); i != k.end(); i++)
			{
				printstring(*i, output);
			}
		}
	}
	else
	{
		output << "Invalid query" << endl;
	} // if no such file in the map, then return as an invalid query
}

map<string, string> loadConfig(string str)
{
	ifstream file(str);
	map<string, string> m;
	string line;
	while (getline(file, line))
	{
		if (line.find("#") != string::npos && line.substr(0, line.find("#")).find("=") == string::npos)
		{
			continue;
		}
		else if (line.find("#") != string::npos)
		{
			line = line.substr(0, line.find_first_of('#'));
		}
		if (!line.empty())
		{
			string parameter, value;
			while (line.front() == ' ')
				line = line.substr(1);
			// while (line.back() == ' ') line.pop_back();
			parameter = line.substr(0, line.find_first_of('='));
			if (parameter.empty()) continue;
			while (parameter.back() == ' ')
				parameter.pop_back();
			value = line.substr(line.find('=') + 1);
			while (value.front() == ' ')
				value = value.substr(1);
			value = value.substr(0, value.find_first_of(' '));
			if (value.empty()) continue;
			// cout << parameter << ' ' << value << endl;
			m.insert(pair<string, string>(parameter, value));
		}
	}
	return m;
}

bool more_weight(WebPage *a, WebPage *b)
{
	return a->getNewWeight() > b->getNewWeight();
}

void PageRank(set<WebPage *> &CandSet, map<string, WebPage *> &m, double probability, int n, ofstream& output)
{
	// add self-loop for each node
	map<string, set<string>> inMap;
	map<string, set<string>> outMap;
	set<string> CandString;
	for (auto i = CandSet.begin(); i != CandSet.end(); ++i) {
		CandString.insert((*i)->getName());
	}
	for (auto i = CandSet.begin(); i != CandSet.end(); ++i) {
		set<string> in;
		set<string> out;
		in.insert((*i)->getName()); // add self-loop
		for (auto j = (*i)->getInlinks().begin(); j != (*i)->getInlinks().end(); ++j) {
			if (CandString.find(*j) != CandString.end()) in.insert(*j);
		}
		out.insert((*i)->getName()); // add self-loop
		for (auto j = (*i)->getOutlinks().begin(); j != (*i)->getOutlinks().end(); ++j) {
			if (CandString.find(*j) != CandString.end()) out.insert(*j);
		}
		inMap[(*i)->getName()] = in;
		outMap[(*i)->getName()] = out;
	}

	// initialize the probability for all the nodes in candidate set
	for (auto i = CandSet.begin(); i != CandSet.end(); ++i)
	{
		(*i)->setOldWeight(1.0 / CandSet.size());		
	}	

	for (auto k = 0; k < n; k++)
	{
		for (auto i = CandSet.begin(); i != CandSet.end(); ++i)
		{
			double temp = 0.0;
			double inWeight = 0.0;
			for (auto j = inMap[(*i)->getName()].begin(); j !=inMap[(*i)->getName()].end(); ++j)
			{
				inWeight += (m[*j])->getOldweight() * 1.0 /outMap[(*j)].size();
			}
			temp = (1.0 - probability) * inWeight + probability * 1.0 / CandSet.size();
			(*i)->setNewWeight(temp);
			// cout << (*i)->getWeight() << endl;
		}

		// update weight of all other nodes 
		for (auto i = CandSet.begin(); i != CandSet.end(); ++i) {
			(*i)->setOldWeight((*i)->getNewWeight());
		}
	}
	vector<WebPage*> Candidate;
	for (auto i = CandSet.begin(); i != CandSet.end(); ++i) {
		Candidate.push_back(*i);
	}

	sort(Candidate.begin(), Candidate.end(), more_weight);
	output << Candidate.size() << endl;
	for (auto i = Candidate.begin(); i != Candidate.end(); ++i) {
		output << (*i)->getName() << endl;
	}
}

int main(int argc, char *argv[])
{
	map<string, string> config;
	if (argc == 2)
	{
		config = loadConfig(argv[1]);
	}
	else
	{
		config = loadConfig("config.txt");
	}
	double probability; // RESTART PROABILITY
	int n;				// STEP NUMBER
	// for (auto i = config.begin(); i != config.end(); ++i)
	// {
	// 	cout << i->first << endl
	// 		 << i->second << endl;
	// }
	// ifstream index;
	// ifstream query;
	// ofstream output;
	if (config.find("INDEX_FILE") != config.end() && config.find("QUERY_FILE") != config.end() && config.find("OUTPUT_FILE") != config.end())
	{
		ifstream index(config.find("INDEX_FILE")->second);
		ifstream query(config.find("QUERY_FILE")->second);
		ofstream output(config.find("OUTPUT_FILE")->second);
		if (config.find("RESTART_PROBABILITY") != config.end()) {
			stringstream ss(config.find("RESTART_PROBABILITY")->second);
			ss >> probability;
		}
			// probability = stold(config.find("RESTART_PROBAILITY")->second);
		if (config.find("STEP_NUMBER") != config.end()) {
			stringstream ss(config.find("STEP_NUMBER")->second);
			ss >> n;
		}
		// ifstream index(argv[1]);
		// ifstream query(argv[2]);
		// ofstream output(argv[3]);
		// if (index.fail() || query.fail())
		// {
		// 	output << "Please provide proper input files" << endl;
		// 	return -1;
		// }
		// if (output.fail())
		// {
		// 	output << "Please provide proper output files" << endl;
		// 	return -1;
		// }

		string line;
		set<WebPage *> wpset;
		while (getline(index, line))
		{
			ifstream ifile(line); // ifile refers to a single file
			if (ifile.fail())
			{
				output << "Invalid query" << endl;
				continue;
			}
			WebPage *wp = new WebPage; // instantiate
			string line2;
			wp->setName(line); // set the filepath of the webpage
			while (getline(ifile, line2))
			{
				wp->wordsParse(line2, ifile); // parse the words and outlinks
			}
			wpset.insert(wp); // insert individual webpage into the set
			ifile.close();	// close the single file
		}
		// finish the parsing for all relevant parts:
		// filepath, contents, inlinks, outlinks

		string line3;
		string command;
		map<string, WebPage *> m1;
		for (auto i = wpset.begin(); i != wpset.end(); i++)
		{
			m1.insert(pair<string, WebPage *>((*i)->getName(), (*i)));
		}
		for (auto it = wpset.begin(); it != wpset.end(); ++it)
		{
			(*it)->inlinksParse(m1);
		}
		// first map: use the filepath to locate WebPage object
		map<string, set<WebPage *>> m2;
		// second map: use the keyword to locate the set of WebPage
		// objects that contain this keyword

		vector<string> q;
		while (getline(query, line3))
		{
			stringstream ss(line3);
			ss >> command;
			q = split(line3);
			if (q.size() > 1)
			{
				if (q[0] == "AND" || q[0] == "OR")
				{
					search(command, ss, output, wpset, m1, probability, n);
				}
				else if (q[0] == "PRINT" || q[0] == "INCOMING" ||
						 q[0] == "OUTGOING")
				{
					printandlinks(command, ss, output, m1);
				}
				else
				{
					output << "Invalid query" << endl;
				}
			}
			else if (q.size() == 1 && q[0] != "")
			{
				set<WebPage *> CandSet;
				set<string> wps;
				// single word search
				for (unsigned int i = 0; i < command.length(); i++)
				{
					command[i] = tolower(command[i]);
				}

				for (auto i = wpset.begin(); i != wpset.end(); i++)
				{
					set<string> w = (*i)->getWords();
					if (w.count(command) != 0)
					{
						wps.insert((*i)->getName());
					}
				}
				CandSet = expand(wps, m1);
				PageRank(CandSet, m1, probability, n, output);
				// output << CandSet.size() << endl;
				// for (auto i = CandSet.begin(); i != CandSet.end(); i++)
				// {
				// 	output << (*i)->getName() << endl;
				// }
			}
			else
			{
				output << "Invalid query" << endl;
			}
		}

		for (auto i = wpset.begin(); i != wpset.end(); i++)
		{
			delete *i;
		}
		index.close();
		query.close();
		output.close();
	}
	return 0;
}