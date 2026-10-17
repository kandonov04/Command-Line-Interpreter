#include "../h/Interpreter.h"
#include "../h/LexicalError.h"
#include "../h/ErrorHandler.h"

Interpreter* Interpreter::Instance()
{
	static Interpreter instance;
	return &instance;
}

Interpreter::Interpreter()
{
	readyChar = "$";
	reader = new Reader();
	parser = new Parser();
	maker = new Maker();
	pipe = new Pipe();

}

Interpreter::~Interpreter()
{
	delete reader;
	delete parser;
	delete maker;
	delete pipe;
}

void Interpreter::setReadyChar(std::string newChar)
{
	this->readyChar = newChar;
}

std::string Interpreter::prepare()
{
	std::cout << readyChar;
	std::string line = reader->read();
	return line;
}

void Interpreter::run(std::string linija)
{
	try {
		parser->parse(linija);
		if (parser->getData().size() > 1) {
			pipe->execute(parser->getData());
		}
		else {
			std::unique_ptr<Command> command(maker->makeCmd(parser->getData()[0])); //Deleted automatically, even when an exception is thrown.
			command->doCommand();
		}
	}
	catch (const LexicalError& e) {
		std::cerr << e.what() << std::endl;
	}
	catch (const ErrorHandler& e) {
		std::cerr << e.what() << std::endl;
	}
}


