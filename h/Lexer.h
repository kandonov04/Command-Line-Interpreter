#ifndef Lexer_h
#define Lexer_h

#include <string>

class Lexer
{
public:

	//Constructor.
	Lexer();

	//Destructor.
	~Lexer() = default;

	//Checks for lexical error in the whole line and prints them.
	void checkWholeLine(std::string line);

	//Checks for lexical for particular parts of command and prints them.
	void check(std::string line, std::string mode, int cnt, std::string arg);

};

#endif

