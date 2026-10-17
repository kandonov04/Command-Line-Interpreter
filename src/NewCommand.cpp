#include "../h/NewCommand.h"

NewCommand::NewCommand(Types::Data* myData) : Command(myData)
{
	inputer = new Inputer();
	executor = new Executor();
	parser = new Parser();
	maker = new Maker();
}

NewCommand::~NewCommand()
{
	delete inputer;
	delete executor;
	delete parser;
	delete maker;
}

void NewCommand::checkError()
{
}

std::string NewCommand::inputCommand()
{
	return std::string();
}

std::string NewCommand::processCommand(std::string line)
{
	return std::string();
}

void NewCommand::doCommand()
{
}
