#include <iostream>
#include <cstdlib>

using namespace std;
int main(int argc, char* argv[])
{
  double sum = 0.0;
  double x;
  int cnt = 0;
  cin >> x;
  while( ! cin.fail() ){
    sum += x;
    cnt++;
    cin >> x;
  }
  cout << sum / cnt << endl;
  return 0;
}
