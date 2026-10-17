#include "../h/CommandDate.h"
#include "../h/ErrorHandler.h"

CommandDate::CommandDate(Types::Data* myData) : Command(myData)
{
    executor = new Executor();
}

CommandDate::~CommandDate()
{
    delete executor;
}

void CommandDate::checkError()
{
    if (myData->arg.size() > 0) {
        throw ErrorHandler("tooManyArg");
    }

    if (!myData->inputRedir.empty()) {
        throw ErrorHandler("inRdrNotSupported");
    }

    if (!myData->opt.empty()) {
        throw ErrorHandler("optNotSupported");
    }
}

std::string CommandDate::inputCommand()
{
    return std::string();
}

std::string CommandDate::processCommand(std::string line)
{
    auto now = std::chrono::system_clock::now();
    std::time_t nowTime = std::chrono::system_clock::to_time_t(now);
    std::tm localTime;
#ifdef _WIN32
    localtime_s(&localTime, &nowTime);
#else
    localtime_r(&nowTime, &localTime);
#endif
    std::ostringstream ss;
    ss << std::put_time(&localTime, "%d.%m.%Y.");
    std::string date = ss.str();
    return date;
}

void CommandDate::doCommand()
{
    checkError();
    std::string in = inputCommand();
    std::string out = processCommand(in);
    executor->print(out, myData -> outputRedir);
}
