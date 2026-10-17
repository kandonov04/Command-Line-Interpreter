#ifndef CommandWc_h
#define CommandWc_h

#include "Command.h"

#include "Inputer.h"
#include "Executor.h"

class CommandWc : public Command
{
public:

	CommandWc(Types::Data* myData);

	virtual ~CommandWc() override;

	void cutBlanco(std::string& arg);

	void cutWord(std::string& arg);

	virtual void checkError() override;

	virtual std::string inputCommand() override;

	virtual std::string processCommand(std::string line) override;

	virtual void doCommand() override;


private:

	Inputer* inputer;
	Executor* executor;

};

#endif

