#include "../h/CommandHead.h"
#include "../h/ErrorHandler.h"

CommandHead::CommandHead(Types::Data* myData) : Command(myData)
{
	inputer = new Inputer();
	executor = new Executor();
}

CommandHead::~CommandHead()
{
	delete inputer;
	delete executor;
}

void CommandHead::checkError()
{
	std::regex pattern("^-n\\d{1,5}$");
	if (myData->opt.empty()) {
		throw ErrorHandler("missingOpt");
	}
	else if (!std::regex_match(myData->opt, pattern)) {
		throw ErrorHandler("optNotExists");
	}

	if (myData->arg.size() > 1) {
		throw ErrorHandler("tooManyArg");
	}
	else if (myData->arg.size() < 1 && myData->inputRedir.empty()) {
		throw ErrorHandler("notEnoughArg");
	}
	else if (myData->arg.size() == 1 && !myData->inputRedir.empty()) {
		throw ErrorHandler("redir&arg");
	}
}

std::string CommandHead::inputCommand()
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

std::string CommandHead::processCommand(std::string line)
{
	std::string opt = myData->opt;
	opt = opt.substr(2);
	int stop = std::stoi(opt);
	int cnt = 0;

	for (int i = 0; i < line.size(); i++) {
		if (line[i] == '\n') {
			cnt++;
		}
		if (cnt == stop) {
			line = line.substr(0, i);
			break;
		}
	}
	return line;
}

void CommandHead::doCommand()
{
	checkError();
	std::string in = inputCommand();
	std::string out = processCommand(in);
	executor->print(out, myData->outputRedir);
}
