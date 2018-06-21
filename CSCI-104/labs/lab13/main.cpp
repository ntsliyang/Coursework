#include "bstree.h"
#include <string>

using namespace std; 

int main() {
	cout << "\n=== CREATING DIGIMON BINARY SEARCH TREE ===\n" << endl;
	BSTree<string> digitree;
	digitree.insert("Ogremon");
	digitree.insert("Agumon");
	digitree.insert("Poromon");
	digitree.insert("Fairimon");
	digitree.insert("Seraphimon");
	digitree.insert("Lopmon");
	digitree.insert("Angewomon");
	digitree.insert("Koromon");
	digitree.insert("Greymon");
	digitree.insert("Cherubimon");

	if(digitree.search("Seraphimon"))
		cout << "Success: found Seraphimon" << endl;
	else
		cout << "Error: couldn't find Seraphimon" << endl;
	if(digitree.search("Agumon"))
		cout << "Success: found Agumon" << endl;
	else
		cout << "Error: couldn't find Agumon" << endl;
	if(!digitree.search("Aldamon"))
		cout << "Success: didn't find Aldamon" << endl;
	else
		cout << "Error: found Aldamon" << endl;

	cout << "\n=== PRE ORDER TRAVERSAL ===" << endl;
	vector<string> listPre2 = digitree.preOrderTraversal();
	for(unsigned int i = 0; i < listPre2.size(); i++)
		cout << listPre2[i] << " ";

	cout << "\n\n=== IN ORDER TRAVERSAL ===" << endl;
	vector<string> listIn2 = digitree.inOrderTraversal();
	for(unsigned int i = 0; i < listIn2.size(); i++)
		cout << listIn2[i] << " ";

	cout << "\n\n=== POST ORDER TRAVERSAL ===" << endl;
	vector<string> listPost2 = digitree.postOrderTraversal();
	for(unsigned int i = 0; i < listPost2.size(); i++)
		cout << listPost2[i] << " ";

	cout << "\n\n";
}