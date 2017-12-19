#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[])
{
  if(argc < 3){
    cout << "Not enough arguments" << endl;
    return 1;
  }
  int n = atoi(argv[1]);
  int k = atoi(argv[2]);
  for(int i=0; i < n; i++){
    cout << 1 + rand()%k << " ";
  }
  cout << endl;
  return 0;
}
