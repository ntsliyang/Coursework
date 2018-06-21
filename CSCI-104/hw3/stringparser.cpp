#include "stackstr.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

bool operands(char c)
{
	if (c >= 'a' && c <= 'z')
		return true;
	else
		return false;
} // function to check whether it is an operand

bool operators(char c)
{
	if (c == '+' || c == '-' || c == ')' || c == '(')
		return true;
	else
		return false;
} // function to check whether it is an operator

int weight(char c)
{
	int w = -1;
	if (c == '>' || c == '<')
		w = 2;
	else if (c == '+' || c == '-')
		w = 1;
	return w;
} // function to check weight of operators

bool precedence(char a, char b)
{
	int weighta = weight(a);
	int weightb = weight(b);
	if (weighta >= weightb)
		return true;
	else
		return false;
} // function to check precedence of operators

void printstring(string temp)
{
	for (unsigned int i = 0; i < temp.length(); i++)
	{
		cout << temp[i];
	}
	cout << endl;
}

int main(int argc, char *argv[])
{
	ifstream ifile(argv[1]);
	ofstream ofile(argv[2]);
	if (ifile.fail())
	{
		cout << "please input proper input files" << endl;
		return 0;
	}
	if (ofile.fail())
	{
		cout << "please input proper output files" << endl;
		return 0;
	}
	string line;
	string ope = "qwertyuiopasdfghjklzxcvbnm+-()<>";
	while (getline(ifile, line))
	{
		bool flag_malform = false;
		if (line == "")
		{
			ofile << "Malformed" << endl;
			continue;
		} // if the expression is empty, then it's malformed
		StackStr *s = new StackStr();
		// build a new stack for storing expressions
		bool op = false;
		for (unsigned int i = 0; i < line.length(); i++)
		{
			if (flag_malform == true)
			{
				break;
			}
			if (operands(line[i]))
			{
				op = true;
			}
			if (!((line[i] >= 'a' && line[i] <= 'z') || line[i] == ' ' || line[i] == '>' || line[i] == '<' || line[i] == '+' || line[i] == '-' || line[i] == '(' || line[i] == ')'))
			{
				ofile << "Malformed" << endl;
				flag_malform = true;
				break;
			}
			if (line[i] == ' ')
				continue;
			if (operands(line[i]) == true)
			{
				//				int idx = i;
				//				int increment = 1;
				size_t found1 = line.find_first_of(ope, i + 1);
				if (found1 != std::string::npos)
				{
					if (line[found1] == '(')
					{
						ofile << "Malformed" << endl;
						flag_malform = true;
						break;
					}
				}
				size_t found2 = line.find_last_of(ope, i - 1);
				if (found2 != std::string::npos)
				{
					if (line[found2] == ')')
					{
						ofile << "Malformed" << endl;
						flag_malform = true;
						break;
					}
				}
			}
			string str(1, line[i]);
			s->push(str);
			if (line[i] == ')')
			{
				size_t found3 = line.find_first_of(ope, i + 1);
				if (found3 != std::string::npos && line[found3] == '(')
				//				if (i < line.length() - 1 && line[i + 1] == '(')
				{
					ofile << "Malformed" << endl;
					flag_malform = true;
					break;
				}
				string temp;
				while (s->size() > 0)
				{
					if (s->top() == " ")
						s->pop();
					temp += s->top();
					s->pop();
					if (s->top() == "(")
					{
						string tmp = s->top();
						temp += tmp.c_str();
						s->pop();
						break;
					};
				}
				cout << "temp before if: ";
				printstring(temp);
				if (temp[temp.length() - 1] == '(' && flag_malform == false)
				{
					std::reverse(temp.begin(), temp.end());
					printstring(temp);
					int max_weight = -1;
					int n_minus = 0;
					bool flag_plus = false;
					bool flag_minus = false;
					bool two_parameters = true;
					bool end_of_string = false;
					for (unsigned int j = 0; j < temp.length(); j++)
					{
						if (weight(temp[j]) > max_weight)
						{
							max_weight = weight(temp[j]);
						}
						if (temp[j] == '+')
						{
							flag_plus = true;
							if (!((operands(temp[j + 1]) == true || temp[j + 1] == '>' || temp[j + 1] == '<') && (operands(temp[j - 1]) == true || temp[j - 1] == '>' || temp[j - 1] == '<')))
							{
								two_parameters = false;
							}
						}
						if (temp[j] == '-')
						{
							n_minus++;
							flag_minus = true;
							if (!((operands(temp[j + 1]) == true || temp[j + 1] == '>' || temp[j + 1] == '<') && (operands(temp[j - 1]) == true || temp[j - 1] == '>' || temp[j - 1] == '<')))
							{
								two_parameters = false;
							}
						}
						if (temp[j] == '>' || temp[j] == '<')
						{
							if (operands(temp[j - 1]))
								end_of_string = true;
						}
					}

					if (max_weight == -1 || (flag_plus == false && flag_minus == false) || (flag_plus == true && flag_minus == true) || two_parameters == false || end_of_string == true || n_minus >= 2)
					{
						ofile << "Malformed" << endl;
						flag_malform = true;
						break;
					}
					// 1. no operator in the parantheses, thus malformed
					// 2. no + or - in parantheses, thus malformed
					// 3. + and - operators mixed, thus malformed
					// 4. there are no valid operands on both sides of + and
					// -, thus malformed
					// 5. >< operators at end of the strings, thus malformed
					// 6. more than one '-' operator used, thus malformed

					// 1. + and ><; max_weight = 2;
					// 2. - and ><; max_weight = 2;
					// 3. +; max_weight = 1;

					// >>yoda+go: normal order
					// <<asgrnfkj+><<dfgkala+>fp: normal order
					string temp1;
					string temp2;
					if (flag_malform == false)
					{
						for (unsigned int j = 0; j < temp.length(); j++)
						{
							if ((j != 0) && ((operands(temp[j]) == true) && (temp[j - 1] == '>' || temp[j - 1] == '<')))
							{
								int pos = j;
								while (operands(temp[pos]))
								{
									pos++;
								} // pos points to the position of the last letter
								pos -= 1;
								cout << "j " << j << " and pos " << pos << endl;
								while ((j != 0) && (temp[j - 1] == '>' || temp[j - 1] == '<'))
								{
									if (temp[j - 1] == '>')
									{
										if (pos - j >= 1)
										{
											temp = temp.substr(0, j) + temp.substr(j + 1); // remove the front character
											printstring(temp);
											pos -= 1;
										}
										temp = temp.substr(0, j - 1) + temp.substr(j); // remove the '>' operator
										printstring(temp);
										pos -= 1;
										if (j >= 1)
											j--;
									}
									else if (temp[j - 1] == '<')
									{
										if (pos - j >= 1)
										{
											temp = temp.substr(0, pos) + temp.substr(pos + 1); // remove the back character
											printstring(temp);
											pos -= 1;
										}
										temp = temp.substr(0, j - 1) + temp.substr(j); // remove the '<' operator
										printstring(temp);
										pos -= 1;
										if (j >= 1)
											j--;
									}
								}
							}
						}

						for (unsigned int j = 0; j < temp.length(); j++)
						{
							if (temp[j] == '+')
							{
								temp = temp.substr(0, j) + temp.substr(j + 1);
								if (j >= 1)
									j--;
							}
							else if (temp[j] == '-')
							{
								int cnt4 = 1;
								int cnt5 = 1;
								while (operands(temp[j - cnt4]))
								{
									temp1 += temp[j - cnt4];
									cnt4++;
								}
								reverse(temp1.begin(), temp1.end());
								// j: position of '-'
								// j - cnt4 + 1: position of first letter of temp1
								// j - 1: position of last letter of temp1
								// j + 1: position of first letter of temp2
								// j + cnt5 - 1: position of last letter of temp2
								//
								while (operands(temp[j + cnt5]))
								{
									temp2 += temp[j + cnt5];
									cnt5++;
								}
								if (temp1 == temp2)
								{
									ofile << "Malformed" << endl;
									flag_malform = true;
									break;
								}
								size_t found = temp1.find(temp2);
								cout << temp1.length() << ' ' << temp2.length() << endl;
								if (found != std::string::npos)
								{
									// means found
									cout << found << endl;
									temp = temp.substr(0, 1) + temp.substr(1, found) + temp.substr(1 + found + temp2.length(), temp1.length() - temp2.length() - found) + temp.substr(temp.length() - 1);
								}
								else
								{
									// means not found
									temp = temp.substr(0, temp1.length() + 1) + temp.substr(temp.length() - 1);
								}
							}
						}
					}

					if (flag_malform == false)
					{
						for (unsigned int j = 1; j < temp.length() - 1; j++)
						{
							string srt(1, temp[j]);
							s->push(srt);
						}
						cout << "temp at end of if: ";
						printstring(temp);
					}
				}
				else
				{
					ofile << "Malformed" << endl;
					flag_malform = true;
					break;
				} // no corresponding left parantheses
			}
		}

		if (op == false && flag_malform == false)
		{
			ofile << "Malformed" << endl;
			flag_malform = true;
			continue;
		}
		string temp3;
		string temp4;
		if (flag_malform == false)
		{
			while (s->size() > 0)
			{
				temp4 += s->top();
				if (s->top() == " ")
					s->pop();
				if (s->top() == "(")
				{
					break;
				}
				temp3 += s->top();
				s->pop();
			}
			cout << "temp4: ";
			printstring(temp4);
			cout << "s->size " << s->size() << endl;
			if (s->size() != 0)
			{
				ofile << "Malformed" << endl;
				continue;
			}
			std::reverse(temp3.begin(), temp3.end());
			cout << "temp3 ";
			printstring(temp3);
			for (unsigned int i = 0; i < temp3.length(); i++)
			{
				if ((i != 0) && ((operands(temp3[i]) == true) && (temp3[i - 1] == '>' || temp3[i - 1] == '<')))
				{
					int pos2 = i;
					while (operands(temp3[pos2]))
						pos2++;
					pos2 -= 1;
					while ((i != 0) && (temp3[i - 1] == '>' || temp3[i - 1] == '<'))
					{
						if (temp3[i - 1] == '>')
						{
							if (pos2 - i >= 1)
							{
								temp3 = temp3.substr(0, i) + temp3.substr(i + 1);
								pos2 -= 1;
							}
							temp3 = temp3.substr(0, i - 1) + temp3.substr(i);
							pos2 -= 1;
							if (i >= 1)
								i--;
						}
						else if (temp3[i - 1] == '<')
						{
							if (pos2 - i >= 1)
							{
								temp3 = temp3.substr(0, pos2) + temp3.substr(pos2 + 1);
								pos2 -= 1;
							}
							temp3 = temp3.substr(0, i - 1) + temp3.substr(i);
							pos2 -= 1;
							if (i >= 1)
								i--;
						}
					}
				}
				else if (temp3[i] == '>' || temp3[i] == '<')
				{
					if (i != 0 && operands(temp3[i - 1]) == true)
					{
						ofile << "Malformed" << endl;
						flag_malform = true;
						break;
					}
				}
				else if (temp3[i] == '+' || temp3[i] == '-')
				{
					ofile << "Malformed" << endl;
					flag_malform = true;
					break;
				}
			}
		}

		if (flag_malform == false)
		{
			for (unsigned int i = 0; i < temp3.length(); i++)
			{
				ofile << temp3[i];
			}
			ofile << endl;
		}

		delete s;
	}

	ifile.close();
	ofile.close();
	return 0;
}