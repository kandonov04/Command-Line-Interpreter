#ifndef CommandDate_h
#define CommandDate_h 

#include "Command.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

#include "Executor.h"

class CommandDate : public Command
{
public:

	CommandDate(Types::Data* myData);

	virtual ~CommandDate() override;

	virtual void checkError() override;

	virtual std::string inputCommand() override;

	virtual std::string processCommand(std::string line) override;

	virtual void doCommand() override;

private:

	Executor* executor;

};

#endif