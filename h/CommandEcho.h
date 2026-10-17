#ifndef CommandEcho_h
#define CommandEcho_h

#include "Command.h"

#include "Inputer.h"
#include "Executor.h"

class CommandEcho : public Command
{
public:

	CommandEcho(Types::Data* myData);

	virtual ~CommandEcho() override;

	virtual void checkError() override;

	virtual std::string inputCommand() override;

	virtual std::string processCommand(std::string line) override;

	virtual void doCommand() override;

private:

	Inputer* inputer;
	Executor* executor;

};

#endif