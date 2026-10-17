#include "../h/CommandBatch.h"
#include "../h/LexicalError.h"
#include "../h/ErrorHandler.h"

CommandBatch::CommandBatch(Types::Data* myData) : Command(myData)
{
	parser = new Parser();
	maker = new Maker();
	pipe = new Pipe();
	inputer = new Inputer();
	executor = new Executor();
	fileHandler = new FileHandler();
}

CommandBatch::~CommandBatch()
{
	delete parser;
	delete inputer;
	delete executor;
	delete maker;
	delete pipe;
	delete fileHandler;
}

void CommandBatch::checkError()
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

std::string CommandBatch::inputCommand()
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

std::string CommandBatch::processCommand(std::string line)
{
	std::string temp;
	std::string in;
	std::string out;
	std::string text;
	std::string error;
	std::istringstream ss(line); //Beacuse batch is getting commands in newlines, we will create string stream from it.

	while (std::getline(ss, temp)) { //This while is working similar as interpreter.
		try {
			parser->parse(temp);
			if (parser->getData().size() > 1) {
				pipe->execute(parser->getData());
			}
			else {
				std::unique_ptr<Command> command(maker->makeCmd(parser->getData()[0])); //Deleted automatically, even when an exception is thrown.
				command->checkError();
				in = command->inputCommand();
				out = command->processCommand(in);
				//The main difference is here, because output from batch can be used as an argument for pipe.
				if (noArg.count(parser->getData()[0]->cmd)) { //If command doesn't have output string, we just do it (like create or remove a file).
					command->doCommand();
				}
				else { //If there is an output redirection, we print it there.
					if (!(parser->getData()[0]->outputRedir).empty()) {
						executor->print(out, parser->getData()[0]->outputRedir);
					}
					else {
						text += out + '\n'; //And for the standard output,wWe don�t print it right away, but we insert it into the text that we print at the end of the function.
					}
				}
			}
		}
		catch (const LexicalError& e) {
			if (!(myData->outputRedir).empty()) {
				error += std::string(e.what()) + '\n';
			}
			else {
				std::cerr << e.what() << std::endl;
			}
		}
		catch (const ErrorHandler&e) {
			if (!(myData->outputRedir).empty()) {
				error += std::string(e.what()) + '\n';
			}
			else {
				std::cerr << e.what() << std::endl;
			}
		}
	}
	if (!(text.empty())) {
		text = text.substr(0, text.length() - 1);
	}
	executor->print(error, myData->outputRedir);
	return text;
}

void CommandBatch::doCommand()
{
	checkError();
	std::string in = inputCommand();
	std::string out = processCommand(in);
	if (!myData->outputRedir.empty()) {
		if (!(myData->outputRedir[1] == '>')) {
			myData->outputRedir = '>' + myData->outputRedir;
		}
	}
	executor->print(out, myData -> outputRedir);
}
