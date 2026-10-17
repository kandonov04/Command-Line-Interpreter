#ifndef LexicalError_h
#define LexicalError_h

#include <string>
#include <exception>
#include <iostream>

class LexicalError : public std::exception
{
public:

	//Constructor.
	LexicalError(std::string line, int cnt);

	//Destructor.
	~LexicalError() = default;

	//Returns description of an error based on helper, that is passed to the constructor as an argument.
	//This one also prints position of a lexical error in line.
	virtual const char* what() const noexcept;

private:

	std::string line;
	int position;
};

#endif