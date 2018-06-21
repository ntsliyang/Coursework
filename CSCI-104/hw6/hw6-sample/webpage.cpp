#include "webpage.h"
using namespace std;

WebPage::WebPage()
{
	newweight = 0.0;
	oldweight = 0,0;
}

WebPage::~WebPage()
{
}

string& WebPage::getName()
{
	return name;
} // accessor name function

void WebPage::setName(string n)
{
	name = n;
} // mutator name function

vector<string>& WebPage::getInlinks()
{
	return inlinks;
} // accessor inlinks function

void WebPage::setInlinks(vector<string> inlinks) {
	this->inlinks = inlinks;
}

vector<string>& WebPage::getOutlinks()
{
	return outlinks;
} // accessor outlinks function

void WebPage::setOutlinks(vector<string> outlinks) {
	this->outlinks = outlinks;
}

std::set<std::string>& WebPage::getWords()
{
	return words;
} // accessor words function

std::string& WebPage::getContents()
{
	return contents;
} // accessor contents function

string WebPage::lower(string str) {
	for (unsigned int i = 0; i < str.length(); i++) {
		str[i] = tolower(str[i]);
	}
	return str;
} // convert a string to all lowercase

void WebPage::wordsParse(string str, ifstream& ifile)
{
	string temp;
	if (str.empty() && (!(ifile.eof()))) contents.append("\n");
	for (unsigned int i = 0; i < str.length(); i++) {
			string tmp(1, str[i]);
			if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') 
			|| (str[i] >= '0' && str[i] <= '9')) {
				temp.append(tmp);
				if (i == str.length() - 1) {
					words.insert(lower(temp));
				}
			} // push valid characters
			else if (!temp.empty() || (!temp.empty() && i == str.length() - 1)) {
				words.insert(lower(temp));
				temp.clear();
			}
			else if (str[i] == '(')
			{ // link to file
				i += 1;
				string outlink;
				while (str[i] != ')')
				{
					string temp2(1, str[i]);
					outlink.append(temp2);
					i++;
				}
				outlinks.push_back(outlink);
			} // process link to file
			else if (str[i] == '[' || str[i] == ']') {
				str.erase(str.begin() + i); // erase the braces
				i -= 1;
			}
			if (tmp != "(") {
				contents.append(tmp);
			}

			if (i == str.length() - 1 && (!(ifile.eof()))) {
				contents.append("\n");
			}
	}
}

void WebPage::inlinksParse(map<string, WebPage* >& m)
{
	for (auto i = (*this).outlinks.begin(); i != (*this).outlinks.end(); ++i) {
		if (m[*i]) {
			(m[*i])->inlinks.push_back((*this).name);
		}
	} 
	// parse the inlink file into each valid webpage
}

void WebPage::setNewWeight(double newweight) {
	this->newweight = newweight;
}

double WebPage::getNewWeight() {
	return newweight;
}

void WebPage::setOldWeight(double oldweight) {
	this->oldweight = oldweight;
}

double WebPage::getOldweight() {
	return oldweight;
}