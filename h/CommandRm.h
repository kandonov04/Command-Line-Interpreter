#ifndef CommandRm_h
#define CommandRm_h

#include "Command.h"

#include <fstream>

class CommandRm : public Command
{
public:

	CommandRm(Types::Data* myData);

	virtual ~CommandRm() override = default;

	virtual void checkError() override;

	virtual std::string inputCommand() override;

	virtual std::string processCommand(std::string line) override;

	virtual void doCommand() override;

};

#endif

