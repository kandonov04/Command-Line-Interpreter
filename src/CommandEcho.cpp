#include "../h/CommandEcho.h"
#include "../h/ErrorHandler.h"

CommandEcho::CommandEcho(Types::Data* myData) : Command(myData)
{
	inputer = new Inputer();
	executor = new Executor();
}

CommandEcho::~CommandEcho()
{
	delete inputer;
	delete executor;
}

void CommandEcho::checkError()
{
	if (myData->arg.size() > 1) {
		throw ErrorHandler("tooManyArg");
	}
	else if (myData->arg.size() < 1 && myData->inputRedir.empty()) {
		throw ErrorHandler("notEnoughArg");
	}
	else if (myData->arg.size() == 1 && !myData->inputRedir.empty()) {
		throw ErrorHandler("redir&arg");
	}

	if (!myData->opt.empty()) {
		throw ErrorHandler("optNotSupported");
	}
}

std::string CommandEcho::inputCommand()
{
	std::string line;

	if (!(myData->inputRedir).empty()) {
		line = inputer->input(myData->inputRedir);
	}
	else {
		line = inputer->input(myData->arg[0]);
	}

	return line;
}

std::string CommandEcho::processCommand(std::string line)
{
	return line;
}

void CommandEcho::doCommand()
{
	checkError();
	std::string in = inputCommand();
	std::string out = processCommand(in);
	executor->print(out, myData->outputRedir);
}

