#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

int main(int argc, char*argv[]){
    ofstream output(argv[1]);
    if(output.fail()){
        cout << "please provide a valid output file" << endl;
        return 1;
    }
    for(int i=0; i<3000; i++){
        string ss = "";
        int z = rand() % 20 + 1;
        for(int j=0; j<z; j++){
            int r = rand() % 58 + 65;
            char c = (char)r;
            string s(1, c);
            ss += s;
        }
        output << ss << endl;
    }
    return 0;
}