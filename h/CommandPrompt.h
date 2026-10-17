#ifndef CommandPrompt_h
#define CommandPrompt_h

#include "Command.h"

#include "Inputer.h"

class CommandPrompt : public Command
{
public:

	CommandPrompt(Types::Data* myData);

	virtual ~CommandPrompt() override;

	virtual void checkError() override;

	virtual std::string inputCommand() override;

	virtual std::string processCommand(std::string line) override;

	virtual void doCommand() override;

private:

	Inputer* inputer;

};

#endif

