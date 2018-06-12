#include "bigint.h"
#include <stdexcept>

BigInt::BigInt(string s) {
	bases = 10;
	int zero_as_int = '0';
	for (int i = s.length() - 1; i >= 0; i--) {
		s1.push_back(s[i] - zero_as_int);
	}
}

BigInt::BigInt(string s, int base) {
	bases = base;
	int zero_as_int = '0';
	for (int i = s.length() - 1; i >= 0; i--) {
		if (s[i] >= 'A' && s[i] <= 'Z') {
			s[i] = s[i] - 'A' + 10;
			s1.push_back(s[i]);
		}
		else {
			s1.push_back(s[i] - zero_as_int);
		}

	}
}

string BigInt::to_string() {
	string s2;
	for (int i = s1.size() - 1; i >= 0; i--) {
			if (s1[i] >= 10) {
				s2 += s1[i] + 'A' - 10;
			}
			else {
				s2 += s1[i] + '0';
			}

	}
	return s2;
}

void BigInt::add(BigInt b) {
	vector<int> b1;
	b1 = b.s1;

	int pos = 0;
	int addr;
	int scale;
	if (bases != b.bases) {
		throw std::runtime_error("Error - different bases");
	}
	if (s1.size() >= b1.size()) {
		while (pos < s1.size()) {
			if (pos >= b1.size()) {
				addr = s1[pos];
			}
			else {
				addr = s1[pos] + b1[pos];
			}

			if (addr >= bases) {
				scale = addr / bases;
				if (pos + 1 >= s1.size()) {
					s1.push_back(scale);
					s1[pos] = addr % bases;
				}
				else {
					s1[pos + 1] += scale;
					s1[pos] = addr % bases;
				}
			}
			else {
				s1[pos] = addr;
			}
			pos++;
		}
	}
	else {
		while (pos < b1.size()) {
			if (pos >= s1.size()) {
				addr = b1[pos];
			}
			else {
				addr = s1[pos] + b1[pos];
			}

			if (addr >= bases) {
				scale = addr / bases;
				if (pos + 1 >= s1.size()) {
					s1.push_back(scale);
					s1[pos] = addr % bases;
				}
				else {
					s1[pos + 1] += scale;
					s1[pos] = addr % bases;
				}
			}
			else {
					s1.push_back(addr);
				}
			}
			pos++;
		}
	}
		