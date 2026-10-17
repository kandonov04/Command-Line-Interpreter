#ifndef NewCommand_h
#define NewCommand_h

#include "Command.h"

#include "Inputer.h"
#include "Executor.h"
#include "Parser.h"
#include "Maker.h"

class NewCommand : public Command
{
public:

	NewCommand(Types::Data* myData);

	virtual ~NewCommand() override;

	virtual void checkError() override;

	virtual std::string inputCommand() override;

	virtual std::string processCommand(std::string line) override;

	virtual void doCommand() override;

private:

	Inputer* inputer;
	Executor* executor;
	Parser* parser;
	Maker* maker;

};

#endif

