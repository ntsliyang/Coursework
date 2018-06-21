#ifndef WEBPAGE_H
#define WEBPAGE_H
#include <set>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

class WebPage
{
public:
	WebPage();
	// constructor
	~WebPage();
	// destructor
	void wordsParse(std::string str, std::ifstream& ifile);
	void inlinksParse(std::map<std::string, WebPage* >& m);
	std::string& getName();
	void setName(std::string n);
	std::vector<std::string>& getInlinks();
	void setOutlinks(std::vector<std::string> outlinks);
	std::vector<std::string>& getOutlinks();
	void setInlinks(std::vector<std::string> inlinks);
	std::set<std::string>& getWords();
    std::string lower(std::string str);
	std::string& getContents();
	void setNewWeight(double newweight);
	double getNewWeight();
	void setOldWeight(double oldweight);
	double getOldweight();

private:
	std::vector<std::string> inlinks;
	std::vector<std::string> outlinks;
	std::set<std::string> words;
	std::string contents;
	std::string name;
	double newweight;
	double oldweight; 
};

#endif
