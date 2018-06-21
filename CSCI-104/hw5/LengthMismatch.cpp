#include "LengthMismatch.h"

LengthMismatch::LengthMismatch(int x, int y) : msg("Input data structures have lengths " +
									   std::to_string(x) + " and " + std::to_string(y))
{
}

const char *LengthMismatch::what() const throw()
{
	return msg.c_str();
}