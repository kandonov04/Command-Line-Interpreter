#ifndef Command_h
#define Command_h

#include "Types.h"

class Command
{
public:

	//Constructor.
	Command(Types::Data* myData);

	//Destructor.
	virtual ~Command() = default;

	//Functions with = 0, all of them are redefined in derived classes, doing similar things in every command.

	//ErrorChecker. Used for finding an error and throw a specific exception class.
	virtual void checkError() = 0;

	//Calls inputer based on myData -> arg. If command doesn't have an argument, it returns empty string.
	virtual std::string inputCommand() = 0;

	//Returns the processed line of code to be printed. If the command does not output any string, it returns an empty string.
	virtual std::string processCommand(std::string line) = 0;

	//Calls in order: checkError ->  inputCommand -> processCommand and executor at the end.
	virtual void doCommand() = 0;

protected:

	Types::Data* myData;

};

#endif
