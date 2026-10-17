#ifndef CommandTime_h
#define CommandTime_h

#include "Command.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

#include "Executor.h"

class CommandTime : public Command
{
public:

	CommandTime(Types::Data* myData);

	virtual ~CommandTime() override;

	virtual void checkError() override;

	virtual std::string inputCommand() override;

	virtual std::string processCommand(std::string line) override;
	
	virtual void doCommand() override;

private:

	Executor* executor;

};

#endif

