#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;

map<string, string> loadConfig(string str);
void parse(string f, set<string> &visited, ifstream &seed, ofstream &output);
void dfs(vector<string> outlinks, set<string> &visited, ofstream &output);
// prototype, signature

map<string, string> loadConfig(string str)
{
	ifstream file(str);
	map<string, string> m;
	string line;
	while (getline(file, line))
	{
		if (line.find("#") != -1 && line.substr(0, line.find("#")).find("=") == -1)
		{
			continue;
		}
		else if (line.find("#") != -1)
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
			while (parameter.back() == ' ')
				parameter.pop_back();
			value = line.substr(line.find('=') + 1);
			while (value.front() == ' ')
				value = value.substr(1);
			value = value.substr(0, value.find_first_of(' '));
			// cout << parameter << ' ' << value << endl;
			m.insert(pair<string, string>(parameter, value));
		}
	}
	return m;
}

void parse(string f, set<string> &visited, ifstream &seed, ofstream &output)
{
	if (seed.fail())
		return;
	// if seed file fails, just return
	if (visited.find(f) != visited.end())
		return;
	// if f is found, just return, means it is visited
	visited.insert(f);
	output << f << endl;
	string line;
	vector<string> outlinks;
	while (getline(seed, line))
	{
		for (int i = 0; i < line.length(); i++)
		{
			if (line[i] == '(')
			{ // link to file
				i += 1;
				string outlink;
				while (line[i] != ')')
				{
					string temp2(1, line[i]);
					outlink.append(temp2);
					i++;
				}
				outlinks.push_back(outlink);
			} // process link to file
		}
	}
	dfs(outlinks, visited, output);
}

void dfs(vector<string> outlinks, set<string> &visited, ofstream &output)
{
	// set<string> visited: whether or not visited
	// starting node: u
	for (auto i = outlinks.begin(); i != outlinks.end(); ++i)
	{
		// *i is one of the outgoing file
		if (visited.find(*i) == visited.end())
		{
			// if *i is not found, insert into visited
			// visited.insert(*i);
			//			output << *i << endl;
			ifstream temp(*i);
			if (!temp.fail())
			{
				parse(*i, visited, temp, output);
			}
		}
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
	ifstream index;
	ofstream output;
	set<string> visited;
	if (config.find("INDEX_FILE") != config.end() && config.find("OUTPUT_FILE") != config.end())
	{
		ifstream index(config.find("INDEX_FILE")->second);
		ofstream output(config.find("OUTPUT_FILE")->second);
		string line;
		while (getline(index, line))
		{
			ifstream ifile(line); // ifile refers to a single file
			parse(line, visited, ifile, output);
			ifile.close(); // close the single file
		}
		index.close();
		output.close();
	}
	return 0;
}