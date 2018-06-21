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
	void inlinksParse(std::set<WebPage *>& wpset, WebPage *w);
	std::string& getName();
	void setName(std::string n);
	std::vector<std::string>& getInlinks();
	std::vector<std::string>& getOutlinks();
	std::set<std::string>& getWords();
    std::string lower(std::string str);
	std::string& getContents();

private:
	std::vector<std::string> inlinks;
	std::vector<std::string> outlinks;
	std::set<std::string> words;
	std::string contents;
	std::string name;
};

#endif
