#include "../h/Maker.h"

#include "../h/CommandEcho.h"
#include "../h/CommandTime.h"
#include "../h/CommandDate.h"
#include "../h/CommandTouch.h"
#include "../h/CommandWc.h"
#include "../h/CommandPrompt.h"
#include "../h/CommandTruncate.h"
#include "../h/CommandRm.h"
#include "../h/CommandTr.h"
#include "../h/CommandHead.h"
#include "../h/CommandBatch.h"
#include "../h/NewCommand.h"
#include "../h/ErrorHandler.h"

Maker::Maker()
{
}

Command* Maker::makeCmd(Types::Data* myData)
{
	//Based on command name, calls constructor for command. If the name is wrong, throws an error;
	Command* command = nullptr;

	if (myData->cmd == "echo") {
		command = new CommandEcho(myData);
	}
	else if (myData->cmd == "touch") {
		command = new CommandTouch(myData);
	}
	else if (myData->cmd == "time") {
		command = new CommandTime(myData);
	}
	else if (myData->cmd == "date") {
		command = new CommandDate(myData);
	}
	else if (myData->cmd == "wc") {
		command = new CommandWc(myData);
	}
	else if (myData->cmd == "prompt") {
		command = new CommandPrompt(myData);
	}
	else if (myData->cmd == "truncate") {
		command = new CommandTruncate(myData);
	}
	else if (myData->cmd == "rm") {
		command = new CommandRm(myData);
	}
	else if (myData->cmd == "tr") {
		command = new CommandTr(myData);
	}
	else if (myData->cmd == "head") {
		command = new CommandHead(myData);
	}
	else if (myData->cmd == "batch") {
		command = new CommandBatch(myData);
	}
	else if (myData->cmd == "") {
		command = new NewCommand(myData);
	}
	else {
		throw ErrorHandler("cmdNotExists");
	}
	return command;
}