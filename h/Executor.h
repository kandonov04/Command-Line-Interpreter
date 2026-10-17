#ifndef Executor_h
#define Executor_h

#include "FileHandler.h"

class Executor
{
public:

	//Constructor.
	Executor();

	//Destructor.
	~Executor();

	//Copy constructor.
	Executor(const Executor& other);

	//Copy assignment operator.
	Executor& operator=(const Executor& other);

	//Move constructor.
	Executor(Executor&& other) noexcept;

	//Move assignment operator.
	Executor& operator=(Executor&& other) noexcept;

	//Based on the output, it prints the line to standard output or to a file.
	void print(std::string linija, std::string output);

private:

	FileHandler* fileHandler;

};

#endif

