#ifndef CommandBatch_h
#define CommandBatch_h

#include "Command.h"

#include <sstream>
#include <set>
#include <memory>

#include "Inputer.h"
#include "Executor.h"
#include "FileHandler.h"
#include "Parser.h"
#include "Pipe.h"
#include "Maker.h"

class CommandBatch : public Command
{
public:

	CommandBatch(Types::Data* myData);

	virtual ~CommandBatch() override;

	virtual void checkError() override;

	virtual std::string inputCommand() override;

	virtual std::string processCommand(std::string line) override;

	virtual void doCommand() override;

private:

	FileHandler* fileHandler;
	Inputer* inputer;
	Executor* executor;
	Parser* parser;
	Pipe* pipe;
	Maker* maker;
	std::set<std::string> noArg = { "prompt", "rm", "touch", "truncate" };

};

#endif