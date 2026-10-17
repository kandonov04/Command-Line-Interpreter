#ifndef CommandTr_h
#define CommandTr_h

#include "Command.h"

#include "Inputer.h"
#include "Executor.h"

class CommandTr : public Command
{
public:

	CommandTr(Types::Data* myData);

	virtual ~CommandTr() override;

	virtual void checkError() override;

	virtual std::string inputCommand() override;

	virtual std::string processCommand(std::string line) override;

	virtual void doCommand() override;

private:

	Inputer* inputer;
	Executor* executor;

};

#endif