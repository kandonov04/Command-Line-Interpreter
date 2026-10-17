#ifndef CommandTouch_h
#define CommandTouch_h

#include "Command.h"

#include <fstream>


class CommandTouch : public Command
{
public:

	CommandTouch(Types::Data* myData);

	virtual ~CommandTouch() override = default;

	virtual void checkError() override;

	virtual std::string inputCommand() override;

	virtual std::string processCommand(std::string line) override;

	virtual void doCommand() override;

};

#endif

