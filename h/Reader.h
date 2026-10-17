#ifndef Reader_h
#define Reader_h

#include <string>

class Reader
{
public:

	//Constructor.
	Reader();

	//Destructor.
	~Reader() = default;

	//Reads one line of code from standard input.
	std::string read();

	//Reads multiple lines of code from standard input.
	std::string readMultipleLines();

};

#endif
