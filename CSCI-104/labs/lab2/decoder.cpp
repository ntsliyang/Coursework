#include <iostream>
#include <string>

// taken from http://stackoverflow.com/questions/3381614/c-convert-string-to-hexadecimal-and-vice-versa
std::string string_to_hex(const std::string & input)
{
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();

    std::string output;
    output.reserve(2 * len);
    for (size_t i = 0; i < len; ++i)
    {
        const unsigned char c = input[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }
    return output;
}

// recursive function to reverse a string
// you should start your debugging here with a breakpoint
std::string ReverseText(std::string & msg, int start = 0, int end = -1)
{
	if (end  ==  -1) end = msg.length() - 1;  // init case
	if (end < start) return msg;             // base case
	else
	{
		char hold  = msg[start];
		msg[start] = msg[end];
		msg[end]   = hold;
		return ReverseText(msg, start++, end--);
	}
}

// A simple loop-based decode function for string
std::string DecodeText(std::string & msg)
{
	size_t len = msg.length();
	for(size_t i = 0; i < len; ++i) msg[i] = msg[i] ^ 0x02;
	return msg;
}

// decodes a secret message
int main()
{	
	// Do not change this secret text
	std::string secret = "novj,vgpagq]02`cn-q`cn-623qa-wfg,aqw,qvk`";
	std::cout << "secret:  " << secret << std::endl;
	std::string rev = ReverseText(secret);
	std::cout << "Reverse: " << rev << std::endl;
	std::string msg = DecodeText(secret);
	std::cout << "Message: " << msg << std::endl;
	return 0;
}
