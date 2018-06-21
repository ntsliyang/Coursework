#include "webpage.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <map>
#include <iterator>
#include <vector>
using namespace std;

void printstring(string& str, ofstream &output)
{
	for (unsigned int i = 0; i < str.length(); i++)
	{
		output << str[i];
	}
	output << endl;
} // function to print the string 

vector<string> split(string line) {
	vector<string> temp;
	stringstream ss(line);
	string line2;
	while (ss >> line2) {
		temp.push_back(line2);
	}
	return temp;
} // split each query line to vector

set<string> intersection(set<string>& s1, set<string>& s2) {
	set<string> temp;
	for (auto i = s1.begin(); i != s1.end(); i++) {
		if (s2.find(*i) != s2.end()) {
			temp.insert((*i));
		}
	}
	return temp;
} // find the intersection of two sets of strings
// and return the intersected set

set<string> setunion(set<string>& s1, set<string>& s2) {
	set<string> temp = s1;
	for (auto i = s2.begin(); i != s2.end(); i++) {
		temp.insert(*i);
	}
	return temp;
} // find the union of two sets of strings, and return the union set

set<string> intersectWebPage(map<string, set<string> >& m)
{
	if (m.size() == 1) {
		return m.begin()->second;
	} // if there is only one set, return this set
	else {
		set<string> temp = m.begin()->second;
		for (auto i = m.begin(); i != m.end(); i++) {
			temp = intersection(temp, i->second);
		}
		return temp;
	}
}

set<string> unionWebPage(map<string, set<string> >& m)
{
	if (m.size() == 1) {
		return m.begin()->second;
	} // if there is only one set, return this set
	else {
		set<string> temp = m.begin()->second;
		for (auto i = m.begin(); i != m.end(); i++) {
			temp = setunion(temp, i->second);
		}
		return temp;
	}
}

void search(string command, stringstream &ss, ofstream &output,
			set<WebPage *>& wpset, map<string, set<WebPage *>>& m)
{
	string keyword;
	map<string, set<string> > m1;
	while (ss >> keyword)
	{
		for (unsigned int i = 0; i < keyword.length(); i++) {
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
		m1.insert(pair<string, set<string> > (keyword, s));
	}
	if (command == "AND")
	{
		set<string> in = intersectWebPage(m1);
		output << in.size() << endl;
		for (auto i = in.begin(); i != in.end(); i++) {
			output << *i << endl;
		}
	}
	else if (command == "OR")
	{
		set<string> un = unionWebPage(m1);
		output << un.size() << endl;
		for (auto i = un.begin(); i != un.end(); i++) {
			output << *i << endl;
		}
	}
}

void printandlinks(string command, stringstream &ss, ofstream &output, 
map<string, WebPage *>& m)
{
	string f;
	string anotherword;
	if (ss >> f && m.count(f) != 0)
	{
		if (ss >> anotherword) {
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

int main(int argc, char *argv[])
{
	ifstream index(argv[1]);
	ifstream query(argv[2]);
	ofstream output(argv[3]);
	if (index.fail() || query.fail())
	{
		output << "Please provide proper input files" << endl;
		return -1;
	}
	if (output.fail())
	{
		output << "Please provide proper output files" << endl;
		return -1;
	}

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

	for (auto it = wpset.begin(); it != wpset.end(); it++)
	{
		for (auto j = (*it)->getOutlinks().begin(); j != (*it)->getOutlinks().end(); j++) {
			for (auto k = wpset.begin(); k != wpset.end(); k++) {
				if ((*k)->getName() == (*j)) {
					(*k)->getInlinks().push_back((*j));
				}
			}
		}
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
		if (q.size() > 1) {
			if (q[0] == "AND" || q[0] == "OR") {
				search(command, ss, output, wpset, m2);
			}
			else if (q[0] == "PRINT" || q[0] == "INCOMING" ||
			q[0] == "OUTGOING") {
				printandlinks(command, ss, output, m1);
			}
			else {
				output << "Invalid query" << endl;
			}
		}
		else if (q.size() == 1 && q[0] != "") {
			set<string> wps;
				// single word search
				for (unsigned int i = 0; i < command.length(); i++) {
					command[i] = tolower(command[i]);
				}

				for (auto i = wpset.begin(); i != wpset.end(); i++)
				{
					set<string> w = (*i)->getWords();
					if (w.count(command) != 0) {
						wps.insert((*i)->getName());
					}
				}
				output << wps.size() << endl;
				for (auto i = wps.begin(); i != wps.end(); i++) {
					output << *i << endl;
				}
		}
		else {
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
	return 0;
}