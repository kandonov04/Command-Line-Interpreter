#include "../h/ErrorHandler.h"

ErrorHandler::ErrorHandler(std::string arg)
{
	this->helper = arg;
}

const char* ErrorHandler::what() const noexcept
{
	//SEMANTIC ERRORS...
	//Command errors.
	if (helper == "cmdNotExists") {
		return "Semantic error! Command does not exist.";
	}
	else if (helper == "forbiddenCmd") {
		return "Semantic error! Specific command is not allowed in pipe";
	}
	//Option errors.
	else if (helper == "optNotExists") {
		return "Semantic error! Option does not exists";
	}
	else if (helper == "optNotSupported") {
		return "Semantic error! This function does not support option.";
	}
	//Redirection errors.
	else if (helper == "inRdrNotSupported") {
		return "Semantic error! This function does not support input redirection.";
	}
	else if (helper == "outRdrNotSupported") {
		return "Semantic error! This function does not support output redirection.";
	}
	//Pipe errors.
	else if (helper == "pipeRdr") {
		return "Semantic error! Redirection is not allowed in pipe";
	}
	else if (helper == "pipeArg") {
		return "Semantic error! Explicit argument passing is not allowed.";
	}

	//SYNTAX ERRORS...
	//Order error.
	else if (helper == "wOrder") {
		return "Syntax error! Wrong order.";
	}
	//Option errors.
	else if (helper == "missingOpt") {
		return "Syntax error! Missing an option.";
	}
	else if (helper == "multipleOpt") {
		return "Syntax error! More than one option is given.";
	}
	//Argument errors.
	else if (helper == "tooManyArg") {
		return "Syntax error! Too many arguments";
	}
	else if (helper == "notEnoughArg") {
		return "Syntax error! Not enough arguments";
	}
	//Redirection errors.
	else if (helper == "redir&arg") {
		return "Syntax error! Both redirection and argument are given";
	}
	else if (helper == "multipleRdr") {
		return "Syntax error! More than one redirection is given.";
	}

	//SYSTEM ERRORS...
	//File Errors.
	if (helper == "exists") {
		return "System error! File already exists.";
	}
	else if (helper == "notExists") {
		return "System error! File does not exist.";
	}

	//UNEXPECTED ERROR.
	else {
		return "Unexpected error";
	}
}
