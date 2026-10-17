#include "../h/CommandTr.h"
#include "../h/ErrorHandler.h"

CommandTr::CommandTr(Types::Data* myData) : Command(myData)
{
	inputer = new Inputer();
	executor = new Executor();
}

CommandTr::~CommandTr()
{
	delete inputer;
	delete executor;
}

void CommandTr::checkError()
{

	if (myData->arg.size() > 3) {
		throw ErrorHandler("tooManyArg");
	}
	else if (myData->arg.size() < 2 && myData->inputRedir.empty()) {
		throw ErrorHandler("notEnoughArg");
	}
	else if (myData->arg.size() == 2 && !myData->inputRedir.empty()) {
		throw ErrorHandler("redir&arg");
	}

	if (!myData->opt.empty()) {
		throw ErrorHandler("optNotSupported");
	}
}

std::string CommandTr::inputCommand()
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

std::string CommandTr::processCommand(std::string line)
{;
	size_t start = 0;
	std::string what;
	std::string with;

	if (myData->arg.size() > 1) {
		what = (myData->arg[1]).substr(1, myData->arg[1].length() - 2);
	}
	else {
		what = (myData->arg[0]).substr(1, myData->arg[0].length() - 2);
	}

	if (myData->arg.size() > 2) {
		with = (myData->arg[2]).substr(1, myData->arg[2].length() - 2);;
	}

	if (what.empty()) { //Empty pattern would match at every position and loop forever.
		return line;
	}

	while ((start = line.find(what, start)) != std::string::npos) {
		line.replace(start, what.length(), with);
		start += with.length();
	}

	return line;
}

void CommandTr::doCommand()
{
	checkError();
	std::string in = inputCommand();
	std::string out = processCommand(in);
	executor->print(out, myData -> outputRedir);
}
