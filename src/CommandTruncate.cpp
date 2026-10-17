#include "../h/CommandTruncate.h"
#include "../h/ErrorHandler.h"

CommandTruncate::CommandTruncate(Types::Data* myData) : Command(myData)
{
}

void CommandTruncate::checkError()
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

std::string CommandTruncate::inputCommand()
{
	return std::string();
}

std::string CommandTruncate::processCommand(std::string line)
{
	return std::string();
}

void CommandTruncate::doCommand()
{
	checkError();
	std::ifstream checkFile(myData->arg[0]);
	if (!checkFile.is_open()) {
		throw ErrorHandler("notExists");
	}
	checkFile.close();
	std::ofstream file(myData->arg[0]);
}
