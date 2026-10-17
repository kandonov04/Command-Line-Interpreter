#include "../h/CommandRm.h"
#include "../h/ErrorHandler.h"

CommandRm::CommandRm(Types::Data* myData) : Command(myData)
{
}

void CommandRm::checkError()
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

std::string CommandRm::inputCommand()
{
	return std::string();
}

std::string CommandRm::processCommand(std::string line)
{
	return std::string();
}

void CommandRm::doCommand()
{
	checkError();
	std::ifstream checkFile(myData->arg[0]);
	if (!checkFile.is_open()) {
		throw ErrorHandler("notExists");
	}
	checkFile.close();
	std::remove(myData->arg[0].c_str());
}
