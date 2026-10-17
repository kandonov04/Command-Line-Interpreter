#include "../h/CommandPrompt.h"
#include "../h/ErrorHandler.h"
#include "../h/Interpreter.h"

CommandPrompt::CommandPrompt(Types::Data* myData) : Command(myData)
{
	inputer = new Inputer();
}

CommandPrompt::~CommandPrompt()
{
	delete inputer;
}

void CommandPrompt::checkError()
{
	if (myData->arg.size() > 1) {
		throw ErrorHandler("tooManyArg");
	}
	else if (myData->arg.size() < 1) {
		throw ErrorHandler("notEnoughArg");
	}

	if (!myData->outputRedir.empty()) {
		throw ErrorHandler("outRdrNotSupported");
	}
	else if (!myData->inputRedir.empty()) {
		throw ErrorHandler("inRdrNotSupported");
	}

	if (!myData->opt.empty()) {
		throw ErrorHandler("optNotSupported");
	}
}

std::string CommandPrompt::inputCommand()
{
	std::string line = inputer->input(myData -> arg[0]);
	return line;
}

std::string CommandPrompt::processCommand(std::string line)
{
	return std::string();
}

void CommandPrompt::doCommand()
{
	checkError();
	std::string sign = inputCommand();
	Interpreter::Instance()->setReadyChar(sign);
}

