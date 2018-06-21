#include <stdexcept>
#include <string>

// after all includes, add this
class LengthMismatch : public std::exception
{
  public:
	LengthMismatch(int x, int y);
	~LengthMismatch() throw() { }
	virtual const char* what() const throw();

  private:
	std::string msg;
};