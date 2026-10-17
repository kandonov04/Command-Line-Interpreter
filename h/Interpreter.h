#ifndef Interpreter_h
#define Interpreter_h

#include "Reader.h"
#include "Parser.h"
#include "Maker.h"
#include "Command.h"
#include "Pipe.h"

#include <memory>


class Interpreter
{
public:

	//Returns the singleton instance of this class. Static. Singleton DP.
	static Interpreter* Instance();

	//Destructor.
	~Interpreter();

	//Disable copy constructor to ensure that there is only one instance.
	Interpreter(const Interpreter&) = delete;

	//Disable move constructor to ensure that there is only one instance.
	Interpreter(Interpreter&& other) noexcept = delete;

	//Disable assignment operator to enforce singleton.
	Interpreter& operator=(const Interpreter&) = delete;

	//Disable move assignment operator to enforce singleton.
	Interpreter& operator=(Interpreter&& other) noexcept = delete;

	//Prints the ready character and reads one line from standard input.
	std::string prepare();

	//Receives a line of code and runs it step by step.
	void run(std::string line);

	//Sets a new ready character.
	void setReadyChar(std::string newChar);

private:

	//Constructor. In private so that only one instance of the class can ever exist.
	Interpreter();

	std::string readyChar;
	Reader* reader;
	Parser* parser;
	Pipe* pipe;
	Maker* maker;

};

#endif