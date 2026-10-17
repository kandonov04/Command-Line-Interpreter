#include "../h/Pipe.h"
#include "../h/ErrorHandler.h"

Pipe::Pipe()
{
	maker = new Maker();
	inputer = new Inputer();
	executor = new Executor();
}

Pipe::~Pipe()
{
	delete inputer;
	delete executor;
	delete maker;
}

void Pipe::checkError(std::vector<Types::Data*> myData)
{
	for (int i = 0; i < myData.size(); i++) {
		if (i == 0) {
			if (!(myData[i]->outputRedir).empty()) {
				throw ErrorHandler("pipeRdr");
			}
		}
		else {
			//Only the last command may have an output redirection, and none of them may have an input redirection.
			if (!(myData[i]->inputRedir).empty() || (i != myData.size() - 1 && !(myData[i]->outputRedir).empty())) {
				throw ErrorHandler("pipeRdr");
			}

			if (myData[i]->arg.size() > 0 && noArg.count(myData[i]->cmd)) {
				throw ErrorHandler("pipeArg");
			}
			else if (myData[i]->arg.size() > 2 && yesArg.count(myData[i]->cmd)) {
				throw ErrorHandler("pipeArg");
			}
		}
	}
}

void Pipe::execute(std::vector<Types::Data*> myData)
{
	std::string in;
	std::string temp;
	std::string out;

	checkError(myData);

	
	for (int i = 0; i < myData.size(); i++) {
		if (i == 0) { //The first command only has an input stream, so we call inputCommand and processCommand to process a string.
			if (notAllowed.count(myData[0] -> cmd)) { //Commands prompt, touch, truncate and rm are not allowed in pipe.
				throw ErrorHandler("forbiddenCmd");
			}
			std::unique_ptr<Command> command(maker->makeCmd(myData[0])); //Deleted automatically, even when an exception is thrown.
			command->checkError();
			in = command->inputCommand();
			temp = command->processCommand(in);
		}
		else { //Other commands don't have an input stream. They receive an argument from the previous function.
			if (!(dateAndTime.count(myData[i]->cmd))) { //if date and time are in pipe, they don't need additional arguments, because they create their own argument.
				myData[i]->arg.insert(myData[i]->arg.begin(), temp);
			}
			if (notAllowed.count(myData[i]->cmd)) {
				throw ErrorHandler("forbiddenCmd");
			}
			std::unique_ptr<Command> command(maker->makeCmd(myData[i]));
			command->checkError();
			temp = command->processCommand(temp);
		}

		if (i == myData.size() - 1) { //The last command prints the string to its output stream.
			out = myData[i]->outputRedir;
			if (myData[i]->cmd == "batch") { //Command Batch is writing 2 times in file, because of errors, so we manually change it to append.
				if (!out.empty()) {
					if (!(out[1] == '>')) {
						out = '>' + out;
					}
				}
			}
		}
	}
	executor->print(temp, out);
}
