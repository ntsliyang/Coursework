#include <string>
#include <vector>

// importing a whole namespace in a header is frowned upon
// this will at least let us write 'string'/'vector' below
using std::string;
using std::vector;

class BigInt {
   public:
      BigInt(string s);   // convert string to BigInt
      BigInt(string s, int base);
      string to_string(); // get string representation
      void add(BigInt b); // add another BigInt to this one
   private:
      // whatever you need
   	vector<int> s1; // string s; char vector s1; int vector int_s;
   	int bases; 
};
	