#ifndef Pipe_h
#define Pipe_h

#include "Types.h"
#include "Inputer.h"
#include "Executor.h"
#include "Command.h"
#include "Maker.h"

#include <set>
#include <string>
#include <vector>
#include <memory>

class Pipe
{
public:

	//Constructor.
	Pipe();

	//Destructor.
	~Pipe();

	//ErrorChecker. Used for finding an error and throw a specific exception class.
	void checkError(std::vector< Types::Data*> myData);

	//Runs pipe step by step.
	void execute(std::vector< Types::Data*> myData);

private:

	Maker* maker;
	Inputer* inputer;
	Executor* executor;
	std::set<std::string> dateAndTime = { "date", "time"};
	std::set<std::string> notAllowed = { "prompt", "rm", "touch", "truncate" };
	std::set<std::string> noArg = { "echo", "wc", "head", "batch", "rm", "truncate", "touch",  "prompt", "time", "date"};
	std::set<std::string> yesArg = { "tr" };

};

#endif

