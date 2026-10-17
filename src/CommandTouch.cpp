#include "../h/CommandTouch.h"
#include "../h/ErrorHandler.h"

CommandTouch::CommandTouch(Types::Data* myData) : Command(myData)
{
}

void CommandTouch::checkError()
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

std::string CommandTouch::inputCommand()
{
	return std::string();
}

std::string CommandTouch::processCommand(std::string line)
{
	return std::string();
}

void CommandTouch::doCommand()
{
	checkError();
    std::ifstream checkFile(myData->arg[0]);
    if (checkFile.is_open()) {
        throw ErrorHandler("exists");
    }
    else {
        std::ofstream createFile(myData->arg[0]);
    }
}
