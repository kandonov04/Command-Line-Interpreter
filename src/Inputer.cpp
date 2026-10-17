#include "../h/Inputer.h"

Inputer::Inputer()
{
	reader = new Reader();
	fileHandler = new FileHandler();
}

Inputer::~Inputer()
{
	delete reader;
	delete fileHandler;
}

Inputer::Inputer(const Inputer& other)
{
    reader = other.reader ? new Reader(*other.reader) : nullptr;
    fileHandler = other.fileHandler ? new FileHandler(*other.fileHandler) : nullptr;
}

Inputer::Inputer(Inputer&& other) noexcept
{
    reader = other.reader;
    fileHandler = other.fileHandler;

    other.reader = nullptr;
    other.fileHandler = nullptr;
}

Inputer& Inputer::operator=(const Inputer& other)
{
    if (this != &other) {
        delete reader;
        delete fileHandler;

        reader = other.reader ? new Reader(*other.reader) : nullptr;
        fileHandler = other.fileHandler ? new FileHandler(*other.fileHandler) : nullptr;
    }
    return *this;
}

Inputer& Inputer::operator=(Inputer&& other) noexcept
{
    if (this != &other) {
        delete reader;
        delete fileHandler;

        reader = other.reader;
        fileHandler = other.fileHandler;

        other.reader = nullptr;
        other.fileHandler = nullptr;
    }
    return *this;
}

std::string Inputer::input(std::string arg)
{
	std::string line;

	if (arg[0] == '\"') {
		arg = arg.substr(1, arg.length() - 2);
		line = arg;
	}
	else {
		if (arg[0] == '<') {
			arg = arg.substr(1);
		}
		line = fileHandler->read(arg);
	}

	return line;
}

