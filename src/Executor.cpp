#include <iostream>
#include "../h/Executor.h"

Executor::Executor()
{
	fileHandler = new FileHandler();
}

Executor::~Executor()
{
	delete fileHandler;
}

Executor::Executor(const Executor& other)
{
    fileHandler = other.fileHandler ? new FileHandler(*other.fileHandler) : nullptr;
}

Executor::Executor(Executor&& other) noexcept
{
    fileHandler = other.fileHandler;

    other.fileHandler = nullptr;
}

Executor& Executor::operator=(const Executor& other)
{
    if (this != &other) {
        delete fileHandler;

        fileHandler = other.fileHandler ? new FileHandler(*other.fileHandler) : nullptr;
    }
    return *this;
}

Executor& Executor::operator=(Executor&& other) noexcept
{
    if (this != &other) {
        delete fileHandler;

        fileHandler = other.fileHandler;

        other.fileHandler = nullptr;
    }
    return *this;
}

void Executor::print(std::string line, std::string output)
{
	if (output.empty()) {
		std::cout << line;
		if (!(line.empty())) {
			std::cout << std::endl;
		}
	}
	else if(output[1] == '>') {
		fileHandler->append(output, line);
	}
	else {
		fileHandler->write(output, line);
	}
}
