#include "webpage.h"
using namespace std;

WebPage::WebPage()
{
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

vector<string>& WebPage::getOutlinks()
{
	return outlinks;
} // accessor outlinks function

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

void WebPage::inlinksParse(set<WebPage *>& wpset, WebPage *w)
{
	for (set<WebPage *>::iterator it = wpset.begin(); it != wpset.end(); it++)
	{
		for (auto j = (*it)->outlinks.begin(); j != (*it)->outlinks.end(); j++) {
			if (*j == w->name) {
				w->inlinks.push_back((*it)->name);
			}
		}
	} // parse the inlink file into each valid webpage
}