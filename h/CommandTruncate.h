#ifndef CommandTruncate_h
#define CommandTruncate_h

#include"Command.h"

#include <fstream>

class CommandTruncate : public Command
{
public:

	CommandTruncate(Types::Data* myData);

	virtual ~CommandTruncate() override = default;

	virtual void checkError() override;

	virtual std::string inputCommand() override;

	virtual std::string processCommand(std::string line) override;

	virtual void doCommand() override;

};

#endif

