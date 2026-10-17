#include "../h/CommandWc.h"
#include "../h/ErrorHandler.h"

CommandWc::CommandWc(Types::Data* myData) : Command(myData)
{
	inputer = new Inputer();
	executor = new Executor();
}

CommandWc::~CommandWc()
{
	delete inputer;
	delete executor;
}

void CommandWc::cutBlanco(std::string& arg)
{
	bool flag = true;

	for (int i = 0; i < arg.size(); i++) {
		if (!(std::isspace(static_cast<unsigned char>(arg[i])))) {
			flag = false;
			arg = arg.substr(i);
			break;
		}
	}

	if (flag == true) {
		arg.clear();
	}
}

void CommandWc::cutWord(std::string& arg)
{
	bool flag = false;

	for (int i = 0; i < arg.size(); i++) {
		if (std::isspace(static_cast<unsigned char>(arg[i]))) {
			flag = true;
			arg = arg.substr(i);
			break;
		}
	}

	if (flag == false) {
		arg.clear();
	}
}

void CommandWc::checkError()
{
	if (myData->opt.empty()) {
		throw ErrorHandler("missingOpt");
	}
	else if (myData->opt != "-w" && myData->opt != "-c") {
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

std::string CommandWc::inputCommand()
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

std::string CommandWc::processCommand(std::string line)
{
	if (myData -> opt == "-w") {
		int cnt = 0;
		cutBlanco(line);
		while (!line.empty()) {
			cutWord(line);
			cnt++;
			cutBlanco(line);
		}
		return std::to_string(cnt);
	}
	else if (myData->opt == "-c") {
		return std::to_string(line.length());
	}
	return std::string();
}

void CommandWc::doCommand()
{
	checkError();
	std::string in = inputCommand();
	std::string out = processCommand(in);
	executor->print(out, myData -> outputRedir);
}