#ifndef CommandHead_h
#define CommandHead_h

#include "Command.h"

#include <regex>

#include "Inputer.h"
#include "Executor.h"

class CommandHead : public Command
{
public:

	CommandHead(Types::Data* myData);

	virtual ~CommandHead() override;

	virtual void checkError() override;

	virtual std::string inputCommand() override;

	virtual std::string processCommand(std::string line) override;

	virtual void doCommand() override;

private:

	Inputer* inputer;
	Executor* executor;

};

#endif

