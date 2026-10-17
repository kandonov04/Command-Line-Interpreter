#ifndef Inputer_h
#define Inputer_h

#include "Reader.h"
#include "FileHandler.h"

class Inputer
{
public:

	//Constructor.
	Inputer();

	//Destructor.
	~Inputer();

	//Copy constructor.
	Inputer(const Inputer& other);

	//Copy assignment operator.
	Inputer& operator=(const Inputer& other);

	//Move constructor.
	Inputer(Inputer&& other) noexcept;

	//Move assignment operator.
	Inputer& operator=(Inputer&& other) noexcept;

	//Based on the argument, reads from standard input or from a file and returns the result as a string.
	std::string input(std::string arg);

private:

	Reader* reader;
	FileHandler* fileHandler;

};

#endif

